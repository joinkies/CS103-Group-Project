#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Defining some common formatting elements
#define LONG_LINE_BREAK "***********************************************************"
#define LINE_BREAK "*****************************"

enum loginType { Admin, Driver, Passenger };

enum carType { Van = 1, Hybrid, Electric, Petrol, Diesel };

struct cc {
	int card_no;
	int card_xp;
	int card_cvc;
};

// User struct holds all the relevant info the user currently logged in
struct userPassenger {
	int acc_no;
	string f_name;
	string l_name;
	int age;
	cc card_details;
	int phone_number;
	string address;
	string email;
	string password;
	loginType user_type = Passenger;

	userPassenger() {
		acc_no = 0;
		f_name = "John";
		l_name = "Smith";
		age = 18;
		card_details.card_no = 0000000000000000;
		card_details.card_xp = 0125;
		card_details.card_cvc = 001;
		phone_number = 0000000000;
		address = "142 Wallaby Way";
		email = "N/A";
		password = "abc123";
	}
};

struct userDriver {
	int acc_no;
	string f_name;
	string l_name;
	int age;
	int phone_number;
	string address;
	int bank_number;
	string license_number;
	int driving_exp;
	carType car_type;
	int car_age;
	float kms_travelled;
	loginType user_type = Driver;
	string email;
	string password;

	userDriver() {
		acc_no = 0;
		f_name = "John";
		l_name = "Smith";
		age = 21;
		phone_number = 0000000000000000;
		address = "142 Wallaby Way";
		bank_number = 0000000000000000;
		license_number = "idk";
		driving_exp = 2;
		car_type = Hybrid;
		car_age = 1;
		kms_travelled = 0.0;
		email = "N/A";
		password = "abc123";
	}
};

bool registration(loginType user_type);
bool login(loginType user_type);
string help(int help_where);
void logOrReg(loginType user_type);
int getUserAmount();
//base cost per kilometer
const int KILOMETER_RATE = 3;

//Functions Jack Added:
//void menu(loginType user_type, userPassenger passenger);
void passengerMenu(userPassenger passenger);
void driverMenu(userDriver driver);
void adminMenu();
void tAndC();

//user functions
void requestRide();
void updatePayment(userPassenger passenger);
void tripCost();

//driver functions
void bankDetails();
void tripBookings();
void dayReport();

//admin functions
void income();
void userInfo();
void driverInfo();

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
		cout << "How many years of driving experience do you have in years: ";
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
			<< driver.car_type << ','
			<< driver.car_age << endl;

		return_value = true;
		CURRENT_USER_ACCESS = Driver;
		driverMenu(driver);
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
		cout << "Card number: ";
		cin >> passenger.card_details.card_no;
		cout << "Card expiry date (MMYY): ";
		cin >> passenger.card_details.card_xp;
		cout << "Card CVC number: ";
		cin >> passenger.card_details.card_cvc;
		cout << "Enter your phone number: ";
		cin >> passenger.phone_number;
		cout << "Provide your address: ";
		cin >> passenger.address;
		cout << "Enter e-mail address: ";
		cin >> passenger.email;
		cout << "Provide a strong password: ";
		cin >> passenger.password;
		file << users_in_file << ','
			<< "Passenger" << ','
			<< passenger.f_name << ','
			<< passenger.l_name << ','
			<< passenger.age << ','
			<< passenger.email << ','
			<< passenger.card_details.card_no << ','
			<< passenger.card_details.card_xp << ','
			<< passenger.card_details.card_cvc << ','
			<< passenger.phone_number << ','
			<< passenger.address << ','
			<< passenger.password << endl;
		return_value = true;
		CURRENT_USER_ACCESS = Passenger;
		passengerMenu(passenger);
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

void passengerMenu(userPassenger passenger) {
menu_restart:
	int menuType;
	bool loggedIn = true;

	while (loggedIn) {
		cout << LONG_LINE_BREAK << endl;
		cout << "\t\tMenu - Passenger" << endl;
		cout << LONG_LINE_BREAK << endl;
		cout << "\t1. Request a Ride" << endl;
		cout << "\t2. Update Payment Method" << endl;
		cout << "\t3. Trip Cost per Kilometer" << endl;
		cout << "\t4. View Terms & Conditions" << endl;
		cout << "\t5. Log Out" << endl;
		cout << "Enter Option: ";
		cin >> menuType;

		//checks user input from the menu screen
		switch (menuType) {
		case 1:
			requestRide();
			break;
		case 2:
			updatePayment(passenger);
			break;
		case 3:
			tripCost();
			break;
		case 4:
			tAndC();
			break;
		case 5:
			cout << "Logout" << endl;
			loggedIn = false;
			break;
		default:
			cout << "Error" << endl;
			goto menu_restart;
			break;
		}
	}
}

void driverMenu(userDriver driver) {
menu_restart:
	int menuType;
	bool loggedIn = true;

	while (loggedIn) {
		cout << LONG_LINE_BREAK << endl;
		cout << "\t\tMenu - Driver" << endl;
		cout << LONG_LINE_BREAK << endl;
		cout << "\t1. View Trip Bookings" << endl;
		cout << "\t2. View Bank Details" << endl;
		cout << "\t3. Day Report of Trips" << endl;
		cout << "\t4. View Terms & Conditions" << endl;
		cout << "\t5. Log Out" << endl;
		cout << "Enter Option: ";
		cin >> menuType;

		//checks user input from the menu screen
		switch (menuType) {
		case 1:
			tripBookings();
			break;
		case 2:
			bankDetails();
			break;
		case 3:
			dayReport();
			break;
		case 4:
			tAndC();
			break;
		case 5:
			cout << "Logout" << endl;
			loggedIn = false;
			break;
		default:
			cout << "Error" << endl;
			goto menu_restart;
			break;
		}
	}
}

void adminMenu() {
	cout << "Admin Menu";
}

void tAndC() {
	cout << "Terms and Conditions" << endl;
}

void tripBookings() {
	cout << "Trip Bookings" << endl;
}

void bankDetails() {
	cout << "Bank Details" << endl;
}

void dayReport() {
	cout << "Day Report" << endl;
}

void requestRide() {
	//variables for passengers current location
	string locStreetName;
	int locStreetNum;
	string locSuburb;
	string locCity;

	//variables for passengers destination
	string destStreetName;
	int destStreetNum;
	string destSuburb;
	string destCity;

	cout << LONG_LINE_BREAK << endl;
	cout << "Request a ride" << endl;
	cout << LONG_LINE_BREAK << endl;

	cout << "Current Location:" << endl;
	cout << "Street Name: ";
	cin >> locStreetName;
	cout << "Street Number: ";
	cin >> locStreetNum;
	cout << "Suburb: ";
	cin >> locSuburb;
	cout << "City: ";
	cin >> locCity;

	cout << endl << "Destination:" << endl;
	cout << "Street Name: ";
	cin >> destStreetName;
	cout << "Street Number: ";
	cin >> destStreetNum;
	cout << "Suburb: ";
	cin >> destSuburb;
	cout << "City: ";
	cin >> destCity;
	cout << endl;
}

void updatePayment(userPassenger passenger) {
	cout << LONG_LINE_BREAK << endl;
	cout << "Update Payment Type" << endl;
	cout << LONG_LINE_BREAK << endl;
}

void tripCost() {
	cout << LONG_LINE_BREAK << endl;
	cout << "Trip Cost" << endl;
	cout << LONG_LINE_BREAK << endl;
	cout << "It costs $" << KILOMETER_RATE << " per kilometer driving with us!" << endl;
}

void income() {
	cout << "Trips and Total Income" << endl;
}

void userInfo() {
	cout << "User Info" << endl;
}

void driverInfo() {
	cout << "Driver Info" << endl;
}