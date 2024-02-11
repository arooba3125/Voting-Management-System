#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int candidates_MNA = 100;

struct MNA {
    string constituency_no;
    long long int CNIC;
    string name;
    string party;
    string symbol;
};

void MNA_Menu();
void MNAadd_record(MNA newcandidate[], int& index);
void MNAview_record(MNA newcandidate[], const int& index);
void MNAsearch_record(MNA newcandidate[],const int& index);
void readfromfile(MNA newcandidate[], int& index);

void MNA_Menu() { 
    MNA newcandidate[candidates_MNA];
    int index = 0;
     readfromfile(newcandidate, index);
    cout << "***Welcome to Candidates of MNA***" << endl;
    cout << "------------------------------" << endl;
    cout << "1. Add MNA Candidate Record" << endl;
    cout << "2. View MNA Candidate Record" << endl;
    cout << "3. Search MNA Candidate Record" << endl;
    cout << "4. Back to Main Menu" << endl;
    int choice;
    do {
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            MNAadd_record(newcandidate, index);
            break;
        case 2:
            MNAview_record(newcandidate, index);
            break;
        case 3:
            MNAsearch_record(newcandidate, index);
            break;
        case 4:
            break;
        default:
            cout << "Enter a valid choice." << endl;
        }
    } while (choice != 4);
}

void MNAadd_record(MNA newcandidate[], int& index) {
    if (index < candidates_MNA) {
        cout << "Enter the National Assembly constituency number: ";
        cin >> newcandidate[index].constituency_no;
        cout << "Enter the CNIC of the candidate: ";
        cin >> newcandidate[index].CNIC;      
        cin.ignore(); // Clear newline character from the input buffer
        cout << "Enter the name of the candidate: ";
        getline(cin, newcandidate[index].name);
        cout << "Enter the name of party the candidate belongs to: ";
        getline(cin, newcandidate[index].party);
        cout << "Enter the sign of the party: ";
        getline(cin, newcandidate[index].symbol); // Use getline for reading the symbol

        ofstream fout("MNA_candidates.txt", ios::app);
        fout << newcandidate[index].constituency_no << setw(17) 
            << newcandidate[index].CNIC << setw(17) << newcandidate[index].name 
            << setw(17) << newcandidate[index].party << setw(17) << newcandidate[index].symbol << endl;
        fout.close();
        cout << "New MNA candidate added successfully!" << endl;
        cout << "Now number of candidates for MNA are " << index + 1 << endl; 
        index++;
    }
    else {
        cout << "Error: MNA Candidate array is full." << endl;
    }
}

void MNAview_record(MNA newcandidate[], const int& index) {
    ifstream fin("MNA_candidates.txt");
    try {
        if (!fin.is_open()) {
            throw runtime_error("Error opening the file for reading.");
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        return;
    }

    cout <<"Consituency No" << setw(17) <<"CNIC" << setw(17) << "Name" << setw(17) <<"Party" << setw(17) <<"Symbol" << endl;

    // Using a separate loop counter to iterate over the array elements
    for (int i = 0; i < index; i++) {

        cout << newcandidate[i].constituency_no << setw(17) << newcandidate[i].CNIC << setw(17) 
            << newcandidate[i].name << setw(17) << newcandidate[i].party << setw(17)
            << newcandidate[i].symbol << endl;

    }

    fin.close();
}


void MNAsearch_record(MNA newcandidate[],const int& index) {
    ifstream fin("MNA_candidates.txt");
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
}
void readfromfile(MNA newcandidate[], int& index) {
    ifstream fin;
    fin.open("MNA_candidates.txt");
    try {
        if (!fin.is_open()) {
            throw runtime_error("Error opening the file for reading.");
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        return;
    }
        while (fin >> newcandidate[index].constituency_no >> newcandidate[index].CNIC >>
            newcandidate[index].name >> newcandidate[index].party >> newcandidate[index].symbol)
 {
            index++;
        }

        fin.close();
        cout << "Data has been successfully read from 'MNA_data.txt'" << endl;
    }
   
