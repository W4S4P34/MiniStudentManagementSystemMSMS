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
	file.open(GetPath(CoursePath + "/Attendance.txt"));
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
	file.open(GetPath(CoursePath + "/Attendance.txt"));
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
