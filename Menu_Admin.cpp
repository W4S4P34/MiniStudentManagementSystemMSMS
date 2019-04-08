#include "Menu.h"

void ShowHelp_Admin()
{
	cout << "\n[ADMIN COMMANDS]\n"
		<< "STUDENTS\n"
		<< "slist   : View list of students in a class\n"
		<< "slookup : Find information of a student\n"
		<< "sadd    : Add a student to a class\n"
		<< "sedit   : Edit a student\n"
		<< "smove   : Move a student to another class\n"
		<< "sdelete : Remove a student\n"
		<< "\n"
		<< "LECTURERS\n"
		<< "limport : Import lecturers\n"
		<< "llist   : List lecturers\n"
		<< "llookup : Find information of a lecturer\n"
		<< "ladd    : Create a lecturer\n"
		<< "ledit   : Edit a lecturer\n"
		<< "ldelete : Delete a lecturer\n"
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
		<< "rimport : Import a course (from a CSV file)\n"
		<< "rlist   : List courses in a term\n"
		<< "radd    : Create a course\n"
		<< "redit   : Edit a course's information\n"
		<< "rdelete : Delete a course\n"
		<< "\n"
		<< "SCOREBOARD\n"
		<< "scview  : View the scoreboard of a course\n"
		<< "sclookup: View the scoreboard of a specific student in a course\n"
		<< "scedit  : Edit an entry in the scoreboard\n"
		<< "\n";
}

void Menu_Admin(const string & ID) {
	// Session "memory"
	string CurrentClassID;
	StudentList CurrentStudentList;
	string CurrentCoursePath;
	Course CurrentCourseInfo;
	AttendanceList CurrentAttendanceList;
	ScoreList CurrentScoreList;
	LecturerList CurrentLecturerList;

	// Start-up script
	LoadLecturer(CurrentLecturerList);
	cout << "\n";
	ShowHelp_General();
	ShowHelp_Admin();

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
		else if (c == "cls") { system("CLS"); cout << "\n"; continue; }
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

		// STUDENT ////////////////////////////////////////////////////////////////////

		else if (c == "slist")
		{
			if (CurrentClassID.empty()) { cout << "ERROR: No classes loaded."; cout << "\n\n"; continue; }
			ListStudents(CurrentStudentList, CurrentClassID);
		}

		else if (c == "slookup")
		{
			if (CurrentClassID.empty()) { cout << "ERROR: No classes loaded."; cout << "\n\n"; continue; }
			string StudentID;
			cout << "Enter student ID: "; getline(cin, StudentID);
			if (StudentID.empty()) { cout << "Invalid student ID."; cout << "\n\n"; continue; }
			LookupStudent(CurrentStudentList, CurrentClassID, StudentID);
		}

		else if (c == "sadd")
		{
			if (CurrentClassID.empty()) { cout << "ERROR: No classes loaded."; cout << "\n\n"; continue; }
			StudentList::Student Student_New;
			cout << "ID: "; getline(cin, Student_New.ID);
			cout << "Last name: "; getline(cin, Student_New.LastName);
			cout << "First name: "; getline(cin, Student_New.FirstName);
			cout << "Gender: "; getline(cin, Student_New.Gender);
			cout << "Birth/Year: "; cin >> Student_New.DOB.y;
			cout << "Birth/Month: "; cin >> Student_New.DOB.m;
			cout << "Birth/Day: "; cin >> Student_New.DOB.d;
			while(cin.get() != '\n');
			CreateStudent(CurrentStudentList, CurrentClassID, Student_New);
		}

		else if (c == "sedit")
		{
			if (CurrentClassID.empty()) { cout << "ERROR: No classes loaded."; cout << "\n\n"; continue; }
			string StudentID;
			cout << "Enter student ID: "; getline(cin, StudentID);
			EditStudent(CurrentStudentList, CurrentClassID, StudentID);
		}

		else if (c == "smove")
		{
			if (CurrentClassID.empty()) { cout << "ERROR: No classes loaded."; cout << "\n\n"; continue; }
			string StudentID;
			cout << "Enter student ID: "; getline(cin, StudentID);
			string ClassID_New;
			cout << "Enter new class ID: "; getline(cin, ClassID_New); Capitalize(ClassID_New);
			if (CurrentClassID.empty()) { cout << "ERROR: Invalid class ID."; cout << "\n\n"; continue; }
			MoveStudent(CurrentStudentList, CurrentClassID, ClassID_New, StudentID);
		}

		else if (c == "sdelete")
		{
			if (CurrentClassID.empty()) { cout << "ERROR: No classes loaded."; cout << "\n\n"; continue; }
			string StudentID;
			cout << "Enter student ID: "; getline(cin, StudentID);
			DeleteStudent(CurrentStudentList, CurrentClassID, StudentID);
		}

		// LECTURER ///////////////////////////////////////////////////////////////////
		
		else if (c == "limport") {
			string FileName;
			cout << "Enter filename: "; getline(cin, FileName);
			if (FileName.empty()) {
				cout << "Invalid filename is invalid.\n";
				continue;
			}
			cout << GetPath("../Import/Lecturers/" + FileName) << "\n";
			ImportLecturer(FileName, CurrentLecturerList);
		}

		else if (c == "llist") {
			ListLecturer(CurrentLecturerList);
		}

		else if (c == "llookup") {
			cout << "Usage: llookup <Lecturer ID>\n";
		}
		else if (c.substr(0, strlen("llookup")) == "llookup") {
			string LecturerID = c.substr(strlen("llookup") + 1);
			if (LecturerID.find_first_not_of(' ') != string::npos) {
				LookupLecturer(CurrentLecturerList, LecturerID);
			}
			else {
				cout << "Usage: llookup <Lecturer ID>\n";
			}
		}

		else if (c == "ladd") {
			string LastName, FirstName, Gender;
			cout << "Last name: "; getline(cin, LastName);
			cout << "First name: "; getline(cin, FirstName);
			cout << "Gender: "; getline(cin, Gender);
			if (
				LastName.empty()
				|| FirstName.empty()
				|| Gender.empty()
				) {
				cout << "Empty value(s) is/are not allowed.\n";
				continue;
			}
			CreateLecturer(CurrentLecturerList, LastName, FirstName, Gender);
		}

		else if (c == "ledit") {
			cout << "Usage: ledit <Lecturer ID>\n";
		}
		else if (c.substr(0, strlen("ledit")) == "ledit") {
			string LecturerID = c.substr(strlen("ledit") + 1);
			if (LecturerID.find_first_not_of(' ') != string::npos) {
				EditLecturer(CurrentLecturerList, LecturerID);
			}
			else {
				cout << "Usage: ledit <Lecturer ID>\n";
			}
		}

		else if (c == "ldelete") {
			cout << "Usage: ldelete <Lecturer ID>\n";
		}
		else if (c.substr(0, strlen("ldelete")) == "ldelete") {
			string LecturerID = c.substr(strlen("ldelete") + 1);
			if (LecturerID.find_first_not_of(' ') != string::npos) {
				DeleteLecturer(CurrentLecturerList, LecturerID);
			}
			else {
				cout << "Usage: ldelete <Lecturer ID>\n";
			}
		}

		else if (c == "cimport") {
			cout << "Enter filename: ";
			string filename;
			getline(cin, filename);
			cout << GetPath("../import/student_info/" + filename) << "\n";

			cout << "Enter class ID: ";
			string ClassID_New;
			getline(cin, ClassID_New);
			if (ClassID_New.empty()) {
				cout << "Invalid class ID.\n";
				continue;
			}
			Capitalize(ClassID_New);
			ImportClass(filename, ClassID_New);
		}

		else if (c == "clist") {
			ListClass();
		}

		else if (c == "cload") {
			cout << "Usage: cload <Class ID>\n";
		}
		else if (c.substr(0, strlen("cload")) == "cload") {
			CurrentClassID = c.substr(strlen("cload") + 1);
			Capitalize(CurrentClassID);
			if (CurrentClassID.find_first_not_of(' ') != string::npos) {
				LoadClass(CurrentStudentList, CurrentClassID);
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

		else if (c == "rimport") {
			string FileName, Year, Term;
			cout << "Enter filename: "; getline(cin, FileName);
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			if ( FileName.empty() || Year.empty() || Term.empty() ) {
				cout << "Empty filename, year and/or term is invalid.\n";
				continue;
			}
			cout << GetPath("../Import/Courses/" + FileName) << "\n";
			ImportCourse(FileName, Year, Term);
		}

		else if (c == "radd") {
			string Year, Term;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			if (Year.empty() || Term.empty()) {
				cout << "Empty year and/or term is invalid.\n";
				continue;
			}

			Course Course_New;
			cout << "Course ID: "; getline(cin, Course_New.ID); Capitalize(Course_New.ID);
			cout << "Course name: "; getline(cin, Course_New.Name);
			// cout << "Lecturer ID: "; getline(cin, Course_New.LecturerID);
			cout << "Class ID: "; getline(cin, Course_New.ClassID); Capitalize(Course_New.ClassID);
			cout << "Room: "; getline(cin, Course_New.Room); Capitalize(Course_New.Room);

			string StartY, StartM, StartD, StartHH, StartMM;
			string EndY, EndM, EndD, EndHH, EndMM;
			string DoW;
			cout << "Enter Start year: "; getline(cin, StartY);
			cout << "Enter Start month: "; getline(cin, StartM);
			cout << "Enter Start day: "; getline(cin, StartD);
			cout << "Enter Start hour: "; getline(cin, StartHH);
			cout << "Enter Start minute: "; getline(cin, StartMM);
			cout << "Enter End year: "; getline(cin, EndY);
			cout << "Enter End month: "; getline(cin, EndM);
			cout << "Enter End day: "; getline(cin, EndD);
			cout << "Enter End hour: "; getline(cin, EndHH);
			cout << "Enter End minute: "; getline(cin, EndMM);
			cout << "Enter Day of Week: "; getline(cin, DoW); Capitalize(DoW);

			Course_New.Start.tm_year = stoi(StartY); Course_New.Start.tm_year -= 1900;
			Course_New.Start.tm_mon = stoi(StartM); Course_New.Start.tm_mon -= 1;
			Course_New.Start.tm_mday = stoi(StartD);
			Course_New.Start.tm_hour = stoi(StartHH);
			Course_New.Start.tm_min = stoi(StartMM);
			if (DoW == "SUN") Course_New.Start.tm_wday = 0;
			else if (DoW == "MON") Course_New.Start.tm_wday = 1;
			else if (DoW == "TUE") Course_New.Start.tm_wday = 2;
			else if (DoW == "WED") Course_New.Start.tm_wday = 3;
			else if (DoW == "THU") Course_New.Start.tm_wday = 4;
			else if (DoW == "FRI") Course_New.Start.tm_wday = 5;
			else if (DoW == "SAT") Course_New.Start.tm_wday = 6;

			Course_New.End.tm_year = stoi(EndY); Course_New.End.tm_year -= 1900;
			Course_New.End.tm_mon = stoi(EndM); Course_New.End.tm_mon -= 1;
			Course_New.End.tm_mday = stoi(EndD);
			Course_New.End.tm_hour = stoi(EndHH);
			Course_New.End.tm_min = stoi(EndMM);
			Course_New.End.tm_wday = Course_New.Start.tm_wday;

			Course_New.Year = Year;
			Course_New.Term = Term;

			CreateCourse(Course_New);
		}

		else if (c == "rdelete") {
			string Year, Term, CourseID, ClassID;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			if (Year.empty() || Term.empty() || CourseID.empty() || ClassID.empty()) {
				cout << "Empty year, term and/or course information is invalid.\n";
				continue;
			}
			DeleteCourse(Year, Term, CourseID, ClassID);
		}

		else if (c == "redit")
		{
			string Year, Term, CourseID, ClassID, DayOfWeek;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			cout << "Enter day of week: "; getline(cin, DayOfWeek); LowerString(DayOfWeek);
			if (Year.empty() || Term.empty() || CourseID.empty() || ClassID.empty() || DayOfWeek.empty()) {
				cout << "Empty year, term and/or course information is invalid.\n";
				continue;
			}
			EditCourse(Year + "/" + Term + "/" + CourseID + "_" + ClassID + "_" + DayOfWeek);
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

		else if (c == "scview")
		{
			string Year, Term, CourseID, ClassID;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			LoadScore(CurrentScoreList, Year + "/" + Term + "/" + CourseID + "_" + ClassID);
			ViewScore(CurrentScoreList);
		}

		else if (c == "sclookup")
		{
			string Year, Term, CourseID, ClassID, StudentID;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			cout << "Enter student ID: "; getline(cin, StudentID); Capitalize(StudentID);
			LoadScore(CurrentScoreList, Year + "/" + Term + "/" + CourseID + "_" + ClassID);
			ViewScore(CurrentScoreList, StudentID);
		}

		else if (c == "scexport")
		{
			string Year, Term, CourseID, ClassID, FileName;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			cout << "Enter new filename: "; getline(cin, FileName);
			LoadScore(CurrentScoreList, Year + "/" + Term + "/" + CourseID + "_" + ClassID);
			ExportScore(FileName, CurrentScoreList, Year + "/" + Term + "/" + CourseID + "_" + ClassID);
		}

		else if (c == "aview")
		{
			string Year, Term, CourseID, ClassID, DayOfWeek;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			cout << "Enter day of week: "; getline(cin, DayOfWeek); LowerString(DayOfWeek);
			LoadAttendance(CurrentAttendanceList, Year + "/" + Term + "/" + CourseID + "_" + ClassID + "_" + DayOfWeek);
			ViewAttendance(CurrentAttendanceList);
		}

		else if (c == "alookup")
		{
			string Year, Term, CourseID, ClassID, StudentID, DayOfWeek;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			cout << "Enter day of week: "; getline(cin, DayOfWeek); LowerString(DayOfWeek);
			cout << "Enter student ID: "; getline(cin, StudentID); Capitalize(StudentID);
			LoadAttendance(CurrentAttendanceList, Year + "/" + Term + "/" + CourseID + "_" + ClassID + "_" + DayOfWeek);
			ViewAttendance(CurrentAttendanceList, StudentID);
		}

		else if (c == "aexport")
		{
			string Year, Term, CourseID, ClassID, DayOfWeek, FileName;
			cout << "Enter year: "; getline(cin, Year); Capitalize(Year);
			cout << "Enter term: "; getline(cin, Term); Capitalize(Term);
			cout << "Enter course ID: "; getline(cin, CourseID); Capitalize(CourseID);
			cout << "Enter class ID: "; getline(cin, ClassID); Capitalize(ClassID);
			cout << "Enter day of week: "; getline(cin, DayOfWeek); LowerString(DayOfWeek);
			cout << "Enter new filename: "; getline(cin, FileName);
			LoadAttendance(CurrentAttendanceList, Year + "/" + Term + "/" + CourseID + "_" + ClassID + "_" + DayOfWeek);
			ExportAttendance(FileName, CurrentAttendanceList, Year + "/" + Term + "/" + CourseID + "_" + ClassID + "_" + DayOfWeek);
		}

		else { cout << "Invalid command."; }
		cout << "\n\n";
	} while (1);
}
