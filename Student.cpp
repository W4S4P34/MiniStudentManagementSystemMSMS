#include "Student.h"

void StudentList::AddStudent(Student New) {
	node * newnode = new node{ New, nullptr };
	newnode->next = head;
	head = newnode;
}

StudentList::~StudentList() {
	while (head != nullptr) {
		node * current = head;
		head = current->next;
		delete current;
	}
}

void ImportStudents(const string & FilePath, const string & ClassID) {
	fstream ExistingClass;
	ExistingClass.open(GetPath("Classes/" + ClassID + ".txt"), fstream::in);
	if (ExistingClass.is_open()) {
		ExistingClass.close();
		cout << "Class " << ClassID << " already exists. Operation aborted.\n";
		return;
	}

	ifstream file;
	file.open(GetPath("../import/student_info/" + FilePath));

	if (!file.is_open()) {
		// return instead of forcefully killing the whole program
		cout << "ERROR: Unable to open student list.\n";
		return;
	}

	StudentList temp;
	string skip;
	string ID, LastName, FirstName, Gender;
	Birth DOB;

	// skip the first line
	getline(file, skip);
	while (!file.eof())
	{
		getline(file, skip, ',');
		getline(file, ID, ',');
		getline(file, LastName, ',');
		getline(file, FirstName, ',');
		getline(file, Gender, ',');
		file >> DOB.y;
		file.ignore(1);
		file >> DOB.m;
		file.ignore(1);
		file >> DOB.d;
		temp.AddStudent({ID, LastName, FirstName, Gender, DOB});
		CreateLogin(ID, ClassID);
	}

	UpdateStudentFile(temp, ClassID);

	temp.~StudentList();
	cout << "Successfully imported " << ClassID << ".\n";

	// LoadStudents(CurrentList, ClassID);
}

void ShowInfo(const StudentList & CurrentList, const string & ClassID, const string & StudentID) {
	if (ClassID.empty()) {
		cout << "ERROR: No class loaded.\n";
		return;
	}
	StudentList::node * current = CurrentList.head;
	while (current != nullptr) {
		if (StudentID == current->data.ID) {
			cout << "ID: " << current->data.ID << endl;
			cout << "Full Name: " << current->data.LastName << " " << current->data.FirstName << endl;
			cout << "Gender: " << current->data.Gender << endl;
			cout << "Date of birth (yyyy/mm/dd): " << current->data.DOB.y << '/' << current->data.DOB.m << '/' << current->data.DOB.d << endl;
			return;
		}
		current = current->next;
	}
	cout << "Student " << StudentID << " not found.\n";
}

void UpdateStudentFile(const StudentList & CurrentList, const string & ClassID) {
	ofstream file;
	file.open(GetPath("Classes/" + ClassID + ".txt"));
	if (!file.is_open()) {
		cout << "ERROR: Unable to create file.\n";
		return;
	}
	file << ClassID;
	StudentList::node * current = CurrentList.head;
	while (current != nullptr) {
		file << endl
			<< current->data.ID << ","
			<< current->data.LastName << ","
			<< current->data.FirstName << ","
			<< current->data.Gender << ","
			<< setw(4) << setfill('0') << current->data.DOB.y << "-"
			<< setw(2) << setfill('0') << current->data.DOB.m << "-"
			<< setw(2) << setfill('0') << current->data.DOB.d;
		current = current->next;
	}
	file.close();
	cout << "Successfully updated " << ClassID << ".\n";
}

void LoadStudents(StudentList & CurrentList, const string & ClassID) {
	ifstream file;
	file.open(GetPath("Classes/" + ClassID + ".txt"));

	if (!file.is_open()) {
		cout << "ERROR: Unable to load " << ClassID << ". Check if this class exists.\n";
		return;
	}

	CurrentList.~StudentList();
	
	string skip;
	string ID, LastName, FirstName, Gender;
	string Day, Month, Year;
	Birth DOB;

	// skip the first line
	getline(file, skip);
	while (!file.eof()) {
		getline(file, ID, ',');
		getline(file, LastName, ',');
		getline(file, FirstName, ',');
		getline(file, Gender, ',');
		getline(file, Year, '-');
		getline(file, Month, '-');
		getline(file, Day);
		DOB.y = stoi(Year);
		DOB.m = stoi(Month);
		DOB.d = stoi(Day);
		CurrentList.AddStudent({ ID, LastName, FirstName, Gender, DOB });
	}

	cout << "Successfully loaded " << ClassID << ".\n";
}

void CreateStudent(StudentList & CurrentList, const string & ClassID, const Student & Student_New) {
	if (ClassID.empty()) {
		cout << "ERROR: No class loaded.\n";
		return;
	}
	CurrentList.AddStudent({ Student_New.ID, Student_New.LastName, Student_New.FirstName, Student_New.Gender, Student_New.DOB });
	CreateLogin(Student_New.ID, ClassID);
	UpdateStudentFile(CurrentList, ClassID);
	cout << "Successfully created student " << Student_New.ID << " in class " << ClassID << ".\n";
}

void EditStudent(StudentList & CurrentList, const string & ClassID, const string & StudentID) {
	if (ClassID.empty()) {
		cout << "ERROR: No class loaded.\n";
		return;
	}
	StudentList::node * current = CurrentList.head;
	while (current != nullptr) {
		if (current->data.ID == StudentID)
			break;
		else
			current = current->next;
	}
	if (current == nullptr) {
		cout << "Student " << StudentID << " not found.\n";
		return;
	}

	size_t info;
	cout << "Enter the information you want to change: \n"
		<< "1. Last name" << endl
		<< "2. First name" << endl
		<< "3. Gender" << endl
		<< "4. Day of Birth" << endl;
	cin >> info;

	while (cin.get() != '\n');
	switch (info) {
		case 1: {
			cout << "Enter new Last name: ";
			getline(cin, current->data.LastName, '\n');
			break;
		}
		case 2: {
			cout << "Enter new First name: ";
			getline(cin, current->data.FirstName, '\n');
			break;
		}
		case 3: {
			cout << "Enter new Gender: ";
			getline(cin, current->data.Gender);
			break;
		}
		case 4: {
			cout << "Enter new date of birth (yyyy/mm/dd)\n";
			cout << "Year: "; cin >> current->data.DOB.y;
			cout << "Month: "; cin >> current->data.DOB.m;
			cout << "Day: "; cin >> current->data.DOB.d;
			while (cin.get() != '\n');
			break;
		}
	}
	UpdateStudentFile(CurrentList, ClassID);
	cout << "Student's info edited.\n";
}

void DeleteStudent(StudentList & CurrentList, const string & ClassID, const string & StudentID) {
	if (ClassID.empty()) {
		cout << "ERROR: No class loaded.\n";
		return;
	}
	StudentList::node * current = CurrentList.head;
	StudentList::node * previous = nullptr;

	while (current != nullptr)
	{
		if (current->data.ID == StudentID)
		{
			if (current == CurrentList.head)
			{
				CurrentList.head = CurrentList.head->next;
				delete current;
				break;
			}
			else if (current->next == nullptr) {
				previous->next = nullptr;
				delete current;
				break;
			}
			else
			{
				previous->next = current->next;
				delete current;
				break;
			}
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}

	DeleteLogin(StudentID, ClassID);
	UpdateStudentFile(CurrentList, ClassID);
}

void ListStudents(const StudentList & CurrentList, const string & ClassID) {
	if (ClassID.empty()) {
		cout << "ERROR: No class loaded.\n";
		return;
	}
	StudentList::node * current = CurrentList.head;
	while (current != nullptr) {
		cout << current->data.ID << ", "
			<< current->data.LastName << " " << current->data.FirstName
			<< endl;
		current = current->next;
	}
}

void MoveStudent(StudentList & CurrentList, const string & ClassID_Old, const string & ClassID_New, const string & StudentID) {
	StudentList temp;
	Student CurrentStudent;

	StudentList::node * current = CurrentList.head;
	while (current != nullptr) {
		if (current->data.ID == StudentID) {
			CurrentStudent = current->data;
			break;
		}
		current = current->next;
	}
	if (current == nullptr) {
		cout << "ERROR: Student " << StudentID << " not found.\n";
		return;
	}
	DeleteStudent(CurrentList, ClassID_Old, CurrentStudent.ID);

	LoadStudents(temp, ClassID_New);
	CreateStudent(temp, ClassID_New, CurrentStudent);

	temp.~StudentList();
}
