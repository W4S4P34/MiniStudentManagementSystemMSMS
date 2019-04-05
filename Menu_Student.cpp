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

		else if (c == "sched")
		{
			cout << "Opted-in courses:" << "\n";
			Timetable::node * current = StudentTimetable.head;
			int i = 0;
			string CourseName, skip;
			time_t CourseStartTime; tm CourseStartTime_tm = { 0 };
			const char wday_name[][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

			fstream CourseInfoFile;
			while (current != nullptr) {
				CourseInfoFile.open(GetPath("Courses/" + current->CoursePath + "_Info.txt"), fstream::in);
				CourseInfoFile.is_open();
				getline(CourseInfoFile, CourseName);
				getline(CourseInfoFile, skip);
				CourseInfoFile >> CourseStartTime;
				localtime_s(&CourseStartTime_tm, &CourseStartTime);
				i++;
				cout << i << ". " << CourseName << " (" << wday_name[CourseStartTime_tm.tm_wday] << ")" << "\n";
				current = current->next;
			}
			CourseInfoFile.close();

		}

		//else if (c == "checkin") { }
		//else if (c == "listck") { }
		//else if (c == "score") { }

		else { cout << "Invalid command.\n"; }
		cout << "\n";
	} while (1);
}
