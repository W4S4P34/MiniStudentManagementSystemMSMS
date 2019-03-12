#include "Menu.h"

/*----------------------------------------------------------------*/

//Menu Student

/*----------------------------------------------------------------*/

//Menu Lecturer

/*----------------------------------------------------------------*/


char Menu_Admin() {
	cout << "ADMIN MENU (Note: choices are case-insensitive.)\n\n"
		<< "[-] Log out\n"
		<< "[*] Change password\n"
		<< "\n"
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
		<< "[A3] Export attendance list (to a CSV file)\n"
		<< endl;

	char r;
	do {
		cout << "> Choose: ";
		string c;
		cin >> c;
		transform(c.begin(), c.end(), c.begin(), ::tolower);

		if (c == "-") { r = -2; cout << "Logging out..."; }
		else if (c == "*") { r = 0; cout << c; }
		else if (c == "t1") { r = 0; cout << c; }
		else if (c == "t2") { r = 0; cout << c; }
		else if (c == "t3") { r = 0; cout << c; }
		else if (c == "t4") { r = 0; cout << c; }
		else if (c == "t5") { r = 0; cout << c; }
		else if (c == "t6") { r = 0; cout << c; }
		else if (c == "t7") { r = 0; cout << c; }
		else if (c == "y1") { r = 0; cout << c; }
		else if (c == "y2") { r = 0; cout << c; }
		else if (c == "y3") { r = 0; cout << c; }
		else if (c == "y4") { r = 0; cout << c; }
		else if (c == "y5") { r = 0; cout << c; }
		else if (c == "y6") { r = 0; cout << c; }
		else if (c == "y7") { r = 0; cout << c; }
		else if (c == "y8") { r = 0; cout << c; }
		else if (c == "c1") { r = 0; cout << c; }
		else if (c == "c2") { r = 0; cout << c; }
		else if (c == "c3") { r = 0; cout << c; }
		else if (c == "c4") { r = 0; cout << c; }
		else if (c == "c5") { r = 0; cout << c; }
		else if (c == "c6") { r = 0; cout << c; }
		else if (c == "c7") { r = 0; cout << c; }
		else if (c == "l1") { r = 0; cout << c; }
		else if (c == "l2") { r = 0; cout << c; }
		else if (c == "l3") { r = 0; cout << c; }
		else if (c == "l4") { r = 0; cout << c; }
		else if (c == "s1") { r = 0; cout << c; }
		else if (c == "s2") { r = 0; cout << c; }
		else if (c == "s3") { r = 0; cout << c; }
		else if (c == "a1") { r = 0; cout << c; }
		else if (c == "a2") { r = 0; cout << c; }
		else if (c == "a3") { r = 0; cout << c; }
		
		else { r = -1; cout << "Invalid choice.\n"; }
	} while (r == -1);
	return r;
}