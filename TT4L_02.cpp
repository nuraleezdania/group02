// *********************************************************  
// Program: TT4L_02.cpp  
// Course: CCP6114 Programming Fundamentals 
// Lecture Class: TC2L
// Tutorial Class: TT4L
// Trimester: 2430
// Member_1: 1211110897 | AFAF FAKHRIAH BINTI MOHD FUAD | EMAIL | PHONE
// Member_2: 242UC244LQ | ANIQAH NABILAH BINTI AZHAR | EMAIL | PHONE
// Member_3: 242UC244PT | JASMYNE YAP | EMAIL | PHONE
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
using namespace std;

//function prototypes
bool has_substring(const string& line, const string& substring);
void create_output_screen_and_file();
void create_database();
void create_table();
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

void create_output_screen_and_file()
{
    
}

void create_database()
{
    string fileInputname = "C:\\mariadb\\fileInput1.mdb"; // Adjust based on the file being processed
    ofstream outputFile("fileOutput1.txt");

    cout << "> DATABASES;" << endl;
    cout << fileInputname << endl;

    if (outputFile.is_open()) {
        outputFile << "> DATABASES;" << endl;
        outputFile << fileInputname << endl;
        outputFile.close();
    }
}

void create_table()
{

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
    ofstream fileOutput;
    string fileOutputName;

    vector<vector<string>> table;
    string tableName;

    ifstream fileInput;
    
    string fileInputName = "C:\\mariadb\\fileInput1.mdb";
    //string fileInputName = "C:\\mariadb\\fileInput2.mdb";
    //string fileInputName = "C:\\yourname\\fileInput3.mdb";

    fileInput.open(fileInputName);

    if (!fileInput.is_open() )
    {
        cout << "Unable to open file" << endl;
        exit(-1);
    }

    string line;
    while( getline(fileInput, line ))
    {
        //cout << line << endl;
        if ( has_substring(line, "CREATE TABLE" ))
        {
            cout << "? CREATE TABLE" << endl;
        }
        else if (has_substring(line, "CREATE") )
        {
            fileOutputName = "?";
            cout << "> CREATE " << fileOutputName << ";" << endl;
        }
        else if ( has_substring(line, "DATABASES;") )
        {
            cout << "> " << line << endl;
            cout << "? "<< endl;
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
