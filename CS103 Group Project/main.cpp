#include <iostream>
using namespace std;

<<<<<<< Updated upstream
int main() {

=======
#define LONG_LINE_BREAK "***********************************************************"
#define LINE_BREAK "*****************************";

bool LOGGED_IN = false;

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
		cout << "\t5. Complaints\n\t6. Update user information\n\t8. Exit Program\n" << LONG_LINE_BREAK << endl;
		cout << "  Or Type 'help' for help with the menu";
		cout << "  What would you like to do?: ";
		cin >> menu_choice;
		try {
			if (menu_choice == "help") {
				cout << "help\n";
			}
			else if (stoi(menu_choice) <= 8 && stoi(menu_choice) >= 1) {
				switch (stoi(menu_choice))
				{
				case 1:
					cout << "user reg\n";
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
>>>>>>> Stashed changes
}