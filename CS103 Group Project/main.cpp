#include <iostream>
#include <string>
using namespace std;

#define LONG_LINE_BREAK "***********************************************************"
#define LINE_BREAK "*****************************";

struct NewUser {
	int acc_no;
	string name;
	int age;
	string payment;
	string 
};

void userReg();
void driverReg();
void transLog();
void lostFound();
void complaints();
void help(int help_where);
void updateUser();


int main() {
	bool program_running = true;
	
	cout << LONG_LINE_BREAK << endl;

	while (program_running) {
		string menu_choice;

		cout << "\t\tTaxi Program\n" << LONG_LINE_BREAK << endl;
		cout << "\t1. Register user\n\t2. Register drive\n\t3. View/edit transaction logs\n\t4. Lost & found\n";
		cout << "\t5. Complaints\n\t6. Update user information\n\t9. Exit Program\n" << LONG_LINE_BREAK << endl;
		cout << "  Or Type 'help' for help with the menu";
		cout << "  What would you like to do?: ";
		cin >> menu_choice;
		try {
			if (menu_choice == "help") {
				help(1);
			}
			else if (stoi(menu_choice) <= 8 && stoi(menu_choice) >= 1) {
				switch (stoi(menu_choice))
				{
				case 1:
					userReg();
					break;
				case 8:
					program_running = false;
				default:
					break;
				}
			}
			else throw (stoi(menu_choice));
		}
		catch (int menu_num) { // Catches user if the options selected doesn't exist
			cout << "Menu choice must be between 1 & 8\n";
		}
		catch (const invalid_argument) { // Catches any word that isn't "help"
			cout << "You must enter a number between 1 and 8 for the main functions, else type 'help'\n";
		}
	}
	return 0;
}

void userReg() {
	cout << "\n\nUser Registration\n" << LINE_BREAK;
	cout << "\n"
}

void help(int help_where) {
	switch (help_where)	{
	case 1:
		cout << "How are you stuck and need help in the main menu?\n";
	default:
		break;
	}
}