/*Software to estimate the value of money invested at any point of time beyond 1960: Compound Interest*/

#include <iostream> //To use cout and cin
#include <string> //To use string
#include <fstream> //To read from file
#include <sstream> //To use stringstream
#include <iomanip> //To use setprecision
#include <limits> //To use numeric_limits
#include <cctype> //To use isdigit()
#include <windows.h> //To use Sleep() in windows 

using namespace std;

int main(){
    //Variable declarations
    string original_path="D:\\OOPD\\Assig1\\Data\\india_data.csv"; //Path of the original csv file 
    string path="D:\\OOPD\\Assig1\\Data\\india_data_modified.csv"; //Path of the modified csv file
    float principal=0, amount=0, value=0, interest=0;
    int year=1960, current_year=2023, choice=1;
    bool should_continue=true;


    //Function declarations/prototypes
    bool Is_Valid_Choice(string&);
    int Get_Valid_Choice();
    void Remove_Header_Row(string&, string&);
    void Print_Interest_and_Inflation_Rate(string&);
    void Take_Inputs(float&, int&, int&, bool&);
    bool Is_Valid_Principal(string&);
    float Get_Valid_Principal();
    bool Is_Valid_Year(string&);
    int Get_Valid_Year();
    void Update_Current_Year(int&);
    float Get_Interest_Rate(int, string&);
    float Calculate_Amount(float, int, int, string&);
    float Get_Inflation_Rate(int, string&);
    float Calculate_Value(float, int, int, string&);
    void Exit_Protocol();
    

    restart: //Label to restart the program
    
    Sleep(1000); //Delay for 1 second
    cout<<"-------------------------------------------------"<<endl;
    cout<<"Welcome to Indian Bank Investment Software"<<endl;
    cout<<"-------------------------------------------------"<<endl;
    cout<<"What would you like to do?"<<endl;
    cout<<"1. View changing Interest and Inflation Rates for your country between 1960 & 2022"<<endl;
    cout<<"2. Calculate the amount of money received as of the current year ("<<current_year<<")"<<endl;
    cout<<"3. Calculate the value [amount with inflation adjustment] of money received as of the current year ("<<current_year<<")"<<endl;
    cout<<"4. Both 2 and 3"<<endl;
    cout<<"5. Change current year"<<endl;
    choice = Get_Valid_Choice();

    switch (choice)    {
    case 1: Remove_Header_Row(original_path, path); // Remove header row from the csv file
            Print_Interest_and_Inflation_Rate(path); // Print all interest and inflation rates
            cout<<"Changing Interest and Inflation Rates have been printed."<<endl;
            Exit_Protocol(); // Exit the program
    case 2: Take_Inputs(principal, year, current_year, should_continue); // Take inputs from the user
            if (should_continue==false){goto restart;} //Restart the program
            Remove_Header_Row(original_path, path); // Remove header row from the csv file
            amount = Calculate_Amount(principal, year, current_year, path); // Calculate amount without inflation adjustment
            cout.setf(ios::fixed); //To set the precision after the decimal point
            cout<<"Amount (INR) received: "<<setprecision(2)<<amount<<endl;
            cout<<"Interest (INR) received on amount: "<<setprecision(2)<<(amount - principal)<<endl;
            Exit_Protocol(); // Exit the program
    case 3: Take_Inputs(principal, year, current_year, should_continue); // Take inputs from the user
            if (should_continue==false){goto restart;} //Restart the program
            Remove_Header_Row(original_path, path); // Remove header row from the csv file
            value = Calculate_Value(principal, year, current_year, path); // Calculate value with inflation adjustment
            cout.setf(ios::fixed); //To set the precision after the decimal point
            cout<<"Value (INR) received: "<<setprecision(2)<<value<<endl;
            cout<<"Interest (INR) received on value: "<<setprecision(2)<<(value - principal)<<endl;
            Exit_Protocol(); // Exit the program
    case 4: Take_Inputs(principal, year, current_year, should_continue); // Take inputs from the user
            if (should_continue==false){goto restart;} //Restart the program
            Remove_Header_Row(original_path, path); // Remove header row from the csv file
            amount = Calculate_Amount(principal, year, current_year, path); // Calculate amount without inflation adjustment
            value = Calculate_Value(principal, year, current_year, path); // Calculate value with inflation adjustment
            cout.setf(ios::fixed); //To set the precision after the decimal point
            cout<<"Amount (INR) received: "<<setprecision(2)<<amount<<endl;
            cout<<"Interest (INR) received on amount: "<<setprecision(2)<<(amount - principal)<<endl;
            cout<<"Value (INR) received: "<<setprecision(2)<<value<<endl;
            cout<<"Interest (INR) received on value: "<<setprecision(2)<<(value - principal)<<endl;
            Exit_Protocol(); // Exit the program
    case 5: Update_Current_Year(current_year); // Update current year
            goto restart; //Restart the program
    default:
        cout<<"Invalid choice."<<endl;
        Exit_Protocol(); // Exit the program
    }

    return 0;
}



// Function definitions

bool Is_Valid_Choice(string& input){

    int decimal_count = 0; //For checking any decimal point
    bool digit_found = false; //For checking if any non-digit entity is entered

    for (char c : input) { //Run though the 'for' loop for every character in the string 'input' 
        if (isdigit(c)) {
            digit_found = true;
        } else if (c == '.') {
            decimal_count++;
            if (decimal_count > 0) {
                cout<<"Decimal point found. Choice must be a whole number."<<endl;
                return false; 
            }
        } else if (c == '-') {
            cout<<"Negative choice found. Choice must be a whole number."<<endl;
            return false;      
        } else {
            cout<<"Invalid character(s) found. Choice must be a whole number."<<endl;
            return false; 
        }
    }

    if (!digit_found) {
        cout<<"No digits found."<<endl;
        return false; // No digits found
    }

    int value = stoi(input);
    return ((value > 0) && (value<6)); // Check if value is greater than 0 and less than 6

}



int Get_Valid_Choice(){
    string choice;
    while (true) {
        cout << "Choice: ";
        getline(cin, choice); 

        if (Is_Valid_Choice(choice)) {
            return stoi(choice);
        } else {
            cout << "Invalid input. Please enter a valid choice in digits (between 1 & 5) only." << endl;
        }
    }
}


void Remove_Header_Row(string& input_file, string& output_file) {
    ifstream in_file(input_file);
    ofstream out_file(output_file);

    // Check if the input file can be opened
    if (!in_file.is_open()) {
        cout << "Error opening input file: " << input_file << endl;
        cout<<"Please check if the file exists."<<endl;
        abort(); //Exit the program
    }

    // Read and skip the header row
    string header_row;
    if (getline(in_file, header_row)) {  
        ;//Do nothing. Just skip the header row.
    } else {
        cout << "Input file is empty." << endl;
        cout<<"Please check if the file contains any data."<<endl;
        abort(); //Exit the program
    }

    // Write the remaining rows to the output file
    string row;
    while (getline(in_file, row)) {
        out_file << row << endl;
    }

    // Close the file streams
    in_file.close();
    out_file.close();
}


void Print_Interest_and_Inflation_Rate(string& path){
    ifstream input_file; //Create an input file stream
    input_file.open(path); //Open the file
    
    cout<<"------------------------------------------------"<<endl;

    string row; //To store the row read from the file
    while (getline(input_file, row)) { 

        int serial_no, year;
        string temp_string=""; //Empty string for temporarily storing non-string data types

        stringstream input_string(row); //To parse the data read into the string
        
        getline(input_string, temp_string, ','); 
        serial_no = stoi(temp_string); //stoi() converts string to int
        
        getline(input_string, temp_string, ',');
        year = stoi(temp_string); 

        getline(input_string, temp_string, ',');
        float interest_rate = stof(temp_string); //stof() converts string to float
        
        getline(input_string, temp_string, ',');
        float inflation_rate = stof(temp_string); 
         
        cout<<"Year: "<<year<<" | ";
        cout<<"Interest Rate: "<<setw(10)<<interest_rate<<" | ";
        cout<<"Inflation Rate: "<<setw(10)<<inflation_rate<<endl;
    }

    input_file.close();
    cout<<"------------------------------------------------"<<endl;
}
 



bool Is_Valid_Principal(string& input) {

    int decimal_count = 0; //For checking more than 1 decimal point
    bool digit_found = false; //For checking if any non-digit entity is entered

    for (char c : input) { //Run though the 'for' loop for every character in the string 'input' 
        if (isdigit(c)) {
            digit_found = true;
        } else if (c == '.') {
            decimal_count++;
            if (decimal_count > 1) {
                cout<<"More than one decimal point found."<<endl;
                return false; 
            }
        } else if (c == '-') {
            cout<<"Negative principal amount found."<<endl;
            return false;       
        } else {
            cout<<"Invalid character(s) found."<<endl;
            return false; 
        }
    }

    if (!digit_found) {
        cout<<"No digits found."<<endl;
        return false; 
    }

    float value = stof(input);
    return (value >= 0); // Check if value is positive
}


float Get_Valid_Principal() {
    string invested_amount;
    while (true) {
        cout << "Amount (INR) invested: ";
        getline(cin, invested_amount); 
        /*getline() is used to read the entire line of input, including spaces and newline characters. 
        Unlike cin, it does not skip whitespace characters.*/

        if (Is_Valid_Principal(invested_amount)) {
            return stof(invested_amount);
        } else {
            cout << "Invalid input. Please enter a valid positive principal amount in digits only." << endl;
        }
    }
}

bool Is_Valid_Year(string& input) {

    int decimal_count = 0; //For checking any decimal point
    bool digit_found = false; //For checking if any non-digit entity is entered

    for (char c : input) { //Run though the 'for' loop for every character in the string 'input' 
        if (isdigit(c)) {
            digit_found = true;
        } else if (c == '.') {
            decimal_count++;
            if (decimal_count > 0) {
                cout<<"Decimal point found. Year must be a four-digit whole number."<<endl;
                return false; 
            }
        } else if (c == '-') {
            cout<<"Negative year found. Year must be a four-digit whole number."<<endl;
            return false;      
        } else {
            cout<<"Invalid character(s) found. Year must be a four-digit whole number."<<endl;
            return false; 
        }
    }

    if (!digit_found) {
        cout<<"No digits found."<<endl;
        return false; 
    }

    int value = stoi(input);
    return ((value > 1959) && (value<2023)); // Check if value is greater than 1959 and less than 2023
}

int Get_Valid_Year() {
    string year_invested;
    while (true) {
        cout << "Year of Investment: ";
        getline(cin, year_invested);

        if (Is_Valid_Year(year_invested)) {
            return stoi(year_invested);
        } else {
            cout << "Invalid input. Please enter a valid year in digits only." << endl;
        }
    }
}

void Take_Inputs(float& principal, int& year, int& current_year, bool& should_continue){
    cout<<"------------------------------------------------"<<endl;
    cout<<"Please enter the following details"<<endl;
    principal = Get_Valid_Principal(); // Get valid principal amount
    year = Get_Valid_Year(); // Get valid year of investment
    if (year>current_year){
        cout<<"Year of investment cannot be greater than current year."<<endl;
        should_continue = false;
    }
    else if (year==current_year){
        cout<<"Year of investment is equal to current year."<<endl;
        cout<<"Amount (INR) received: "<<principal<<endl;
        cout<<"No interest received."<<endl;
        should_continue = false;
    }
    else{
        cout<<"------------------------------------------------"<<endl;
        cout<<"Amount (INR) invested: "<<principal<<endl;
        cout<<"Year of Investment: "<<year<<endl;
        cout<<"Current year: "<<current_year<<endl;
        should_continue = true;
    }
}

void Update_Current_Year(int& current_year){
    cout<<"------------------------------------------------"<<endl;
    cout<<"Current year: "<<current_year<<endl;
    string new_year;
    while (true)
    {   cout<<"Enter a valid new current year: ";
        getline(cin, new_year);

        if (new_year=="2023"){
            current_year = 2023;
            cout<<"Current year updated to "<<current_year<<endl;
            break;
        }
        else if (Is_Valid_Year(new_year)) {
            current_year = stoi(new_year);
            cout<<"Current year updated to "<<current_year<<endl;
            break;
        } else {
            cout << "Invalid input." << endl;
        }
    }    
}

float Get_Interest_Rate(int year, string& path){
    ifstream input_file; //Create an input file stream
    input_file.open(path); //Open the file
    
    string row; //To store the row read from the file
    while (getline(input_file, row)) { 
        int serial_no, temp_year;
        string temp_string=""; //Empty string for temporarily storing non-string data types

        stringstream input_string(row); //To parse the data read into the string
        
        getline(input_string, temp_string, ','); 
        serial_no = stoi(temp_string); 
        
        getline(input_string, temp_string, ',');
        temp_year = stoi(temp_string); 

        getline(input_string, temp_string, ',');
        float interest_rate = stof(temp_string); 
        
        getline(input_string, temp_string, ',');
        float inflation_rate = stof(temp_string); 

        if (temp_year==year){
            return interest_rate;
        }
    }
    input_file.close();
    return 0;
}

float Calculate_Amount(float principal, int year, int current_year, string& path){
    for (int i=year; i<current_year; i++){
        float interest_rate = Get_Interest_Rate(i, path);
        principal = principal*(1+(interest_rate/100));
    }
    return principal;
}

float Get_Inflation_Rate(int year, string& path){
    ifstream input_file; 
    input_file.open(path); 
    
    string row; 
    while (getline(input_file, row)) { 
        int serial_no, temp_year;
        string temp_string=""; 

        stringstream input_string(row); 
        
        getline(input_string, temp_string, ','); 
        serial_no = stoi(temp_string); 
        
        getline(input_string, temp_string, ',');
        temp_year = stoi(temp_string); 

        getline(input_string, temp_string, ',');
        float interest_rate = stof(temp_string); 
        
        getline(input_string, temp_string, ',');
        float inflation_rate = stof(temp_string); 

        if (temp_year==year){
            return inflation_rate;
        }
    }
    input_file.close();
    return 0;
}

float Calculate_Value(float principal, int year, int current_year, string& path){
    for (int i=year; i<current_year; i++){
        float interest_rate = Get_Interest_Rate(i, path);
        float inflation_rate = Get_Inflation_Rate(i, path);
        principal = principal*(1+((interest_rate-inflation_rate)/100));
    }
    return principal;
}

void Exit_Protocol(){
    cout<<"Thank you for letting us serve you. Toodles!"<<endl;
    Sleep(1000); //Delay for 1 second
    abort(); //Exit the program
}
