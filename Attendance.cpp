#include "Attendance.h"

void AttendanceList::Add(const string & ID, const string & CheckIns)
{
	Attendance * newnode = new Attendance{ ID, CheckIns, nullptr };
	if (head == nullptr) {
		head = newnode;
	}
	else {
		Attendance * append = head;
		while (append->next != nullptr) append = append->next;
		append->next = newnode;
	}
}

void AttendanceList::Delete(const string & ID)
{
	AttendanceList::Attendance * current = head;
	AttendanceList::Attendance * previous = nullptr;

	while (current != nullptr) {
		if (current->ID == ID) {
			if (current == head) {
				head = head->next;
				delete current;
				break;
			}
			else if (current->next == nullptr) {
				previous->next = nullptr;
				delete current;
				break;
			}
			else {
				previous->next = current->next;
				delete current;
				break;
			}
		}
		else {
			previous = current;
			current = current->next;
		}
	}
}

AttendanceList::~AttendanceList()
{
	while (head != nullptr) {
		Attendance * current = head;
		head = current->next;
		delete current;
	}
}

///////////////////////////////////////////////////////////////////////////////

void LoadAttendance(AttendanceList & List, const string & CoursePath)
{
	ifstream file;
	file.open(GetPath("Courses/" + CoursePath + "_Attendance.txt"));
	if (!file.is_open()) {
		cout << "ERROR: Unable to open attendance list.";
		return;
	}

	string test;
	string ID, CheckIns;
	streamoff BeginOfLine;
	while (!file.eof()) {
		BeginOfLine = file.tellg();
		getline(file, test);
		if (test.empty() || test == "\n")
			break;
		file.seekg(BeginOfLine);

		getline(file, ID, ',');
		getline(file, CheckIns);

		List.Add(ID, CheckIns);
	}
	file.close();
}

void UpdateAttendance(const AttendanceList & List, const string & CoursePath)
{
	ofstream file;
	file.open(GetPath("Courses/" + CoursePath + "_Attendance.txt"));
	if (!file.is_open()) {
		cout << "ERROR: Unable to open attendance list.";
		return;
	}

	AttendanceList::Attendance * current = List.head;
	while (current != nullptr) {
		file << current->ID << "," << current->CheckIns << "\n";
		current = current->next;
	}
	file.close();
}

void ImportAttendance(const string & FileName, const string & CoursePath)
{
	ifstream file_in;
	file_in.open(GetPath("../Import/Attendance/" + FileName + ".csv"));
	ofstream file_out;
	file_out.open(GetPath(CoursePath + "/Attendance.txt"));
	if (!file_in.is_open() || !file_out.is_open()) {
		cout << "ERROR: Unable to import attendance list.";
		return;
	}

	string skip, copy;
	getline(file_in, skip);
	while (!file_in.eof()) {
		getline(file_in, copy);
		file_out << copy << "\n";
	}
	file_in.close();
	file_out.close();
}

void ExportAttendance(const string & FileName, const AttendanceList & List, const string & CoursePath)
{
	ofstream file;
	file.open(GetPath("../Export/Attendance/" + FileName + ".csv"));
	if (!file.is_open()) {
		cout << "ERROR: Unable to export attendance list.";
		return;
	}

	file << "ID,CheckIns" << "\n";

	AttendanceList::Attendance * current = List.head;
	while (current != nullptr) {
		file << current->ID << "," << current->CheckIns << "\n";
		current = current->next;
	}
	file.close();
}

void ViewAttendance(const AttendanceList & List) {
	AttendanceList::Attendance * current = List.head;
	while (current != nullptr) {
		cout << current->ID << "," << current->CheckIns << "\n";
		current = current->next;
	}
}

void ViewAttendance(const AttendanceList & List, const string & StudentID)
{
	AttendanceList::Attendance * current = List.head;
	while (current != nullptr && current->ID != StudentID)
		current = current->next;
	if (current == nullptr) {
		cout << "Student " << StudentID << " not found.\n";
		return;
	}

	cout << "ID: " << StudentID
		<< "\n"
		<< "Check-in marks: " << current->CheckIns;
}

void EditAttendance(AttendanceList & List, const string & CoursePath, const string & StudentID, const size_t & Week, const bool & State) {
	AttendanceList::Attendance * current = List.head;
	while (current != nullptr && current->ID != StudentID)
		current = current->next;
	if (current == nullptr) {
		cout << "Student " << StudentID << " not found.\n";
		return;
	}

	if (Week < 1 || Week > current->CheckIns.length()) {
		cout << "Invalid week number.\n";
		return;
	}
	current->CheckIns[Week - 1] = (State ? 'x' : '-');

	UpdateAttendance(List, CoursePath);
	cout << "Attendance for student " << StudentID << " updated.";
}

///////////////////////////////////////////////////////////////////////////////

void CheckIn_Menu(const string & StudentID) {
	Timetable StudentTimetable;
	StudentTimetable.Load(StudentID);

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

	int selection;
	do {
		cout << "Choose course (Enter a number): "; cin >> selection;
		if (selection < 1 || selection > i) {
			cout << "Invalid choice.\n";
		}
	} while (selection < 1 || selection > i);

	current = StudentTimetable.head;
	for (int j = 1; j < selection; j++)
		current = current->next;

	CheckIn(current->CoursePath, StudentID);
}

void CheckIn(const string & CoursePath, const string & StudentID) {
	time_t CurrentTime, CourseStartTime, CourseEndTime;
	tm CurrentTime_tm = {0}, CourseStartTime_tm = {0}, CourseEndTime_tm ={0};
	string skip;

	time(&CurrentTime);

	fstream CourseInfoFile;
	CourseInfoFile.open(GetPath("Courses/" + CoursePath + "_Info.txt"), fstream::in);
	getline(CourseInfoFile, skip);
	getline(CourseInfoFile, skip);
	CourseInfoFile >> CourseStartTime;
	CourseInfoFile >> CourseEndTime;

	size_t DC = ceil((CourseEndTime - CourseStartTime) / (60 * 60 * 24 * 7));
	size_t CW = ceil((CurrentTime - CourseStartTime) / (60 * 60 * 24 * 7));

	if (CW < 0 || CW > DC) {
		cout << "System hasn't opened yet. Please come back later.\n";
		while (cin.get() != '\n');
		return;
	}

	localtime_s(&CurrentTime_tm, &CurrentTime);
	localtime_s(&CourseStartTime_tm, &CourseStartTime);
	localtime_s(&CourseEndTime_tm, &CourseEndTime);

	if (CurrentTime_tm.tm_wday != CourseStartTime_tm.tm_wday) {
		cout << "System hasn't opened yet. Please come back later.\n";
		while (cin.get() != '\n');
		return;
	}

	if ((CurrentTime_tm.tm_hour < CourseStartTime_tm.tm_hour) || (CurrentTime_tm.tm_hour == CourseStartTime_tm.tm_hour && CurrentTime_tm.tm_min < CourseStartTime_tm.tm_min) ||
		(CurrentTime_tm.tm_hour > CourseEndTime_tm.tm_hour) || (CurrentTime_tm.tm_hour == CourseEndTime_tm.tm_hour && CurrentTime_tm.tm_min > CourseEndTime_tm.tm_min)) {
		cout << "System hasn't opened yet. Please come back later.\n";
		while (cin.get() != '\n');
		return;
	}

	AttendanceList List;
	LoadAttendance(List, CoursePath);
	AttendanceList::Attendance * current = List.head;
	while (current != nullptr) {
		if (current->ID == StudentID) {
			current->CheckIns[CW] = 'x';
			break;
		}
		current = current->next;
	}
	UpdateAttendance(List, CoursePath);
}
