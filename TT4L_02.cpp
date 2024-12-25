// *********************************************************
// Program: TT4L_02.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC2L
// Tutorial Class: TT4L
// Trimester: 2430
// Member_1: 1211110897 | AFAF FAKHRIAH BINTI MOHD FUAD | EMAIL | PHONE
// Member_2: 242UC244LQ | ANIQAH NABILAH BINTI AZHAR | aniqah.nabilah.azhar@student.mmu.edu.my | 011-62046219
// Member_3: 242UC244PT | JASMYNE YAP | jasmyne.yap@student.mmu.edu.my | 011-63464323
// Member_4: 242UC244QB | NUR ALEEZ DANIA BINTI MOHD SHAHRUL AZMAN | nur.aleez.dania@student.mmu.edu.my | 019-7109905
// *********************************************************
// Task Distribution
// Member_1:  function for insert_into_table, create fileInput3.mdb, fileOutput3.txt
// Member_2:  function for create_output_screen_and_file, create fileInput2.mdb, fileOutput2.txt
// Member_3:  function for create_table, flowchart (structured diagram)
// Member_4:  function for create_database, and select_all_from_view_table_in_csv_mode 
// *********************************************************
#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <sstream> //for string stream operations
using namespace std;

// Function prototypes
bool has_substring(const string& line, const string& substring); //To check if a substring exist in a string
void create_output_screen_and_file(const string& fileOutputName, const string& outputScreenFile); //To create output for screen and file
void create_database(const string& fileInputName, const string& fileOutputName, string& outputScreenFile); //To create database & view database name
void create_table(ifstream& fileInput, string& outputScreenFile, const string& tableName); //To create table
void insert_into_table(const string& line, string& outputScreenFile, vector<vector<string>>& tableData); //To insert data for row into the table
void select_all_from_view_table_in_csv_mode(const vector<vector<string>>& selectData, string& outputScreenFile); // To output table data in csv mode

// Function definitions
bool has_substring(const string& line, const string& substring)
{
    if (line.find(substring) != string::npos)
    {
        return true; //substring found
    }
    else
    {
        return false; //substring not found
    }

}
void create_output_screen_and_file(const string& fileOutputName, const string& outputScreenFile) {
    cout << outputScreenFile; // Output content to screen

    ofstream fileOutput(fileOutputName); // Append to output file
    if (!fileOutput.is_open()) {
        cout << "Error opening output file" << endl;
        return;
    }

    fileOutput << outputScreenFile; // To write content to output file
    fileOutput.close(); // Close output file
}

void create_database(const string& fileInputName, const string& fileOutputName, string& outputScreenFile) {
    outputScreenFile += "> CREATE " + fileOutputName + ";\n"; // To add CREATE command for database 
    outputScreenFile += "> DATABASES;\n"; // To create DATABASES 
    outputScreenFile += "C:\\mariadb\\" + fileInputName + "\n"; // To view database name
}

void create_table(ifstream& fileInput, string& outputScreenFile, const string& tableName) {
    vector<string> columns;
    string columnLine;

    while (getline(fileInput, columnLine)) {
        if (has_substring(columnLine, "TABLES;")) {
            break; // Stop when TABLES; is encountered
        }

        if (has_substring(columnLine, "CREATE TABLE") || columnLine.empty()) {
            continue; // Skip "CREATE TABLE" or empty lines
        }

        int pos = columnLine.find(' ');
        if (pos != string::npos) {
            string columnName = columnLine.substr(0, pos);
            string columnType = columnLine.substr(pos + 1);
            if (!columnType.empty()) {
                columns.push_back(columnName + " " + columnType);
            }
        }
    }

    // Build the CREATE TABLE statement
    string createTableStatement = "> CREATE TABLE " + tableName + "(\n";
    for (int i = 0; i < columns.size(); ++i) {
        createTableStatement += columns[i];
        if (i != columns.size() - 1) {
            //createTableStatement += ",";
            createTableStatement += "\n";
        } else {
            createTableStatement += "\n"; // Add a newline after the last column
        }
    }
    createTableStatement += ");\n";

    outputScreenFile += createTableStatement;

    // Add table to TABLES output
    string tablesStatement = "> TABLES;\n" + tableName + "\n";
    outputScreenFile += tablesStatement;
}

void insert_into_table(const string& line, string& outputScreenFile, vector<vector<string>>& tableData) {
    string insertStatement = "> " + line + "\n";
    outputScreenFile += insertStatement;

    int valuesStart = line.find("VALUES (");
    if (valuesStart != string::npos) {
        string valuesPart = line.substr(valuesStart + 8); // Extract values part after "VALUES ("

        int closingPos = valuesPart.find_last_of(")");
        if (closingPos != string::npos) {
            valuesPart = valuesPart.substr(0, closingPos);
        }

        vector<string> rowData;
        stringstream ss(valuesPart);
        string value;

        while (getline(ss, value, ',')) {
            value.erase(0, value.find_first_not_of(" '\"")); // Trim leading spaces and quotes
            value.erase(value.find_last_not_of(" '\"") + 1); // Trim trailing spaces and quotes
            rowData.push_back(value);
        }

        tableData.push_back(rowData); // Add row data to table
    }
}

//Function to select all from view table in csv format
void select_all_from_view_table_in_csv_mode(const vector<vector<string>>& selectData, string& outputScreenFile) {
    string selectQuery = "> SELECT * FROM customer;\n"; // To add SELECT statement to output
    string header = "customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email,\n"; //To defined the header of the table
    string rows;

    //
    for (const auto& row : selectData) {
        string rowContent;
        for (int i = 0; i < row.size(); ++i) {
            rowContent += row[i];
            if (i != row.size() - 1) rowContent += ","; // To add comma between values
        }
        rowContent += ",\n";
        rows += rowContent;
    }

    outputScreenFile += selectQuery + header + rows; // To add SELECT query, header and rows to output
}

int main() {
    string fileInputName = "fileInput1.mdb"; // Name of the input file ( change if needed )
    string fileOutputName = "fileOutput1.txt"; //// Name of the output file ( change if needed )

    ifstream fileInput(fileInputName);  //To open input file
    if (!fileInput.is_open()) { // To check if the input file can be open or not
        cout << "Error opening input file" << endl;
        return -1;
    }

    string outputScreenFile;
    vector<vector<string>> tableData;

    create_database(fileInputName, fileOutputName, outputScreenFile); //create_database function

    string line;
    while (getline(fileInput, line)) {
        if (has_substring(line, "CREATE TABLE")) 
        {
            create_table(fileInput, outputScreenFile, "customer");
        } 
        else if (has_substring(line, "INSERT INTO")) 
        {
            insert_into_table(line, outputScreenFile, tableData);
        }
    }

    select_all_from_view_table_in_csv_mode(tableData, outputScreenFile); //Output table data in csv format
    create_output_screen_and_file(fileOutputName, outputScreenFile); //Output to screen and file

    fileInput.close(); //To close input file

    return 0; // To exit program
}
