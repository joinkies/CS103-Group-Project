#include <iostream>
#include <string>
using namespace std;

#define LONG_LINE_BREAK "***********************************************************"
#define LINE_BREAK "*****************************";

bool LOGGED_IN = false;
enum UserStatus { Admin, Passenger, Driver };
enum Payment { Card, Cash };
enum CarType { Hybrid, Petrol, Electric, Diesel };

struct User {
	string fName;
	string lName;
	string DoB;
	Payment pay;
	UserStatus userType;
	int phNum;
	string address;
	string password;
	string userName;
	string email;
};

struct Driver {
	string fName;
	string lName;
	string DoB;
	UserStatus userType;
	string licenseNum;
	int exp;
	CarType carType;
	int carYear;
	int bankNo;
};

void transLog();
void lostFound();
void complaints();
void help(int help_where);
void updateUser();

string userGenericLogin();
string adminLogin();
string userGeniricReg();


int main() {
	bool program_running = true;
	
	cout << LONG_LINE_BREAK << endl;

	while (program_running) {
		if (LOGGED_IN) {
			/*
			Run program as the user will see it until they log out,
			else they go through the login procress
			*/
			try {
			}
			catch (int menu_num) { // Catches user if the options selected doesn't exist
				cout << "Menu choice must be between 1 & 8\n";
			}
			catch (const invalid_argument) { // Catches any word that isn't "help"
				cout << "You must enter a number between 1 and 8 for the main functions, else type 'help'\n";
			}
		}
		else {
			// Holds the temp user status for 
			string temp_user_status;

			cout << "\t\tTaxi Program Login\n" << LONG_LINE_BREAK << endl;
			cout << "  Are you a:\n\tdriver\n\tpassenger\n\tor admin\n";
			cout << "  Type 'help' for additional info\n";
			cout << "  What would you like to do?: ";
			cin >> temp_user_status;
			
			if (temp_user_status == "help") {
				cout << "Type out your response as a word in lowercase,\nAs listed in the options\n";
			}
			else if (temp_user_status == "passenger") {
				cout << "user\n";
			}
			else if (temp_user_status == "admin") {
				cout << "admin\n";
			}
			else if (temp_user_status == "driver") {
				cout << "driver\n";
			}
			else {
				cout << "Type out your response, make sure spelling is correct and lowercase\n";
			}
		}		
	}
	return 0;
}