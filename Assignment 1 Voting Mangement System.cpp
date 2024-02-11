#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "MPAdata.h"
#include "MNAdata.h"
#include "Voters.h"
using namespace std;
void mainmenu() {
	cout << "*******VOTING MANAGEMENT SYSTEM*******" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << endl;
	cout << "1. National Assembly Candidates Data " << endl;
	cout << "2. Provintial Assembly Candidates Data " << endl;
	cout << "3. Voters Data " << endl;
	cout << "4. Exit" << endl;
	int choice;			

	do {
		cout << "Enter your choice" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			MNA_Menu();
			break;
		case 2:
		MPA_Menu();
			break;

		case 3:
			Voters_Menu();
			break;
		case 4:
			return;
		default:
			cout << "enter valid choice";
		}
	} while (choice != 4);
}


int main() {
	mainmenu();
}