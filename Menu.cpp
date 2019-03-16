#include "Menu.h"
#include "Student.h"

void ShowHelp_General() {
	cout << "[SHARED COMMANDS]\n"
		<< "logout : Log out\n"
		<< "-      : Log out\n"
		<< "quit   : Exit\n"
		<< "cls    : Clear the screen\n"
		<< "info   : Show current user information (not available for admins)\n"
		<< "help   : Show this command list and other user-specific commands\n"
		<< "passwd : Change password\n"
		<< "\n";
}

void ShowHelp_Student() {
	cout << "\n[STUDENT COMMANDS]\n"
		<< "checkin : Check-in\n"
		<< "listck  : View check-in result\n"
		<< "sched  : View schedules\n"
		<< "score  : View scoreboard result\n"
		<< "\n";
}

void ShowHelp_Admin() {
	cout << "\n[ADMIN COMMANDS]\n"
		<< "STUDENTS AND CLASSES\n"
		<< "timport : Import students of a class (from a CSV file)\n"
		<< "tload   : Load a class from the database\n"
		<< "tclass  : Show current working class\n"
		<< "tlookup : Find information of a student\n"
		<< "tadd    : Add a student to a class\n"
		<< "tedit   : Edit a student\n"
		<< "tdelete : Remove a student\n"
		<< "tlist   : View list of students in a class\n"
		<< "\n";
}

void Menu_Student(const string & ID) {
	string StudentID = ID.substr(0, ID.find_first_of('@'));
	string ClassID = ID.substr(ID.find_first_of('@') + 1);

	// potentially dangerous?
	StudentList CurrentList;
	LoadStudents(CurrentList, ClassID);

	// Start-up script
	ShowInfo(CurrentList, ClassID, StudentID);
	cout << "\n";
	ShowHelp_General();
	ShowHelp_Student();
	// End of start-up script

	// Intepreter
	do {
		string c;
		cout << "(" << ID << ")> ";
		getline(cin, c);

		// case-insensitivity
		for (size_t i = 0; i < c.length(); i++)
			c[i] = ::tolower(c[i]);

		if (c == "logout" || c == "-") { break; }
		else if (c == "quit") { exit(EXIT_SUCCESS); }
		else if (c == "cls") { system("CLS"); }
		else if (c == "info") { ShowInfo(CurrentList, ClassID, StudentID); }
		else if (c == "help") { ShowHelp_General(); ShowHelp_Student(); }
		
		else if (c == "passwd") {
			string Password_New, Password_New_Re;
			cout << "Enter new password: ";
			Password_New = GetPassword();
			cout << "\n";
			cout << "Re-enter new password: ";
			Password_New_Re = GetPassword();
			cout << "\n";

			if (Password_New != Password_New_Re) {
				cout << "Passwords do not match. Operation aborted.\n";
			}
			else {
				ChangePassword(ID, AC_STUDENT, Password_New);
			}
		}

		//else if (c == "checkin") { }
		//else if (c == "listck") { }
		//else if (c == "sched") { }
		//else if (c == "score") { }

		else { cout << "Invalid command.\n"; }
		cout << "\n";
	} while (1);
}

void Menu_Admin(const string & ID) {
	StudentList CurrentList;
	string ClassID;

	// Start-up script
	ShowHelp_General();
	ShowHelp_Admin();
	// End of start-up script

	// Intepreter
	do {
		string c;
		cout << "(" << ID << ")> ";
		getline(cin, c);

		// case-insensitivity
		for (size_t i = 0; i < c.length(); i++)
			c[i] = ::tolower(c[i]);

		if (c == "logout" || c == "-") { break; }
		else if (c == "quit") { exit(EXIT_SUCCESS); }
		else if (c == "cls") { system("CLS"); }
		else if (c == "help") { ShowHelp_General(); ShowHelp_Admin(); }

		else if (c == "passwd") {
			string Password_New, Password_New_Re;
			cout << "Enter new password: ";
			Password_New = GetPassword();
			cout << "\n";
			cout << "Re-enter new password: ";
			Password_New_Re = GetPassword();
			cout << "\n";

			if (Password_New != Password_New_Re) {
				cout << "Passwords do not match. Operation aborted.\n";
			}
			else {
				ChangePassword(ID, AC_ADMIN, Password_New);
			}
		}

		else if (c == "timport") {
			ImportStudents(CurrentList, ClassID);
		}

		else if (c == "tload") {
			cout << "Usage: tload <Class ID>\n";
		}
		else if (c.substr(0, strlen("tload")) == "tload") {
			ClassID = c.substr(strlen("tload") + 1);
			if (ClassID.find_first_not_of(' ') != string::npos) {
				LoadStudents(CurrentList, ClassID);
			}
			else {
				cout << "Usage: tload <Class ID>\n";
			}
		}

		else if (c == "tclass") {
			cout << "Current class = "
				<< (ClassID.empty() ? "none" : ClassID)
				<< "\n";
		}

		else if (c == "tlist") {
			ListStudents(CurrentList, ClassID);
		}

		else if (c == "tlookup") {
			cout << "Usage: tlookup <Student ID>\n";
		}
		else if (c.substr(0, strlen("tlookup")) == "tlookup") {
			string StudentID = c.substr(strlen("tlookup")+1);
			if (StudentID.find_first_not_of(' ') != string::npos) {
				ShowInfo(CurrentList, ClassID, StudentID);
			}
			else {
				cout << "Usage: tlookup <Student ID>\n";
			}
		}

		else if (c == "tadd") {
			CreateStudent(CurrentList, ClassID);
		}

		else if (c == "tedit") {
			cout << "Usage: tedit <Student ID>\n";
		}
		else if (c.substr(0, strlen("tedit")) == "tedit") {
			string StudentID = c.substr(strlen("tedit") + 1);
			if (StudentID.find_first_not_of(' ') != string::npos) {
				EditStudent(CurrentList, ClassID, StudentID);
			}
			else {
				cout << "Usage: tedit <Student ID>\n";
			}
		}

		else if (c == "tdelete") {
			cout << "Usage: tdelete <Student ID>\n";
		}
		else if (c.substr(0, strlen("tdelete")) == "tdelete") {
			string StudentID = c.substr(strlen("tdelete") + 1);
			if (StudentID.find_first_not_of(' ') != string::npos) {
				DeleteStudent(CurrentList, ClassID, StudentID);
			}
			else {
				cout << "Usage: tdelete <Student ID>\n";
			}
		}

		else if (c == "clist") {
			ListClasses();
		}
	
		else { cout << "Invalid command.\n"; }
		cout << "\n";
	} while (1);
}
