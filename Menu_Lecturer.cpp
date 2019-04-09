#include "Menu.h"

void ShowHelp_Lecturer() {
	cout << "\n[LECTURER COMMANDS]\n"
		<< "ylist    : View list of academic years\n"
		<< "tlist    : View list of terms in a year\n"
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
		else if (c == "help") { ShowHelp_General(); ShowHelp_Lecturer(); }

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
				ChangePassword(ID, AC_LECTURER, Password_New);
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

		else if (c == "rslist")
		{
			string Year, Term, CourseID, ClassID, DayOfWeek;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			cout << "Enter day of week: "; getline(cin, DayOfWeek); LowerString(DayOfWeek);
			ListStudent_Course(Year + "/" + Term + "/" + CourseID + "_" + ClassID + "_" + DayOfWeek);
		}
		
		else if (c == "alist")
		{
			string Year, Term, CourseID, ClassID, DayOfWeek;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			cout << "Enter day of week (3-letter): "; getline(cin, DayOfWeek); LowerString(DayOfWeek);

			if (
				Year.empty() || Year == "\n"
				|| Term.empty() || Term == "\n"
				|| CourseID.empty() || CourseID == "\n"
				|| ClassID.empty() || ClassID == "\n"
				|| (DayOfWeek != "mon"
				&& DayOfWeek != "tue"
				&& DayOfWeek != "wed"
				&& DayOfWeek != "thu"
				&& DayOfWeek != "fri"
				&& DayOfWeek != "sat"
				&& DayOfWeek != "sun")
			) {
				cout << "Empty values and/or invalid day-of-week found.";
				continue;
			}

			AttendanceList CurrentAttendanceList;
			LoadAttendance(CurrentAttendanceList, Year + "/" + Term + "/" + CourseID + "_" + ClassID + "_" + DayOfWeek);

			ViewAttendance(CurrentAttendanceList);
		}

		else if (c == "aedit")
		{
			string Year, Term, CourseID, ClassID, DayOfWeek;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			cout << "Enter day of week (3-letter): "; getline(cin, DayOfWeek); LowerString(DayOfWeek);

			if (
				Year.empty() || Year == "\n"
				|| Term.empty() || Term == "\n"
				|| CourseID.empty() || CourseID == "\n"
				|| ClassID.empty() || ClassID == "\n"
				|| (DayOfWeek != "mon"
				&& DayOfWeek != "tue"
				&& DayOfWeek != "wed"
				&& DayOfWeek != "thu"
				&& DayOfWeek != "fri"
				&& DayOfWeek != "sat"
				&& DayOfWeek != "sun")
				) {
				cout << "Empty values and/or invalid day-of-week found.";
				continue;
			}

			AttendanceList CurrentAttendanceList;
			LoadAttendance(CurrentAttendanceList, GetPath(Year + "/" + Term + "/" + CourseID + "_" + ClassID + "_" + DayOfWeek));
			if (CurrentAttendanceList.head == nullptr) {
				cout << "Unexpected: Empty attendance list.";
				continue;
			}

			string StudentID;
			size_t Week;
			string State_String;
			bool State;

			cout << "Enter student ID: "; getline(cin, StudentID);
			cout << "Enter week number: "; cin >> Week;
			cout << "Type + for present; - for absent: "; cin >> State_String;

			if (Week < 1 || Week > 10 || StudentID.empty() || StudentID == "\n" || (State_String != "+" && State_String != "-")) {
				cout << "Invalid student ID, week number and/or presence state.";
				continue;
			}

			State = (State_String == "+" ? true : false);
			EditAttendance(CurrentAttendanceList, Year + "/" + Term + "/" + CourseID + "_" + ClassID + "_" + DayOfWeek, StudentID, Week, State);
		}

		else if (c == "scimport")
		{
			string Year, Term, CourseID, ClassID, DayOfWeek;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			cout << "Enter day of week (3-letter): "; getline(cin, DayOfWeek); LowerString(DayOfWeek);

			if (
				Year.empty() || Year == "\n"
				|| Term.empty() || Term == "\n"
				|| CourseID.empty() || CourseID == "\n"
				|| ClassID.empty() || ClassID == "\n"
				|| (DayOfWeek != "mon"
				&& DayOfWeek != "tue"
				&& DayOfWeek != "wed"
				&& DayOfWeek != "thu"
				&& DayOfWeek != "fri"
				&& DayOfWeek != "sat"
				&& DayOfWeek != "sun")
			) {
				cout << "Empty values and/or invalid day-of-week found.";
				continue;
			}

			string FileName;
			cout << "Enter score filename: "; getline(cin, FileName);
			if (FileName.empty() || FileName == "\n") {
				cout << "Empty filename is invalid.";
				continue;
			}

			ImportScore(FileName, Year + "/" + Term + "/" + CourseID + "_" + ClassID + "_" + DayOfWeek);
		}

		else if (c == "sclist")
		{
			string Year, Term, CourseID, ClassID, DayOfWeek;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			cout << "Enter day of week (3-letter): "; getline(cin, DayOfWeek); LowerString(DayOfWeek);

			if (
				Year.empty() || Year == "\n"
				|| Term.empty() || Term == "\n"
				|| CourseID.empty() || CourseID == "\n"
				|| ClassID.empty() || ClassID == "\n"
				|| (DayOfWeek != "mon"
				&& DayOfWeek != "tue"
				&& DayOfWeek != "wed"
				&& DayOfWeek != "thu"
				&& DayOfWeek != "fri"
				&& DayOfWeek != "sat"
				&& DayOfWeek != "sun")
			) {
				cout << "Empty values and/or invalid day-of-week found.\n";
				continue;
			}

			ScoreList CurrentScoreList;
			LoadScore(CurrentScoreList, Year + "/" + Term + "/" + CourseID + "_" + ClassID);
			ViewScore(CurrentScoreList);
		}

		else if (c == "scedit")
		{
			string Year, Term, CourseID, ClassID, DayOfWeek;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			cout << "Enter day of week (3-letter): "; getline(cin, DayOfWeek); LowerString(DayOfWeek);

			if (
				Year.empty() || Year == "\n"
				|| Term.empty() || Term == "\n"
				|| CourseID.empty() || CourseID == "\n"
				|| ClassID.empty() || ClassID == "\n"
				|| (DayOfWeek != "mon"
				&& DayOfWeek != "tue"
				&& DayOfWeek != "wed"
				&& DayOfWeek != "thu"
				&& DayOfWeek != "fri"
				&& DayOfWeek != "sat"
				&& DayOfWeek != "sun")
				) {
				cout << "Empty values and/or invalid day-of-week found.";
				continue;
			}

			ScoreList CurrentScoreList;
			LoadScore(CurrentScoreList, Year + "/" + Term + "/" + CourseID + "_" + ClassID);

			string StudentID;
			cout << "Enter student ID: "; getline(cin, StudentID);

			ScoreList::Score * current = CurrentScoreList.head;
			while (current != nullptr) {
				if (current->ID == StudentID) break;
				current = current->next;
			}

			if (current == nullptr) {
				cout << "Student " << StudentID << " not found.";
				continue;
			}

			ViewScore(CurrentScoreList, StudentID);

			float Midterm, Final, Lab, Bonus;
			cout << "New score:\n";
			cout << "Midterm: "; cin >> Midterm;
			cout << "Final: "; cin >> Final;
			cout << "Lab: "; cin >> Lab;
			cout << "Bonus: "; cin >> Bonus;
			while (cin.get() != '\n');

			EditScore(CurrentScoreList, Year + "/" + Term + "/" + CourseID + "_" + ClassID, StudentID, Midterm, Final, Lab, Bonus);
		}

		else { cout << "Invalid command."; }
		cout << "\n\n";
	} while (1);
}
