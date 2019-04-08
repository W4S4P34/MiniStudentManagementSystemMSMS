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
	// Session data
	string StudentID = ID.substr(0, ID.find_first_of('@'));
	string CurrentClassID = ID.substr(ID.find_first_of('@') + 1);
	Timetable StudentTimetable;
	ScoreList StudentScoreboard;
	int i = 0; // number of courses (THIS SESSION ONLY)

	// potentially dangerous?
	StudentList CurrentList;
	LoadClass(CurrentList, CurrentClassID);

	// Start-up script
	StudentTimetable.Load(StudentID);
	LookupStudent(CurrentList, CurrentClassID, StudentID);
	cout << "\n";
	ShowHelp_General();
	ShowHelp_Student();

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
		else if (c == "info") { LookupStudent(CurrentList, CurrentClassID, StudentID); }
		else if (c == "help") { ShowHelp_General(); ShowHelp_Student(); }

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
				ChangePassword(ID, AC_STUDENT, Password_New);
			}
		}

		else if (c == "sched")
		{
			i = 0;
			cout << "Opted-in courses:" << "\n";
			Timetable::node * current = StudentTimetable.head;
			string CourseName, LecturerID, Room;
			time_t CourseStartTime; tm CourseStartTime_tm = { 0 };
			time_t CourseEndTime; tm CourseEndTime_tm = { 0 };
			const char wday_name[][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

			fstream CourseInfoFile;
			while (current != nullptr) {
				CourseInfoFile.open(GetPath("Courses/" + current->CoursePath + "_Info.txt"), fstream::in);
				getline(CourseInfoFile, CourseName);
				getline(CourseInfoFile, LecturerID);
				getline(CourseInfoFile, Room);
				CourseInfoFile >> CourseStartTime;
				CourseInfoFile >> CourseEndTime;
				CourseInfoFile.close();
				localtime_s(&CourseStartTime_tm, &CourseStartTime);
				localtime_s(&CourseEndTime_tm, &CourseEndTime);
				i++;
				cout << i << ". "
					<< left << setw(30) << (CourseName + " (" + wday_name[CourseStartTime_tm.tm_wday] + ")")
					<< left << setw(10) << Room
					<< setw(2) << right << CourseStartTime_tm.tm_hour << ":" << setw(2) << CourseStartTime_tm.tm_min
					<< " - "
					<< setw(2) << right << CourseEndTime_tm.tm_hour << ":" << setw(2) << CourseEndTime_tm.tm_min << '\n';
				current = current->next;
			}
		}

		else if (c == "checkin")
		{
			CheckIn_Menu(StudentID);
		}

		else if (c == "score")
		{
			int i = 0;
			cout << "Opted-in courses:" << "\n";
			Timetable::node * current = StudentTimetable.head;
			string CourseName, skip;
			time_t CourseStartTime; tm CourseStartTime_tm = { 0 };
			const char wday_name[][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

			fstream CourseInfoFile;
			while (current != nullptr) {
				CourseInfoFile.open(GetPath("Courses/" + current->CoursePath + "_Info.txt"), fstream::in);
				getline(CourseInfoFile, CourseName);
				getline(CourseInfoFile, skip);
				getline(CourseInfoFile, skip);
				CourseInfoFile >> CourseStartTime;
				CourseInfoFile.close();
				localtime_s(&CourseStartTime_tm, &CourseStartTime);
				i++;
				cout << i << ". " << CourseName << " (" << wday_name[CourseStartTime_tm.tm_wday] << ")" << "\n";
				current = current->next;
			}
			
			current = StudentTimetable.head;

			int selection;
			do {
				cout << "Choose course (Enter a number): "; cin >> selection;
				if (selection < 1 || selection > i) {
					cout << "Invalid choice." << "\n" << "\n";
				}
			} while (selection < 1 || selection > i);

			for (int j = 1; j < selection; j++)
				current = current->next;

			LoadScore(StudentScoreboard, current->CoursePath);
			ViewScore(StudentScoreboard, StudentID);
			while (cin.get() != '\n');
		}

		else if (c == "listck")
		{
			int i = 0;
			cout << "Opted-in courses:" << "\n";
			Timetable::node * current = StudentTimetable.head;
			string CourseName, skip;
			time_t CourseStartTime; tm CourseStartTime_tm = { 0 };
			const char wday_name[][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

			fstream CourseInfoFile;
			while (current != nullptr) {
				CourseInfoFile.open(GetPath("Courses/" + current->CoursePath + "_Info.txt"), fstream::in);
				getline(CourseInfoFile, CourseName);
				getline(CourseInfoFile, skip);
				getline(CourseInfoFile, skip);
				CourseInfoFile >> CourseStartTime;
				CourseInfoFile.close();
				localtime_s(&CourseStartTime_tm, &CourseStartTime);
				i++;
				cout << i << ". " << CourseName << " (" << wday_name[CourseStartTime_tm.tm_wday] << ")" << "\n";
				current = current->next;
			}

			current = StudentTimetable.head;

			int selection;
			do {
				cout << "Choose course (Enter a number): "; cin >> selection;
				if (selection < 1 || selection > i) {
					cout << "Invalid choice." << "\n" << "\n";
				}
			} while (selection < 1 || selection > i);

			for (int j = 1; j < selection; j++)
				current = current->next;

			AttendanceList CurrentAttendanceList;
			LoadAttendance(CurrentAttendanceList, current->CoursePath);
			ViewAttendance(CurrentAttendanceList, StudentID);
		}

		else { cout << "Invalid command.\n"; }
		cout << "\n";
	} while (1);
}
