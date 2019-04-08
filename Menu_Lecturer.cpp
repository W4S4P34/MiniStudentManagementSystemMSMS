#include "Menu.h"

void ShowHelp_Lecturer() {
	cout << "\n[LECTURER COMMANDS]\n"
		<< "ylist    : View list of academic years\n"
		<< "tlist    : View list of terms in a year\s"
		<< "rlist    : View list of courses in a term\n"
		<< "rslist   : View list of students of a course\n"
		<< "\n"
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

	do {
		string c;
		cout << "(" << ID << ")> ";
		getline(cin, c);

		// case-insensitivity
		for (size_t i = 0; i < c.length(); i++)
			c[i] = ::tolower(c[i]);

		if (c == "logout" || c == "-") { break; }
		else if (c == "quit" || c == "exit") { exit(EXIT_SUCCESS); }
		else if (c == "cls") { system("CLS"); cout << "\n"; continue; }
		else if (c == "info") { LookupLecturer(CurrentLecturerList, ID); }
		else if (c == "help") { ShowHelp_General(); ShowHelp_Admin(); }

		else if (c == "passwd")
		{
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

		else if (c == "ylist")
		{
			ListYears();
		}

		else if (c == "tlist")
		{
			string Year;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			if (Year.empty() || Year == "\n") {
				cout << "Empty values are invalid.";
				continue;
			}
			ListTerms(Year);
		}

		else if (c == "rlist")
		{
			string Year, Term;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			if (Year.empty() || Year == "\n" || Term.empty() || Term == "\n") {
				cout << "Empty values are invalid.";
				continue;
			}
			ListCourses(Year, Term);
		}

		// else if (c == "rslist")
		
		else if (c == "alist")
		{
			string Year, Term, CourseID, ClassID, DayOfWeek;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			cout << "Enter day of week: "; getline(cin, DayOfWeek); LowerString(DayOfWeek);

			if (
				   Year.empty() || Year == "\n"
				|| Term.empty() || Term == "\n"
				|| CourseID.empty() || CourseID == "\n"
				|| ClassID.empty() || ClassID == "\n"
				|| 
				)
		}

		else { cout << "Invalid command."; }
		cout << "\n\n";
	} while (1);
}
