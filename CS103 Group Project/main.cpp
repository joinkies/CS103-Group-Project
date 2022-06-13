#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Defining some common formatting elements
#define LONG_LINE_BREAK "***********************************************************"
#define LINE_BREAK "*****************************"

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

	userPassenger(int an = 0, int a = 0, string fn = "John", string ln = "Smith", paymentType pt = Cash, string e = "N/A", string p = "abc123") {
		acc_no = an;
		f_name = fn;
		l_name = ln;
		age = a;
		payment = pt;
		email = e;
		password = p;
	}
};

struct userDriver {
	int acc_no;
	string f_name;
	string l_name;
	int age;
	paymentType driver_pay;
	float kms_travelled;
	loginType user_type = Driver;
};

bool registration(loginType user_type);
bool login(loginType user_type);
string help(int help_where);
void logOrReg(loginType user_type);
int getUserAmount();
/*
void transLog();
void lostFound();
void complaints();
void updateUser();
*/
// When the program starts, the user is not logged in.
bool LOGGED_IN = false;
loginType CURRENT_USER_ACCESS;


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
					switch (stoi(menu_choice)) {
					case 1:
						logOrReg(Driver);
						break;
					case 2:
						logOrReg(Passenger);
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
			cout << "\n\tSuccessfule login\n\n";

		}
	} // End of while loop

	return 0;
}

void logOrReg(loginType user_type) {
	login_restart:
		string log_reg;
		cout << "  1. Log in\n  2. Register\n Your choice: ";
		cin >> log_reg;
		try {
			if (log_reg == "help") {
				cout << help(2);
				goto login_restart;
			}
			else if (stoi(log_reg) == 1) {
				LOGGED_IN = login(user_type);
			}
			else if (stoi(log_reg) == 2) {
				LOGGED_IN = registration(user_type);
			}
			else {
				cout << "\n You must select 1, 2 or type in help!\n\n";
				goto login_restart;
			}
		}
		catch (const invalid_argument) {
			cout << "\n Type 1, 2 or 'help'\n\n";
			goto login_restart;
		}
}

bool login(loginType user_type) {
	cout << "\nLogin\n\n";
	return false;
}

int getUserAmount() {
	ifstream countfile;
	countfile.open("users.csv");

	int users = 0;
	string line;
	while (getline(countfile, line)) {
		users++;
	}

	countfile.close();

	return users;
}

bool registration(loginType user_type) {	
	int payment_type;
	bool return_value = false;

	int users_in_file = getUserAmount();

	ofstream file;
	file.open("users.csv", ios::app);

	switch (user_type) {
	case Driver: {
		userDriver driver;
		cout << "\nDriver Reg\n" << LINE_BREAK << endl;
		return_value = true;
		break;
	}
	case Passenger:
		userPassenger passenger;
		cout << "\nPassenger Registration\n" << LINE_BREAK << endl;
		cout << "Enter your first name: ";
		cin >> passenger.f_name;
		cout << "Enter last name: ";
		cin >> passenger.l_name;
		cout << "Enter your age: ";
		cin >> passenger.age;
		cout << "Enter e-mail address: ";
		cin >> passenger.email;
		cout << "Provide a strong password: ";
		cin >> passenger.password;
		cout << "1. Cash\n2. Card\n Your choice?: ";
		cin >> payment_type;
		passenger.payment = paymentType(payment_type--);
		file << users_in_file << ',' << "Passenger" << ',' << passenger.f_name << ',' << passenger.l_name << ',' << passenger.age << ',' << passenger.email << ',' << passenger.payment << ',' << passenger.password << endl;
		
		return_value = true;
		break;
	}

	file.close();

	return return_value;
} // End of registration function

string help(int help_where) {
	switch (help_where) {
	case 1:
		return "\n  Enter the number corresponding\n  to your desired action\n\n";
	case 2:
		return "\n  Select whether you want to login or register\n  as a new user, then provide all the neccessary information.\n\n";
	default:
		return "\n  Help not found\n\n";
	}
}