#include "Menu.h"

void ShowHelp_Lecturer() {
	cout << "\n[LECTURER COMMANDS]\n"
		<< "clist    : View list of courses in a term\n"
		<< "cslist   : View list of students of a course\n"
		<< "alist    : View attendance list of a course\n"
		<< "aedit    : Edit an attendance\n"
		<< "scimport : Import scoreboard of a course\n"
		<< "sclist   : View a scoreboard\n"
		<< "scedit   : Edit scores of a student\n"
		<< "\n";
}

void Menu_Lecturer(const string & ID) {
	LecturerList CurrentLecturerList;
	LoadLecturer(CurrentLecturerList);

	// Start-up script
	LookupLecturer(CurrentLecturerList, ID);
	cout << "\n";
	ShowHelp_General();
	ShowHelp_Lecturer();
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
		else if (c == "info") { LookupLecturer(CurrentLecturerList, ID); }
		else if (c == "help") { ShowHelp_General(); ShowHelp_Lecturer(); }

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
				ChangePassword(ID, AC_LECTURER, Password_New);
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
