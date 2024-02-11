#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
const int candidates_MPA = 100;

struct MPA {
    string constituency_no;
    long long int CNIC;
    string name;
    string party;
    string symbol;
};

void MPA_Menu();
void MPAadd_record(MPA newcandidate[], int& index);
void MPAview_record(MPA newcandidate[], const int& index);
void MPAsearch_record(MPA newcandidate[],const int& index);
void readfromfilepa(MPA newcandidate[], int& index);

void MPA_Menu() {
    MPA newcandidate[candidates_MPA];
    int index = 0;
    readfromfilepa(newcandidate, index);
    cout << "***Welcome to Candidates of MPA***" << endl;
    cout << "------------------------------" << endl;
    cout << "1. Add MPA Candidate Record" << endl;
    cout << "2. View MPA Candidate Record" << endl;
    cout << "3. Search MPA Candidate Record" << endl;
    cout << "4. Back to Main Menu" << endl;

    int choice;
    do {
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            MPAadd_record(newcandidate, index);
            break;
        case 2:
            MPAview_record(newcandidate, index);
            break;
        case 3:
            MPAsearch_record(newcandidate, index);
            break;
        case 4:
            break;
        default:
            cout << "Enter a valid choice." << endl;
        }
    } while (choice != 4);
}

void MPAadd_record(MPA newcandidate[], int& index) {
    if (index < candidates_MPA) {
        cout << "Enter the Provintial Assembly constituency number: ";
        cin >> newcandidate[index].constituency_no;
        cout << "Enter the CNIC of the candidate: ";
        cin >> newcandidate[index].CNIC;
        cin.ignore(); // Clear newline character from the input buffer
        cout << "Enter the name of the candidate: ";
        getline(cin, newcandidate[index].name);
        cout << "Enter the name of party the candidate belongs to: ";
        getline(cin, newcandidate[index].party);
        cout << "Enter the sign of the party: ";
        cin >> newcandidate[index].symbol;

        ofstream fout("MPA_candidates.txt", ios::app);
        fout << newcandidate[index].constituency_no << setw(17) << newcandidate[index].CNIC << setw(17) 
            << newcandidate[index].name << setw(17) << newcandidate[index].party << setw(17) 
            << newcandidate[index].symbol << endl;
        fout.close();
        cout << "New MPA candidate added successfully!" << endl;
        cout << "Now number of candidates for MPA are " << index << endl;
        index++;
    }
    else {
        cout << "Error: MPA Candidate array is full." << endl;
    }
}
void MPAview_record(MPA newcandidate[],const int& index) {
    ifstream fin("MPA_candidates.txt");
    try {
        if (!fin.is_open()) {
            throw runtime_error("Error opening the file for reading.");
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        return;
    }

    cout << "Consituency No" << setw(17) << "CNIC" << setw(17) 
        << "Name" << setw(17) << "Party" << setw(17) << "Symbol" << endl;

    // Use a separate loop counter to iterate over the array elements
    for (int i = 0; i < index; i++) {
        cout << newcandidate[i].constituency_no << setw(17) << newcandidate[i].CNIC << setw(17)
            << newcandidate[i].name << setw(17) << newcandidate[i].party << setw(17)
            << newcandidate[i].symbol << endl;
    }

    fin.close();
}

void MPAsearch_record(MPA newcandidate[], const int& index) {
    ifstream fin("MPA_candidates.txt");
    try {
        if (!fin.is_open()) {
            throw runtime_error("Error opening the file for reading.");
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        return;
    }
    string searchcandidates;
    bool found = false;
    cout << "Enter the constituency number of which you want to check the candidates: ";
    cin >> searchcandidates;
    cout << "Constituency Number\tCNIC\tName\tParty\tSymbol" << endl;
    // Using a separate loop counter to iterate over the array elements
    for (int i = 0; i < index; i++) {
        if (newcandidate[i].constituency_no == searchcandidates) {
            found = true;  
            cout << newcandidate[i].constituency_no << setw(17) << newcandidate[i].CNIC << setw(17)
                << newcandidate[i].name << setw(17) << newcandidate[i].party << setw(17)
                << newcandidate[i].symbol << endl;
        }
    }
    if (!found) {
        cout << "Record not found for constituency number: " << searchcandidates << endl;
    }
    fin.close();
}void readfromfilepa(MPA newcandidate[], int& index) {
    ifstream fin;
    fin.open("MPA_candidates.txt");

    try {
        if (!fin.is_open()) {
            throw runtime_error("File  does not exist.");
        } 
    }
    catch (runtime_error& e) {
        cout << "Error: " << e.what() << endl;
        return;
    }
        while (fin >> newcandidate[index].constituency_no >> newcandidate[index].CNIC >>
            newcandidate[index].name >> newcandidate[index].party >> newcandidate[index].symbol)
        {
            index++;
        }

        fin.close();
        cout << "Data has been successfully read from 'MPA_data.txt'" << endl;
    }
   
