#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Defining some common formatting elements
#define LONG_LINE_BREAK "***********************************************************"
#define LINE_BREAK "*****************************"

// Established the types of people that can be logged in,
// so the program knows which to show
enum loginType { Admin, Driver, Passenger };

enum carType { Van = 1, Hybrid, Electric, Petrol, Diesel };

struct cc {
	string card_no,
		card_xp,
		card_cvc;
};

// User struct holds all the relevant info the user currently logged in
struct userPassenger {
	int acc_no;
	string f_name,
		l_name,
		age,
		phone_number,
		address,
		email,
		password;
	cc card_details;
	loginType user_type = Passenger;

	userPassenger() {
		acc_no = 0;
		f_name = "John";
		l_name = "Smith";
		age = 18;
		card_details.card_no = "0000000000000000";
		card_details.card_xp = "0125";
		card_details.card_cvc = "001";
		phone_number = "0000000000";
		address = "142 Wallaby Way";
		email = "N/A";
		password = "abc123";
	}
};

struct userDriver {
	int acc_no;
	string f_name,
		l_name,
		age,
		phone_number,
		address,
		bank_number,
		license_number,
		driving_exp,
		car_type,
		car_age,
		kms_travelled,
		email,
		password;
	loginType user_type = Driver;

	userDriver() {
		acc_no = 0;
		f_name = "John";
		l_name = "Smith";
		age = "21";
		phone_number = "0000000000000000";
		address = "142 Wallaby Way";
		bank_number = "0000000000000000";
		license_number = "idk";
		driving_exp = "2";
		car_type = Hybrid;
		car_age = "1";
		kms_travelled = "0.0";
		email = "N/A";
		password = "abc123";
	}
};

struct userAdmin {
	int id;
	string email;
	string password;
	loginType user_type = Admin;
};

bool registration(loginType user_type);
bool login();
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
int CURRENT_USERID;
userDriver currentDriver;
userPassenger currentPassneger;


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
						login();
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
			switch (CURRENT_USER_ACCESS)
			{
			case Admin:
				break;
			case Driver:
				break;
			case Passenger:
				cout << currentPassneger.f_name << endl << currentPassneger.l_name;
				break;
			default:
				break;
			}

			cout << "\n\tSuccessfull login\n\n";
			cout << "Logged in = " << LOGGED_IN << endl;
			cout << "Current user access = " << CURRENT_USER_ACCESS << endl;
			
			return 0;
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
				LOGGED_IN = login();
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

bool login() {
	cout << "\nLogin\n\n";

	ifstream login_from_file;
	login_from_file.open("users.csv");

	string line, email, password;

	cout << "Enter your email: ";
	cin >> email;
	cout << "Enter you password: ";
	cin >> password;

	while (login_from_file) {
		getline(login_from_file, line);

		string arr[11];

		stringstream ss(line);
		int i = 0;
		while (ss.good()) {
			string a;
			getline(ss, a, ',');
			arr[i] = a;
			i++;
		}
		if (arr[1] == email) {
			if (arr[2] == password) {
				cout << "\nSuccessful login\n\n";
				if (arr[3] == "Driver") {
					CURRENT_USER_ACCESS = Driver;
					currentDriver.acc_no = stoi(arr[0]);
					currentDriver.email = arr[1];
					currentDriver.password = arr[2];
					currentDriver.f_name = arr[4];
					currentDriver.l_name = arr[5];
					currentDriver.age = arr[6];
					currentDriver.bank_number = arr[7];
					currentDriver.license_number = arr[8];
					currentDriver.driving_exp = arr[9];
					currentDriver.car_type = arr[10];
					currentDriver.car_age = arr[11];
				}
				else if (arr[3] == "Passenger") {
					CURRENT_USER_ACCESS = Passenger;
					currentPassneger.acc_no = stoi(arr[0]);
					currentPassneger.email = arr[1];
					currentPassneger.password = arr[2];
					currentPassneger.f_name = arr[4];
					currentPassneger.l_name = arr[5];
					currentPassneger.age = arr[6];
					currentPassneger.card_details.card_no = arr[7];
					currentPassneger.card_details.card_xp = arr[8];
					currentPassneger.card_details.card_cvc = arr[9];
					currentPassneger.phone_number = arr[10];
					currentPassneger.address = arr[11];
				}
				else {
					CURRENT_USER_ACCESS = Admin;
				}
				return true;
			}
			break;
		}
	}
	cout << "Account not found!\n\n";
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
	bool return_value = false;

	int users_in_file = getUserAmount();

	ofstream file;
	file.open("users.csv", ios::app);

	switch (user_type) {
	case Driver: {
		userDriver driver;
		cout << "\nDriver Reg\n" << LINE_BREAK << endl;
		cout << "\nEnter your first name: ";
		cin >> driver.f_name;
		cout << "Enter last name: ";
		cin >> driver.l_name;
		cout << "Enter your age: ";
		cin >> driver.age;
		cout << "Enter your bank number: ";
		cin >> driver.bank_number;
		cout << "Enter your license number: ";
		cin >> driver.license_number;
		cout << "How many years of driving experience do you have: ";
		cin >> driver.driving_exp;
		// enum carType { Van = 1, Hybrid, Electric, Petrol, Diesel };
		cout << "What is your car type?\n 1. Van\n 2. Hybrid\n 3. Electric\n 4. Petrol\n 5. Diesel\nEnter the corrospondiong number: ";
		int car_type;
		cin >> car_type;
		cout << "How old is your car in years: ";
		cin >> driver.car_age;
		cout << "Enter your email: ";
		cin >> driver.email;
		cout << "Enter a strong password: ";
		cin >> driver.password;
		file << users_in_file << ','
			<< driver.email << ','
			<< driver.password << ','
			<< "Driver" << ','
			<< driver.f_name << ','
			<< driver.l_name << ','
			<< driver.age << ','
			<< driver.bank_number << ','
			<< driver.license_number << ','
			<< driver.driving_exp << ','
			<< car_type << ','
			<< driver.car_age << endl;
			
		return_value = true;
		CURRENT_USER_ACCESS = Driver;
		currentDriver = driver;
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
		cout << "Enter your card details\n";
		cin.ignore();
		cout << "Card number: ";
		getline(cin, passenger.card_details.card_no);
		cout << "Card expiry date (MM/YY): ";
		cin >> passenger.card_details.card_xp;
		cout << "Card CVC number: ";
		cin >> passenger.card_details.card_cvc;
		cin.ignore();
		cout << "Enter your phone number: ";
		getline(cin, passenger.phone_number);
		cin.ignore();
		cout << "Provide your address: ";
		getline(cin, passenger.address);
		cout << "Enter e-mail address: ";
		cin >> passenger.email;
		cout << "Provide a strong password: ";
		cin >> passenger.password;
		file << users_in_file << ','
			<< passenger.email << ','
			<< passenger.password << ','
			<< "Passenger" << ','
			<< passenger.f_name << ','
			<< passenger.l_name << ','
			<< passenger.age << ','
			<< passenger.card_details.card_no << ','
			<< passenger.card_details.card_xp << ','
			<< passenger.card_details.card_cvc << ','
			<< passenger.phone_number << ','
			<< passenger.address << endl;
		return_value = true;
		CURRENT_USER_ACCESS = Passenger;
		currentPassneger = passenger;
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