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
// Member_4:  function for create_database, pseudocode
// *********************************************************
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

//function prototypes
bool has_substring(const string& line, const string& substring);
void create_output_screen_and_file(const string& fileOutputName, const string& content);
void create_database(ofstream& outputFile);
void create_table(ifstream& fileInput, ostream& outputFile);
void insert_into_table(const string& line, string& outputScreenFile, string& insertStatement);
void select_all_from_view_table_in_csv_mode(const vector<vector<string>>& selectData, string& outputScreenFile);


//function definitions
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


void create_output_screen_and_file(const string& fileOutputName, const string& content)
{
    cout<< content <<endl; //output content to screen

    ofstream outputFile(fileOutputName); //opening output file
    if(!outputFile.is_open())
    {
        cout<< "Error opening output file"<<endl;
        return;
    }

    outputFile << content << endl; //print content to output file
    outputFile.close(); //close output file
}

//Database function
void create_database(ofstream& outputFile) 
{
    string db_name = "C:\\mariadb\\fileInput1.mdb"; //database name ( change if needed)
     cout << db_name << endl;

    if (outputFile.is_open()) {         //open in output file
        outputFile << "> DATABASES;" << endl;
        outputFile << db_name << endl;
    } else {
        cout << "Error opening output file" << endl; //Message if the output file cannot open
    }
}

void create_table(ifstream& fileInput, ofstream& outputFile)
{
    vector<string> columns; // Vector to hold column definitions
    string columnLine;

    while (getline(fileInput, columnLine)) {
        if (has_substring(columnLine, "TABLES;")) {
            break; // Stop when TABLES; is encountered
        }

        // Skip lines containing "CREATE TABLE" or empty lines
        if (has_substring(columnLine, "CREATE TABLE") || columnLine.empty()) {
            continue;
        }

        // Process the column definition lines
        size_t pos = columnLine.find(' ');
        if (pos != string::npos) {
            string columnName = columnLine.substr(0, pos); // Extract column name
            string columnType = columnLine.substr(pos + 1); // Extract column type

            // Ensure columnType is not empty and strip any unwanted spaces
            if (!columnType.empty()) {
                // Create the column definition string
                string columnDef = columnName + " " + columnType;
                columns.push_back(columnDef); // Add to vector
            }
        }
    }

    // Begin creating the CREATE TABLE statement
    string createTableStatement = "> CREATE TABLE customer(\n";

    // Add columns from the vector to the CREATE TABLE statement
    for (size_t i = 0; i < columns.size(); ++i) {
        if (i != 0) {
            createTableStatement += "\n"; // Add new line between columns
        }
        createTableStatement += columns[i]; // Add column definition
    }

    createTableStatement += "\n);"; // Close the CREATE TABLE statement

    // Output the statement to the screen
    cout << createTableStatement << endl;

    // Write the statement to the output file
    if (outputFile.is_open()) {
        outputFile << createTableStatement << endl;
    }
    else {
        cout << "Error opening output file" << endl;
    }
}


void insert_into_table(ifstream& fileInput, ofstream& fileOutput)
{
    string line;

    // To read the INSERT INTO line to get the table name
    while (getline(fileInput, line))
    {
        if (has_substring(line, "INSERT INTO"))
        {
            // To find the table name based on INSERT INTO statement.
            size_t pos = line.find("INSERT INTO");
            size_t startPos = pos + 11; // Skip "INSERT INTO"
            size_t endPos = line.find("(", startPos);
            string tableName = line.substr(startPos, endPos - startPos);

            // Trim any leading or trailing spaces
            tableName.erase(0, tableName.find_first_not_of(" "));
            tableName.erase(tableName.find_last_not_of(" ") + 1);

            // Output the table name
            fileOutput << "> INSERT INTO " << tableName << " VALUES" << endl;
            cout << "> INSERT INTO " << tableName << " VALUES" << endl;

            while (getline(fileInput, line))
            {
                if (line.find(");") != string::npos)
                {
                    size_t start = line.find("(");
                    size_t end = line.find(")");

                    if (start != string::npos && end != string::npos)
                    {
                        // To extract the values
                        string values = line.substr(start + 1, end - start - 1);

                        // Print out the values.
                        fileOutput << "(" << values << ");" << endl;
                        cout << "(" << values << ");" << endl;
                    }
                    break;  // Exit after the INSERT statement ends.
                }
                else
                {
                    size_t start = line.find("(");
                    size_t end = line.find(")");

                    if (start != string::npos && end != string::npos)
                    {
                        // To extract the values
                        string values = line.substr(start + 1, end - start - 1);

                        // Print out the values.
                        fileOutput << "(" << values << ");" << endl;
                        cout << "(" << values << ");" << endl;
                    }
                }
            }
        }
    }

    fileOutput.close();

    cout << "Output file has been created. Data saved to the output file." << endl;
}

void select_all_from_view_table_in_csv_mode(ifstream& fileInput, ofstream& fileOutput) {
    string line;
    vector<string> headers;
    vector<vector<string>> rows;

    while (getline(fileInput, line)) {
        if (has_substring(line, "SELECT * FROM")) {
            getline(fileInput, line); // Read the headers
            stringstream ss(line);
            string header;
            while (getline(ss, header, ',')) {
                headers.push_back(header);
            }

            while (getline(fileInput, line)) {
                if (line.empty()) break;
                stringstream rowStream(line);
                vector<string> row;
                string value;
                while (getline(rowStream, value, ',')) {
                    row.push_back(value);
                }
                rows.push_back(row);
            }
            break;
        }
    }

    if (fileOutput.is_open()) {
        for (const auto& header : headers) {
            fileOutput << header;
            if (&header != &headers.back()) fileOutput << ",";
        }
        fileOutput << "\n";

        for (const auto& row : rows) {
            for (const auto& value : row) {
                fileOutput << value;
                if (&value != &row.back()) fileOutput << ",";
            }
            fileOutput << "\n";
        }
    } else {
        cout << "Error opening output file" << endl;
    }
}

//Main function
int main()
{
    // Declare and open the output file before passing it to the function
    ofstream fileOutput;
    fileOutput.open("fileOutput1.txt");  // Open output file for writing
    if (!fileOutput.is_open()) {
        cout << "Error opening output file" << endl;
        return -1;
    }

    string fileInputName = "fileInput1.mdb"; //Name of the input file (can be change if needed)
    ifstream fileInput(fileInputName);  //Open the input file for reading
    string fileOutputName = "fileOutput1.txt";  //Name of the output file

    if (!fileInput.is_open()) {     //To check if the input file opened successfully
        cout << "Error opening input file" << endl; //Print error message
        return -1; //Exit the program with an error code
    }

    //Print the creation of the output file
    if (fileOutput.is_open()) { //Verify the output file is open
        fileOutput << "> CREATE " << fileOutputName << "\n";
    } else {
        cout << "Error opening output file" << endl;
    }
    string line;
    while (getline(fileInput, line)) {

        if(line.empty()) {
            continue;
        }        
        
        cout << "> " << line << endl; //

        if (has_substring(line, "CREATE TABLE")) 
        {
            create_table(fileInput, fileOutput);
        } 
        else if (has_substring(line, "CREATE")) 
        {

        } 
        else if (has_substring(line, "DATABASES")) 
        {
            create_database(fileOutput);
        } 
        else if (has_substring(line, "SELECT * FROM")) 
        {
            select_all_from_view_table_in_csv_mode(fileInput, fileOutput);
        } 
        else if (has_substring(line, "INSERT INTO")) 
        {
            insert_into_table(fileInput, fileOutput);
        }
        else {
            cout << "Invalid input command -> " << line << endl; //Print error
        }
    }
    cout << endl;

    fileInput.close();
    fileOutput.close();

    return 0;
}
