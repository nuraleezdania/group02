#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

//function prototypes
void create_output_screen_and_file();
void create_database();
void create_table();
void insert_into_table();
void select_all_from_view_table_in_csv_mode();

struct Column {
    string name;
    string type; // INT or TEXT
};

struct Table {
    string name;
    vector<Column> columns;
    vector<vector<string> > rows;
};

vector<Table> database;

//function definitions
//function to output content both screen and into output file
void create_output_screen_and_file(const string& fileOutputName, const string& content){
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

//function to create database
void create_database(const string& db_name) {
}

//function to create table
void create_table(const string& table_name, const vector<Column>& columns) {
    Table table;
    table.name = table_name;
    table.columns = columns;
    database.push_back(table);
    cout << "Table '" << table_name << "' created successfully." << endl;
}

//function to create insert into table
void insert_into_table(const string& table_name, const vector<string>& row) {
    for (auto& table : database) {
        if (table.name == table_name) {
            if (row.size() != table.columns.size()) {
                cout << "Error: Row size does not match the table's column size." << endl;
                return;
            }
            table.rows.push_back(row);
            cout << "Row inserted into table '" << table_name << "' successfully." << endl;
            return;
        }
    }
    cout << "Error: Table '" << table_name << "' not found." << endl;
}

//function to view table in CSV mode
void view_table_in_csv_mode(const string& table_name) {
    for (const auto& table : database) {
        if (table.name == table_name) {
            for (const auto& col : table.columns) {
                cout << col.name << ",";
            }
            cout << endl;

            for (const auto& row : table.rows) {
                for (const auto& value : row) {
                    cout << value << ",";
                }
                cout << endl;
            }
            return;
        }
    }
    cout << "Error: Table '" << table_name << "' not found." << endl;
}

//main
int main() {

    //To create database
    create_database("Databases");

    //To create table
    vector<Column> columns = {
        {"ID", "INT"}, {"Name", "TEXT"}, {"City", "TEXT"}, 
        {"State", "TEXT"}, {"Country", "TEXT"}, {"Phone", "TEXT"}, {"Email", "TEXT"}
    };  
    create_table("customer", columns);

    //To insert rows into table
    insert_into_table("customer", {"1", "name1", "city1", "state1", "country1", "phone1", "email1"});
    insert_into_table("customer", {"2", "name2", "city2", "state2", "country2", "phone2", "email2"});
    insert_into_table("customer", {"3", "name3", "city3", "state3", "country3", "phone3", "email3"});
    insert_into_table("customer", {"4", "name4", "city4", "state4", "country4", "phone4", "email4"});

    //To view table in CSV mode
    view_table_in_csv_mode("customer");

    //Read a file
    fstream fileInput1;
    
    string fileOutputName;

    string fileInputName = "C:\\mariadb\\fileInput1.mdb";
    //string fileInputName = "C:\\yourname\\fileInput2.mdb";
    //string fileInputName = "C:\\yourname\\fileInput3.mdb";

    fileInput1.open("fileInput1.mdb");

    if (!fileInput1.is_open() )
    {
        cout << "Unable to open file" << endl;
        exit(-1);
    }

    string line;
    while( getline(fileInput1, line ))
    {
        cout << line << endl;
    }
    cout << endl;

    fileInput1.close();

    //fileOutputName = "fileOutput1.txt"; //incorrect
    
    cout << "> CREATE " << fileOutputName << ";" << endl;

    cout << "> DATABASES;" << endl;
    cout << fileInputName << endl;

    {
        getline(fileInput1, line);
        cout << line;
    }
    cout << endl;

    void create_output_screen_and_file();

    return 0;

}