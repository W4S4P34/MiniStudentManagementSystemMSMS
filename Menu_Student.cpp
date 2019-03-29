#include "Menu.h"

void ShowHelp_Student() {
	cout << "\n[STUDENT COMMANDS]\n"
		<< "checkin : Check-in\n"
		<< "listck  : View check-in result\n"
		<< "sched  : View schedules\n"
		<< "score  : View scoreboard result\n"
		<< "\n";
}

void Menu_Student(const string & ID) {
	string StudentID = ID.substr(0, ID.find_first_of('@'));
	string CurrentClassID = ID.substr(ID.find_first_of('@') + 1);

	// potentially dangerous?
	StudentList CurrentList;
	LoadStudents(CurrentList, CurrentClassID);

	// Start-up script
	ShowInfo(CurrentList, CurrentClassID, StudentID);
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
		else if (c == "quit" || c == "exit") { exit(EXIT_SUCCESS); }
		else if (c == "cls") { system("CLS"); }
		else if (c == "info") { ShowInfo(CurrentList, CurrentClassID, StudentID); }
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
