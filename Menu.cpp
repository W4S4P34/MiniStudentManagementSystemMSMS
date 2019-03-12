#include "Menu.h"

void ShowMenu(const char & AccessClass) {
	cout << "COMMAND LIST:\n"
		<< "[-] Log out\n"
		<< "[I] Show user info\n"
		<< "[?] Show this command list\n"
		<< "[*] Change password\n"
		<< "[CLS] Clear the screen\n"
		<< "\n";

	switch (AccessClass) {
		case AC_STUDENT:
			cout << "------------------------------\n\n"
				<< "[C] Check-in\n"
				<< "[H] View check-in result\n"
				<< "[S] View schedules\n"
				<< "[R] View scoreboard result\n";
			break;

		case AC_LECTURER:
			cout << "------------------------------\n\n"
				<< "[C1] View list of courses in the current semester\n"
				<< "[C2] View list of students of a course\n"
				<< "[A1] View attendance list of a course\n"
				<< "[A2] Edit an attendance\n"
				<< "[S1] Import scoreboard of a course (midterm, final, lab, bonus) from a csv file\n"
				<< "[S2] Edit grade of a student\n"
				<< "[S3] View a scoreboard\n";
			break;

		case AC_ADMIN:
			cout << "------------------------------\n\n"
				<< "STUDENTS AND CLASSES\n"
				<< "[T1] Import students of a class (from a CSV file)\n"
				<< "[T2] Add a student to a class\n"
				<< "[T3] Change a student from class A to class B\n"
				<< "[T4] Edit a student\n"
				<< "[T5] Remove a student\n"
				<< "[T6] View list of classes\n"
				<< "[T7] View list of students in a class\n"
				<< "\n"
				<< "ACADEMIC YEARS AND SEMESTERS\n"
				<< "[Y1] Create an academic year\n"
				<< "[Y2] Update an academic year\n"
				<< "[Y3] Delete an academic year\n"
				<< "[Y4] View an academic year\n"
				<< "[Y5] Create a semester\n"
				<< "[Y6] Update a semester\n"
				<< "[Y7] Delete a semester\n"
				<< "[Y8] View a semester\n"
				<< "\n"
				<< "COURSES\n"
				<< "[C1] Create a new course\n"
				<< "[C2] Edit a course\n"
				<< "[C3] Delete a course\n"
				<< "[C4] Add a student to a course\n"
				<< "[C5] Remove a student from a course\n"
				<< "[C6] View list of courses in the current semester\n"
				<< "[C7] View list of students of a course\n"
				<< "\n"
				<< "LECTURERS\n"
				<< "[L1] Create a lecturer\n"
				<< "[L2] Update a lecturer's info\n"
				<< "[L3] Delete a lecturer\n"
				<< "[L4] View all lecturers\n"
				<< "\n"
				<< "SCOREBOARDS\n"
				<< "[S1] Search scoreboard of a course\n"
				<< "[S2] View scoreboard of a course\n"
				<< "[S3] Export a scoreboard (to a Csv file)\n"
				<< "\n"
				<< "ATTENDANCE LISTS\n"
				<< "[A1] Search attendance list of a course\n"
				<< "[A2] View attendance list of a course\n"
				<< "[A3] Export attendance list (to a CSV file)\n";
			break;
	}
	
	cout << "\nNote: invalid command will return no error.";
}

void Interpret(const string & ID, const char & AccessClass) {
	do {
		string c;
		cout << "(" << ID << ")>";
		getline(cin, c);

		// case-insensitivity
		for (size_t i = 0; i < c.length(); i++)
			c[i] = ::tolower(c[i]);

		if (c == "-") break;
		else if (c == "i") cout << "Show user information";
		else if (c == "?") ShowMenu(AccessClass);
		else if (c == "cls") system("CLS");
		else if (c == "*") ChangePassword(ID, AccessClass);

		else switch (AccessClass) {
			case AC_STUDENT:
				if (c == "c") { cout << c; }
				else if (c == "h") { cout << c; }
				else if (c == "s") { cout << c; }
				else if (c == "r") { cout << c; }
				break;

			case AC_LECTURER:
				if (c == "c1") { cout << c; }
				else if (c == "c2") { cout << c; }
				else if (c == "a1") { cout << c; }
				else if (c == "a2") { cout << c; }
				else if (c == "s1") { cout << c; }
				else if (c == "s2") { cout << c; }
				else if (c == "s3") { cout << c; }
				break;

			case AC_ADMIN:
				if (c == "t1") { cout << c; }
				else if (c == "t2") { cout << c; }
				else if (c == "t3") { cout << c; }
				else if (c == "t4") { cout << c; }
				else if (c == "t5") { cout << c; }
				else if (c == "t6") { cout << c; }
				else if (c == "t7") { cout << c; }
				else if (c == "y1") { cout << c; }
				else if (c == "y2") { cout << c; }
				else if (c == "y3") { cout << c; }
				else if (c == "y4") { cout << c; }
				else if (c == "y5") { cout << c; }
				else if (c == "y6") { cout << c; }
				else if (c == "y7") { cout << c; }
				else if (c == "y8") { cout << c; }
				else if (c == "c1") { cout << c; }
				else if (c == "c2") { cout << c; }
				else if (c == "c3") { cout << c; }
				else if (c == "c4") { cout << c; }
				else if (c == "c5") { cout << c; }
				else if (c == "c6") { cout << c; }
				else if (c == "c7") { cout << c; }
				else if (c == "l1") { cout << c; }
				else if (c == "l2") { cout << c; }
				else if (c == "l3") { cout << c; }
				else if (c == "l4") { cout << c; }
				else if (c == "s1") { cout << c; }
				else if (c == "s2") { cout << c; }
				else if (c == "s3") { cout << c; }
				else if (c == "a1") { cout << c; }
				else if (c == "a2") { cout << c; }
				else if (c == "a3") { cout << c; }
				break;
		}

		cout << "\n";

	} while (1);
}