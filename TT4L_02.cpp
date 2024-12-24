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
void create_database();
void create_table(ifstream& fileInput, ostream& outputFile);
void insert_into_table();
void select_all_from_view_table_in_csv_mode();


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

void create_database()
{
    string fileInputname = "C:\\A2_CCP6114_2430_TT4L_G02_Afaf_Aniqah_JasmyneYap_NurAleezL\\fileInput1.mdb"; // Adjust based on the file being processed
    ofstream outputFile("fileOutput1.txt");

    cout << "> DATABASES;" << endl;
    cout << fileInputname << endl;

    if (outputFile.is_open()) {
        outputFile << "> DATABASES;" << endl;
        outputFile << fileInputname << endl;
        outputFile.close();
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


void insert_into_table()
{

}

void select_all_from_view_table_in_csv_mode()
{

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

    string fileInputName = "fileInput1.mdb";
    ifstream fileInput(fileInputName);
    string fileOutputName;

    if (!fileInput.is_open()) {
        cout << "Unable to open input file" << endl;
        return -1;
    }

    string line;
    while( getline(fileInput, line ))
    {
        //cout << line << endl;
        if ( has_substring(line, "CREATE TABLE" ))
        {
            create_table(fileInput,fileOutput);
        }
        else if (has_substring(line, "CREATE") )
        {
            fileOutputName = "fileOutput1.txt";
            cout << "> CREATE " << fileOutputName << ";" << endl;
        }
        else if ( has_substring(line, "DATABASES;") )
        {
            stringstream content;
            content << "> " << line << endl;
            content << "C:\\mariadb\\"<< fileInputName << endl;
            fileOutput << "> " << line << endl;
            fileOutput << fileInputName << endl;
        }
        else if ( has_substring(line, "?1") )
        {
            cout << "?1" << endl;
        }
        else if ( has_substring(line, "?2") )
        {
            cout << "?2" << endl;
        }
        else if ( has_substring(line, "?3") )
        {
            cout << "?3" << endl;
        }
        else if ( has_substring(line, "?4") )
        {
            cout << "?4" << endl;
        }
        else if ( has_substring(line, "?5") )
        {
            cout << "?5" << endl;
        }
        else if ( has_substring(line, "?6") )
        {
            cout << "?6" << endl;
        }
/*      else
        {
            cout << "Error message: Invalid input command" << endl;
        }
        */

    }

    cout << endl;

    fileInput.close();
    fileOutput.close();

    //fileOutputName = "fileOutput1.txt"; //incorrect
    //cout << "> CREATE " << fileOutputName << ";" << endl;

    //cout << "> DATABASES;" << endl;
    //cout << fileInputName << endl;

    return 0;
}
