#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

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

//stores requested rides
struct Request {
	string passengerName;
	string locStreetName;
	int locStreetNum;
	string locSuburb;
	string locCity;

	string destStreetName;
	int destStreetNum;
	string destSuburb;
	string destCity;
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

//base cost per kilometer
const int KILOMETER_RATE = 3;
const int TIME_RATE = 1;
const double GST = 0.15;

void passengerMenu(userPassenger passenger);
void driverMenu(userDriver driver);
void adminMenu();

//terms and conditions
void tAndC();

//user functions
void requestRide(userPassenger passenger);
void updatePayment(userPassenger passenger);
void tripCost();

//driver functions
void bankDetails(userDriver driver);
void tripBookings();
void enterJobDetails(int job);
void dayReport();

//admin functions
void income();
void userInfo();
void driverInfo();

bool LOGGED_IN = false;
loginType CURRENT_USER_ACCESS;
int CURRENT_USERID;
userDriver currentDriver;
userPassenger currentPassenger;


int main() {
menu_restart:
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
				adminMenu();
				break;
			case Driver:
				driverMenu(currentDriver);
				break;
			case Passenger:
				passengerMenu(currentPassenger);
				break;
			default:
				break;
			}

			LOGGED_IN = false;
			goto menu_restart;

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

		string arr[12];

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
					currentPassenger.acc_no = stoi(arr[0]);
					currentPassenger.email = arr[1];
					currentPassenger.password = arr[2];
					currentPassenger.f_name = arr[4];
					currentPassenger.l_name = arr[5];
					currentPassenger.age = arr[6];
					currentPassenger.card_details.card_no = arr[7];
					currentPassenger.card_details.card_xp = arr[8];
					currentPassenger.card_details.card_cvc = arr[9];
					currentPassenger.phone_number = arr[10];
					currentPassenger.address = arr[11];
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
		currentPassenger = passenger;
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

//**************************************************************************************************************
//**************************************************************************************************************

//menu for user passenger
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
			requestRide(passenger);
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

//menu for user driver
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
			bankDetails(driver);
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

//menu for user admin
void adminMenu() {
menu_restart:
	int menuType;
	bool loggedIn = true;

	while (loggedIn) {
		cout << LONG_LINE_BREAK << endl;
		cout << "\t\tMenu - Admin" << endl;
		cout << LONG_LINE_BREAK << endl;
		cout << "\t1. Trips and Total Income" << endl;
		cout << "\t2. User Information" << endl;
		cout << "\t3. Driver Information" << endl;
		cout << "\t4. View Terms & Conditions" << endl;
		cout << "\t5. Log Out" << endl;
		cout << "Enter Option: ";
		cin >> menuType;

		//checks user input from the menu screen
		switch (menuType) {
		case 1:
			income();
			break;
		case 2:
			userInfo();
			break;
		case 3:
			driverInfo();
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

//terms and conditions
void tAndC() {
	char agree;
	cout << LONG_LINE_BREAK << endl;
	cout << "Terms and Conditions" << endl;
	cout << LONG_LINE_BREAK << endl;

	cout << "1. afjbsdk*bskgbsgjgbksg\n";
	cout << "2. dfhsdujafsdgs\n";
	cout << "3. dsgihisgobonpnfsdbs\n";
	cout << "4. sdgbsbgoasdkgiw\n\n";

	//checks if the user agrees with the terms and conditions
	cout << "Do you agree to the terms and conditions above? (y/n)";
	cin >> agree;

	switch (agree) {
	case 'y':
		cout << "You agree" << endl;
		break;
	case 'n':
		cout << "You Disagree" << endl;
		break;
	default:
		cout << "You have to input either 'y' or 'n'" << endl;
		break;
	}
}

//displays if there is any jobs to take for the driver
void tripBookings() {
	cout << LONG_LINE_BREAK << endl;
	cout << "Current Jobs: " << endl;
	cout << LONG_LINE_BREAK << endl << endl;

	//reads 'Available_Rides' folder and displays all the txt files in it
	int jobs = 0;
	string path = "Available_Rides/";
	for (const auto& entry : fs::directory_iterator(path)) {
		ifstream infile;
		infile.open(entry.path());

		if (infile.is_open()) {
			jobs++;
			cout << "Job " << jobs << endl;
			cout << LONG_LINE_BREAK << endl;
			string tp;
			while (getline(infile, tp)) {
				cout << tp << endl;
			}
			infile.close();
		}
	}
	int whichJob;
	char takeOnlyJob;

	//checks what job the driver wants to take
	if (jobs == 0) {
		cout << "There are no jobs at the moment :(" << endl;
	}
	else if (jobs == 1) {
		cout << "There is 1 job available would you like to take it? (y/n) ";
		cin >> takeOnlyJob;
		switch (takeOnlyJob) {
		case 'y':
			enterJobDetails(1);
			break;
		case 'n':
			break;
		}
	}
	else {
		cout << "Which job would you like to take? (1-" << jobs << ")" << endl;
		cout << "(Enter '0' if you wish to return to the menu)" << endl;
		cin >> whichJob;
		if (whichJob == 0) {
			cout << endl;
		}
		else {
			enterJobDetails(whichJob);
		}
	}
}

//driver enters the job details and it gets put into a file
void enterJobDetails(int job) {
	int tripDist;
	int tripTime;
	int tripCost;

	cout << "Job " << job << " selected:" << endl;
	cout << "How far was the trip (kms): ";
	cin >> tripDist;
	cout << "How long did the trip take (mins): ";
	cin >> tripTime;

	tripCost = (tripDist * KILOMETER_RATE) + (tripTime * TIME_RATE);

	int loop = 1;
	ofstream outfile;

	//copys ride details to a new file in 'Completed Rides' and deletes ride request
	string path = "Available_Rides/";
	for (const auto& entry : fs::directory_iterator(path)) {
		if (loop == job) {
			ifstream infile;
			infile.open(entry.path());

			string fLine;
			getline(infile, fLine);
			string name = fLine + ".txt";

			outfile.open("Completed_Rides/" + name);
			outfile << fLine << endl;

			if (infile.is_open()) {
				string tp;
				while (getline(infile, tp)) {
					outfile << tp << endl;
				}
				infile.close();
				remove(entry.path());//removes the ride request as it has been completed
			}
			break;
		}
		else {
			loop++;
		}
	}
	outfile << "Trip Distance:\n" << tripDist << endl;
	outfile << "Time Taken:\n" << tripTime << endl;
	outfile << "Trip Cost:\n" << tripCost << endl;

	outfile.close();
}

//view and update bank details
void bankDetails(userDriver driver) {
	char askUserUpdate;

	cout << LONG_LINE_BREAK << endl;
	cout << "Update Bank Details" << endl;
	cout << LONG_LINE_BREAK << endl;

	cout << "Would you like to update your bank details? (y/n): ";
	cin >> askUserUpdate;

	switch (askUserUpdate) {
	case 'y':
		cout << "Enter bank number: ";
		cin >> driver.bank_number;
		//still needs the code to update the file
		break;
	case 'n':
		cout << "no";
		break;
	default:
		cout << "error";
		break;
	}
}

void dayReport() {
	cout << "Day Report of trips" << endl;
}

//user can request a ride
void requestRide(userPassenger passenger) {
	Request ride;

	cout << LONG_LINE_BREAK << endl;
	cout << "Request a ride" << endl;
	cout << LONG_LINE_BREAK << endl;

	cout << "Current Location:" << endl;
	cout << "Street Name: ";
	cin >> ride.locStreetName;
	cout << "Street Number: ";
	cin >> ride.locStreetNum;
	cout << "Suburb: ";
	cin >> ride.locSuburb;
	cout << "City: ";
	cin >> ride.locCity;

	cout << endl << "Destination:" << endl;
	cout << "Street Name: ";
	cin >> ride.destStreetName;
	cout << "Street Number: ";
	cin >> ride.destStreetNum;
	cout << "Suburb: ";
	cin >> ride.destSuburb;
	cout << "City: ";
	cin >> ride.destCity;
	cout << endl;

	string fileName = passenger.f_name + " " + passenger.l_name + ".txt";
	ride.passengerName = passenger.f_name + " " + passenger.l_name;

	//writes user input to file
	ofstream outfile;
	outfile.open("Available_Rides/" + fileName);
	outfile << ride.passengerName << endl << endl;
	outfile << "Current Location:" << endl;
	outfile << "Street Name:\n" << ride.locStreetName << endl;
	outfile << "Street Number:\n" << ride.locStreetNum << endl;
	outfile << "Suburb:\n" << ride.locSuburb << endl;
	outfile << "City:\n" << ride.locCity << endl << endl;

	outfile << "Destination:" << endl;
	outfile << "Street Name:\n" << ride.destStreetName << endl;
	outfile << "Street Number:\n" << ride.destStreetNum << endl;
	outfile << "Suburb:\n" << ride.destSuburb << endl;
	outfile << "City:\n" << ride.destCity << endl << endl;

	outfile.close();
}

//updates the user payment details
void updatePayment(userPassenger passenger) {
	char askUserUpdate;

	cout << LONG_LINE_BREAK << endl;
	cout << "Update Payment Type" << endl;
	cout << LONG_LINE_BREAK << endl;

	cout << "Would you like to update your card details? (y/n): ";
	cin >> askUserUpdate;

	switch (askUserUpdate) {
	case 'y':
		cout << "Enter card number: ";
		cin >> passenger.card_details.card_no;
		cout << "Enter card expiry: ";
		cin >> passenger.card_details.card_xp;
		cout << "Enter card cvc: ";
		cin >> passenger.card_details.card_cvc;

		//still needs the code to update the file
		break;
	case 'n':
		break;
	default:
		cout << "error";
		break;
	}
}

//displays trip cost fees
void tripCost() {
	cout << LONG_LINE_BREAK << endl;
	cout << "Trip Cost" << endl;
	cout << LONG_LINE_BREAK << endl;
	cout << "It costs $" << KILOMETER_RATE << " per kilometer and $" << TIME_RATE << " for every minute spent driving with us" << endl;
}

//displays all the past trips and income
void income() {
	cout << "Trips and Total Income" << endl;
	double totalIncome = 0.00;

	int trip = 0;
	string path = "Completed_Rides/";
	for (const auto& entry : fs::directory_iterator(path)) {
		ifstream infile;
		infile.open(entry.path());
		int line = 1;

		if (infile.is_open()) {
			trip++;
			cout << endl << "Trip: " << trip << endl;
			cout << LONG_LINE_BREAK << endl;
			cout << "Name: ";
			string tp;
			while (getline(infile, tp)) {
				cout << tp << endl;
				if (line == 28) {
					totalIncome += stoi(tp);

				}
				line++;
			}
			infile.close();
		}
	}
	double totalIncomeAfterTax = totalIncome - totalIncome * GST;
	cout << LONG_LINE_BREAK << endl;
	cout << "Toal Income: $" << totalIncome << endl;
	cout << "Toal Income After Tax: $" << totalIncomeAfterTax << endl;
}

void userInfo() {
	cout << "User Info" << endl;
}

void driverInfo() {
	cout << "Driver Info" << endl;
}