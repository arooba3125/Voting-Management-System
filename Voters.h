#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int voters_no = 100;

struct Areadetails {
    string NA_constituencyno;
    string PA_constituencyno;
    string polling_station;
};

struct Voters {
   int Block_code;
    long long int CNIC;
    int series_no;
    int family_no;
    Areadetails Area;
};

void Voters_Menu();
void Votersadd_record(Voters newvoter[], int& index);
void Votersview_record(Voters newvoter[], int& index);
void Voterssearch_record(Voters newvoter[], int& index);
void Votersupdate_record(Voters newvoter[], int& index);
void readfromfile(Voters newvoter[], int& index);
void writetofile(Voters newvoter[], int index);
void input_voter_details(Voters& voter);


void Voters_Menu() {
    Voters newvoter[voters_no];
    int index = 0;
    readfromfile(newvoter, index);
    cout << "*** Welcome to Voters Database ***" << endl;
    cout << "---------------------------------" << endl;
    cout << "1. Add Voters Record" << endl;
    cout << "2. View Voters Record" << endl;
    cout << "3. Search Voters Record" << endl;
    cout << "4. Update Voters Record" << endl;
    cout << "5. Back to Main Menu" << endl;

    int choice;
    do {
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            Votersadd_record(newvoter, index);
            break;
        case 2:
            Votersview_record(newvoter, index);
            break;
        case 3:
            Voterssearch_record(newvoter, index);
            break;
        case 4:
            Votersupdate_record(newvoter, index);
            break;
        case 5:
            break;
        default:
            cout << "Enter a valid choice.\n";
        }
    } while (choice != 6);
}



void Votersadd_record(Voters newvoter[], int& index) {
    ofstream fout("Voters.txt", ios::app);
    int input_cnic;
    cout << "Please enter your CNIC: ";
    cin >> input_cnic;

    for (int i = 0; i < index; i++) {
        if (input_cnic == newvoter[i].CNIC) {
            cout << "You are already registered." << endl;
            return;
        }
    }

    newvoter[index].CNIC = input_cnic;

    input_voter_details(newvoter[index]); // Call the function to input voter details

    // Write the record to the file with proper formatting
    writetofile(newvoter, index);
    cout << "New voter record added successfully!\n";
    index++;
    fout.close();
}


void Votersview_record(Voters newvoter[], int& index) {
    ifstream fin("Voters.txt");
    try {
        if (!fin.is_open()) {
            throw runtime_error("Error opening the file for reading.");
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        return; // Exit the function if file opening fails
    }

    cout << setw(10) << "Block Code" << setw(15) << "CNIC" << setw(10) << "Series No" 
        << setw(10) << "Family No" << setw(20) << "NA Constituency No" << setw(20) 
        << "PA Constituency No" << setw(30) << "Polling Station" << endl;

    // Read and display each record until the end of the file
    for (int i = 0; i < index; i++) {
        cout << setw(10) << newvoter[i].Block_code << setw(15) 
            << newvoter[i].CNIC << setw(10) << newvoter[i].series_no << setw(10)
            << newvoter[i].family_no << setw(20) 
            << newvoter[i].Area.NA_constituencyno << setw(20) << newvoter[i].Area.PA_constituencyno
            << setw(30) << newvoter[i].Area.polling_station << endl;
    }

    fin.close();
}

void Voterssearch_record(Voters newvoter[], int& index) {
    ifstream fin("Voters.txt");
    try {
        if (!fin.is_open()) {
            throw runtime_error("Error opening the file for reading.");
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        return;
    }

    int searchCNIC;
    bool found = false;
    cout << "Enter the CNIC of the voter you want to check: ";
    cin >> searchCNIC;
    // Loop through the records in the file
    for (int i = 0; i < index; i++) {
       
        if (newvoter[i].CNIC == searchCNIC) {
            found = true;
            cout << setw(10) << newvoter[i].Block_code << setw(15) << newvoter[i].CNIC 
                << setw(10) << newvoter[i].series_no << setw(10)
                << newvoter[i].family_no << setw(20) << newvoter[index].Area.NA_constituencyno << setw(20) << newvoter[i].Area.PA_constituencyno
                << setw(30) << newvoter[i].Area.polling_station << endl;
            break; // Once found, no need to continue searching
        }
    }
    if (!found) {
        cout << "Record not found for CNIC:" << searchCNIC << ". It may not be registered for voting." << endl;
    }
    fin.close();
}

void Votersupdate_record(Voters newvoter[], int& index) {
    ifstream fin("Voters.txt");
    try {
        if (!fin.is_open()) {
            throw runtime_error("Error opening the file for reading.");
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        return;
    }
    ofstream fout("temp.txt");
    int cnic;
    bool update = false;
    cout << "Enter your CNIC for updating voter data: ";
    cin >> cnic;

    // Loop through the records in the file
    for (int i = 0; i < index; i++) {
       
        if (cnic == newvoter[i].CNIC) {
            update = true;
            // Update record directly at the appropriate index
            cout << "Record found for CNIC: " << cnic << ". Please provide the updated information." << endl;
            // Update the record by calling the function to input voter details
            input_voter_details(newvoter[i]);
        }// Write the record to the temporary file
        fout << setw(10) << newvoter[i].Block_code << setw(15) << newvoter[i].CNIC << setw(10) << newvoter[i].series_no << setw(10)
            << newvoter[i].family_no << setw(20) << newvoter[i].Area.NA_constituencyno << setw(20) << newvoter[i].Area.PA_constituencyno
            << setw(30) << newvoter[i].Area.polling_station << endl;  
    }
        cout << "RECORD UPDATED SUCCESSFULLY" << endl;
    fin.close();
    fout.close();
    if (!update) {
        cout << "CNIC does not exist" << endl;
    }
    else {
        // Replace the original file with the updated one
        remove("Voters.txt");
        rename("temp.txt", "Voters.txt");
    }
}

void readfromfile(Voters newvoter[], int& index) {
    ifstream fin;   
    fin.open("Voters.txt");
    try {
        if (!fin.is_open()) {
            throw runtime_error("File  does not exist.");
        }
    }
        catch (runtime_error& e) {
            cout << "Error: " << e.what() << endl;
            return;
        }

        while (fin >> newvoter[index].Block_code >> newvoter[index].CNIC >> newvoter[index].series_no >> newvoter[index].family_no >>
            newvoter[index].Area.NA_constituencyno >> newvoter[index].Area.PA_constituencyno) {
            getline(fin, newvoter[index].Area.polling_station);
            index++;
        }
       
}

void writetofile(Voters newvoter[], int index) {
    ofstream fout("Voters.txt", ios::app); // Open the file in append mode

    // Write each record to the file with proper formatting
    fout << setw(10) << newvoter[index].Block_code << setw(15) << newvoter[index].CNIC << setw(10) << newvoter[index].series_no << setw(10)
        << newvoter[index].family_no << setw(20) << newvoter[index].Area.NA_constituencyno << setw(20) << newvoter[index].Area.PA_constituencyno
        << setw(30) << newvoter[index].Area.polling_station << endl;

    cout << "Data has been successfully written to the file." << endl;

    fout.close(); 
}
void input_voter_details(Voters& voter) {
    cout << "Enter Block Code of the voter: ";
    cin >> voter.Block_code;

    cout << "Enter Series Number of the family of voter: ";
    cin >> voter.series_no;

    cout << "Enter Family Number of the voter: ";
    cin >> voter.family_no;

    cout << "Enter the assigned NA Constituency Number to voter: ";
    cin >> voter.Area.NA_constituencyno;

    cout << "Enter the assigned PA Constituency Number to voter: ";
    cin >> voter.Area.PA_constituencyno;
    cin.ignore();
    cout << "Enter the allocated Polling Station: ";
    getline(cin, voter.Area.polling_station);
}