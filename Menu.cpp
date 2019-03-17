#include "Menu.h"
#include "Student.h"
#include "Course.h"

void Capitalize(string & string) {
	for (size_t i = 0; i < string.length(); i++)
		string[i] = ::toupper(string[i]);
}

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
		<< "STUDENTS\n"
		<< "slist   : View list of students in a class\n"
		<< "slookup : Find information of a student\n"
		<< "sadd    : Add a student to a class\n"
		<< "sedit   : Edit a student\n"
		<< "smove   : Move a student to another class\n"
		<< "sdelete : Remove a student\n"
		<< "\n"
		<< "CLASSES\n"
		<< "cimport : Import students of a class (from a CSV file)\n"
		<< "clist   : List classes\n"
		<< "cload   : Load a class from the database\n"
		<< "cnow    : Show current working class\n"
		<< "\n"
		<< "YEARS & TERMS\n"
		<< "ylist   : List academic years\n"
		<< "yadd    : Create a year\n"
		<< "yedit   : Rename a year\n"
		<< "ydelete : Delete a year\n"
		<< "tlist   : List terms in a year\n"
		<< "tadd    : Create a term in a year\n"
		<< "tedit   : Rename a term in a year\n"
		<< "tdelete : Delete a term in a year\n"
		<< "\n"
		<< "COURSES\n"
		<< "rlist   : List courses in a term\n"
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
		else if (c == "quit" || c == "exit") { exit(EXIT_SUCCESS); }
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

		else if (c == "slist") {
			ListStudents(CurrentList, CurrentClassID);
		}

		else if (c == "slookup") {
			cout << "Usage: slookup <Student ID>\n";
		}
		else if (c.substr(0, strlen("slookup")) == "slookup") {
			string StudentID = c.substr(strlen("slookup") + 1);
			if (StudentID.find_first_not_of(' ') != string::npos) {
				ShowInfo(CurrentList, CurrentClassID, StudentID);
			}
			else {
				cout << "Usage: slookup <Student ID>\n";
			}
		}

		else if (c == "sadd") {
			if (CurrentClassID.empty()) {
				cout << "ERROR: No class loaded.\n";
				continue;
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

		else if (c == "sedit") {
			cout << "Usage: sedit <Student ID>\n";
		}
		else if (c.substr(0, strlen("sedit")) == "sedit") {
			string StudentID = c.substr(strlen("sedit") + 1);
			if (StudentID.find_first_not_of(' ') != string::npos) {
				EditStudent(CurrentList, CurrentClassID, StudentID);
			}
			else {
				cout << "Usage: sedit <Student ID>\n";
			}
		}

		else if (c == "smove") {
			cout << "Usage: smove <Student ID>\n";
		}
		else if (c.substr(0, strlen("smove")) == "smove") {
			if (CurrentClassID.empty()) {
				cout << "ERROR: No class loaded.\n";
				continue;
			}
			string StudentID = c.substr(strlen("smove") + 1);
			if (StudentID.find_first_not_of(' ') != string::npos) {

				string ClassID_New;
				cout << "Enter target class ID: ";
				getline(cin, ClassID_New);
				Capitalize(ClassID_New);

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
				cout << "Usage: smove <Student ID>\n";
			}
		}

		else if (c == "sdelete") {
			cout << "Usage: sdelete <Student ID>\n";
		}
		else if (c.substr(0, strlen("sdelete")) == "sdelete") {
			string StudentID = c.substr(strlen("sdelete") + 1);
			if (StudentID.find_first_not_of(' ') != string::npos) {
				DeleteStudent(CurrentList, CurrentClassID, StudentID);
			}
			else {
				cout << "Usage: sdelete <Student ID>\n";
			}
		}
		
		else if (c == "cimport") {
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
			Capitalize(ClassID_New);
			ImportStudents(filename, ClassID_New);
		}

		else if (c == "clist") {
			ListClasses();
		}

		else if (c == "cload") {
			cout << "Usage: cload <Class ID>\n";
		}
		else if (c.substr(0, strlen("cload")) == "cload") {
			CurrentClassID = c.substr(strlen("cload") + 1);
			Capitalize(CurrentClassID);
			if (CurrentClassID.find_first_not_of(' ') != string::npos) {
				LoadStudents(CurrentList, CurrentClassID);
			}
			else {
				cout << "Usage: cload <Class ID>\n";
			}
		}

		else if (c == "cnow") {
			cout << "Current class = "
				<< (CurrentClassID.empty() ? "none" : CurrentClassID)
				<< "\n";
		}

		else if (c == "ylist") {
			ListYears();
		}

		else if (c == "yadd") {
			cout << "Usage: yadd <Year>\n";
		}
		else if (c.substr(0, strlen("yadd")) == "yadd") {
			string Year = c.substr(strlen("yadd") + 1);
			Capitalize(Year);
			if (Year.find_first_not_of(' ') != string::npos) {
				CreateYear(Year);
			}
			else {
				cout << "Usage: yadd <Year>\n";
			}
		}

		else if (c == "yedit") {
			string Year_Old, Year_New;
			cout << "Enter year: "; getline(cin, Year_Old); Capitalize(Year_Old);
			cout << "Rename " << Year_Old << " into: "; getline(cin, Year_New); Capitalize(Year_New);
			if (Year_Old.empty() || Year_New.empty()) {
				cout << "Empty year(s) is/are invalid.\n";
				continue;
			}
			EditYear(Year_Old, Year_New);
		}

		else if (c == "ydelete") {
			cout << "Usage: ydelete <Year>\n";
		}
		else if (c.substr(0, strlen("ydelete")) == "ydelete") {
			string Year = c.substr(strlen("ydelete") + 1);
			Capitalize(Year);
			if (Year.find_first_not_of(' ') != string::npos) {
				DeleteYear(Year);
			}
			else {
				cout << "Usage: ydelete <Year>\n";
			}
		}

		else if (c == "tlist") {
			cout << "Usage: tlist <Year>\n";
		}
		else if (c.substr(0, strlen("tlist")) == "tlist") {
			string Year = c.substr(strlen("tlist") + 1);
			Capitalize(Year);
			if (Year.find_first_not_of(' ') != string::npos) {
				ListTerms(Year);
			}
			else {
				cout << "Usage: tlist <Year>\n";
			}
		}

		else if (c == "tadd") {
			string Year, Term;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			if (Year.empty() || Term.empty()) {
				cout << "Empty year and/or term is invalid.\n";
				continue;
			}
			CreateTerm(Year, Term);
		}

		else if (c == "tedit") {
			string Year, Term_Old, Term_New;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term_Old); Capitalize(Term_Old);
			cout << "Rename " << Term_Old << " into: "; getline(cin, Term_New); Capitalize(Term_New);
			if (Year.empty() || Term_Old.empty() || Term_New.empty()) {
				cout << "Empty year and/or term(s) is/are invalid.\n";
				continue;
			}
			EditTerm(Year, Term_Old, Term_New);
		}

		else if (c == "tdelete") {
			string Year, Term;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			if (Year.empty() || Term.empty()) {
				cout << "Empty year and/or term is invalid.\n";
				continue;
			}
			DeleteTerm(Year, Term);
		}

		else if (c == "rlist") {
			string Year, Term;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			if (Year.empty() || Term.empty()) {
				cout << "Empty year and/or term is invalid.\n";
				continue;
			}
			ListCourses(Year, Term);
		}

		else { cout << "Invalid command.\n"; }
		cout << "\n";
	} while (1);
}
