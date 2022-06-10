#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Defining some common formatting elements
#define LONG_LINE_BREAK "***********************************************************"
#define LINE_BREAK "*****************************"

// When the program starts, the user is not logged in.
bool LOGGED_IN = false;

// Established the types of people that can be logged in,
// so the program knows which to show
enum loginType { Admin, Driver, Passenger };
// Users will have two options for payment type,
// For the sake of consistency, their two options held in enum
enum paymentType { Cash, Card };

// User struct holds all the relevant info the user currently logged in
struct userPassenger {
	int acc_no;
	string f_name;
	string l_name;
	int age;
	paymentType payment;
	string email;
	string password;
	loginType user_type = Passenger;
};

struct userDriver {
	int acc_no;
	string f_name;
	string l_name;
	int age;
	paymentType driver_pay;

	loginType user_type = Driver;
};

void registration(loginType user_type);
void login(loginType user_type);
void transLog();
void lostFound();
void complaints();
string help(int help_where);
void updateUser();


int main() {
	bool program_running = true;
	
	cout << LONG_LINE_BREAK << endl;

	while (program_running) { // Main program loop
		if (!LOGGED_IN) { // Menu when user isn't logged in
			string menu_choice;

			cout << "\t\tTaxi Program\n" << LONG_LINE_BREAK << endl;
			cout << "\t1. Driver \n\t2. Passenger\n\t3. Admin\n\t4. Exit Program\n" << LONG_LINE_BREAK << endl;
			cout << "  Or Type 'help' for help with the menu";
			cout << "  What would you like to do?: ";
			cin >> menu_choice;
			try {
				if (menu_choice == "help") {
					cout << help(1);
				}
				else if (stoi(menu_choice) <= 4 && stoi(menu_choice) >= 1) {
					int log_reg;
					switch (stoi(menu_choice)) {
					case 1:
						cout << "  1. Log in\n  2. Register\n Your choice: ";
						cin >> log_reg;
						if (log_reg == 1) {
							login(Driver);
						}
						else if (log_reg == 2) {
							registration(Driver);
						}
						else {
							cout << "\n You must select 1 or 2!\n\n";
						}
						break;
					case 2:
						cout << "  1. Log in\n  2. Register\n Your choice: ";
						cin >> log_reg;
						if (log_reg == 1) {
							login(Passenger);
						}
						else if (log_reg == 2) {
							registration(Passenger);
						}
						else {
							cout << "\n You must select 1 or 2!\n\n";
						}
						break;
					case 3:
						login(Admin);
						break;
					case 4:
						program_running = false;
						break;
					} // End of switch case
				} // End of else if (menu_choice) {}
				else throw (stoi(menu_choice));
			} // End of try {}
			catch (int menu_choice) { // Catches user if the options selected doesn't exist
				cout << "\n  Menu choice must be between 1 & 4\n\n";
			}
			catch (const invalid_argument) { // Catches any word that isn't "help"
				cout << "\n  You must enter a number between 1 and 4 for the main functions, else type 'help'\n\n";
			}
		} // End of if (!LOGGED_IN) {}
		else { // Menu when the user is logged in

		}
	} // End of while loop

	return 0;
}

void login(loginType user_type) {
	cout << "\nLogin\n\n";
}

void registration(loginType user_type) {
	cout << "\n\nUser Registration\n" << LINE_BREAK << endl;
	
	int payment_type, new_user_type;

	fstream file;

	file.open("users.csv", ios::out | ios::trunc);

	switch (user_type) {
	case Driver: {
		userDriver driver;
		cout << "\nDriver Reg\n" << LINE_BREAK << endl;
		break;
	}
	case Passenger:
		userPassenger passenger;
		cout << "\nPassenger Registration\n" << LINE_BREAK << endl;
		cout << "Enter your first name: ";
		getline(cin, passenger.f_name);
		cin.ignore();
		cout << "Enter last name: ";
		getline(cin, passenger.l_name);
		cin.ignore();
		cout << "Enter your age: ";
		cin >> passenger.age;
		cout << "Enter e-mail address: ";
		cin >> passenger.email;
		cout << "Provide a strong password: ";
		cin >> passenger.password;
		cout << "1. Cash\n2. Card\nTo pay drivers? ";
		int pay_driver;

		break;
	}
}

string help(int help_where) {
	switch (help_where) {
	case 1:
		return "\n  Enter the number corresponding\n  to your desired action\n\n";
		break;
	}
}