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
		<< "tmove   : Move a student to another class\n"
		<< "clist   : List classes\n"
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
		else if (c == "quit") { exit(EXIT_SUCCESS); }
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

void Menu_Admin(const string & ID) {
	StudentList CurrentList;
	string CurrentClassID;

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
			cout << "Enter filename: ";
			string filename;
			getline(cin, filename);
			cout << GetPath("../import/student_info/" + filename) << endl;

			cout << "Enter class ID: ";
			string ClassID_New;
			getline(cin, ClassID_New);
			if (ClassID_New.empty()) {
				cout << "Invalid class ID.\n";
				continue;
			}
			NormalizeClassID(ClassID_New);
			ImportStudents(filename, ClassID_New);
		}

		else if (c == "tload") {
			cout << "Usage: tload <Class ID>\n";
		}
		else if (c.substr(0, strlen("tload")) == "tload") {
			CurrentClassID = c.substr(strlen("tload") + 1);
			NormalizeClassID(CurrentClassID);
			if (CurrentClassID.find_first_not_of(' ') != string::npos) {
				LoadStudents(CurrentList, CurrentClassID);
			}
			else {
				cout << "Usage: tload <Class ID>\n";
			}
		}

		else if (c == "tclass") {
			cout << "Current class = "
				<< (CurrentClassID.empty() ? "none" : CurrentClassID)
				<< "\n";
		}

		else if (c == "tlist") {
			ListStudents(CurrentList, CurrentClassID);
		}

		else if (c == "tlookup") {
			cout << "Usage: tlookup <Student ID>\n";
		}
		else if (c.substr(0, strlen("tlookup")) == "tlookup") {
			string StudentID = c.substr(strlen("tlookup")+1);
			if (StudentID.find_first_not_of(' ') != string::npos) {
				ShowInfo(CurrentList, CurrentClassID, StudentID);
			}
			else {
				cout << "Usage: tlookup <Student ID>\n";
			}
		}

		else if (c == "tadd") {
			if (CurrentClassID.empty()) {
				cout << "ERROR: No class loaded.\n";
				return;
			}
			Student Student_New;
			cout << "ID: "; getline(cin, Student_New.ID);
			cout << "Last name: "; getline(cin, Student_New.LastName);
			cout << "First name: "; getline(cin, Student_New.FirstName);
			cout << "Gender: "; getline(cin, Student_New.Gender);
			cout << "Birth/Year: "; cin >> Student_New.DOB.y;
			cout << "Birth/Month: "; cin >> Student_New.DOB.m;
			cout << "Birth/Day: "; cin >> Student_New.DOB.d;
			while (cin.get() != '\n');
			CreateStudent(CurrentList, CurrentClassID, Student_New);
		}

		else if (c == "tedit") {
			cout << "Usage: tedit <Student ID>\n";
		}
		else if (c.substr(0, strlen("tedit")) == "tedit") {
			string StudentID = c.substr(strlen("tedit") + 1);
			if (StudentID.find_first_not_of(' ') != string::npos) {
				EditStudent(CurrentList, CurrentClassID, StudentID);
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
				DeleteStudent(CurrentList, CurrentClassID, StudentID);
			}
			else {
				cout << "Usage: tdelete <Student ID>\n";
			}
		}

		else if (c == "tmove") {
			cout << "Usage: tmove <Student ID>\n";
		}
		else if (c.substr(0, strlen("tmove")) == "tmove") {
			if (CurrentClassID.empty()) {
				cout << "ERROR: No class loaded.\n";
				continue;
			}
			string StudentID = c.substr(strlen("tmove") + 1);
			if (StudentID.find_first_not_of(' ') != string::npos) {

				string ClassID_New;
				cout << "Enter target class ID: ";
				getline(cin, ClassID_New);
				NormalizeClassID(ClassID_New);

				ifstream temp;
				temp.open(GetPath("Classes/" + ClassID_New + ".txt"));

				if (ClassID_New.empty() || !temp.is_open()) {
					cout << "Invalid class ID.\n";
				}
				else {
					MoveStudent(CurrentList, CurrentClassID, ClassID_New, StudentID);
				}

			}
			else {
				cout << "Usage: tmove <Student ID>\n";
			}
		}

		else if (c == "clist") {
			ListClasses();
		}
	
		else { cout << "Invalid command.\n"; }
		cout << "\n";
	} while (1);
}
