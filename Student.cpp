#include "Student.h"

void StudentList::Add(const string & ID, const string & LastName, const string & FirstName, const string & Gender, const Birth & DOB)
{
	Student * newStudent = new Student { ID, LastName, FirstName, Gender, DOB, nullptr };
	if (head == nullptr) {
		head = newStudent;
	}
	else {
		Student * append = head;
		while (append->next != nullptr) append = append->next;
		append->next = newStudent;
	}
}

void StudentList::Delete(const string & ID)
{
	StudentList::Student * current = head;
	StudentList::Student * previous = nullptr;

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

StudentList::~StudentList() {
	while (head != nullptr) {
		Student * current = head;
		head = current->next;
		delete current;
	}
}

///////////////////////////////////////////////////////////////////////////////

void ImportClass(const string & FilePath, const string & ClassID)
{
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
		temp.Add(ID, LastName, FirstName, Gender, DOB);
		CreateLogin(ID, ClassID);
	}

	UpdateClass(temp, ClassID);

	temp.~StudentList();
	cout << "Successfully imported " << ClassID << ".\n";

	// LoadStudents(CurrentList, ClassID);
}

void LookupStudent(const StudentList & CurrentList, const string & ClassID, const string & StudentID)
{
	if (ClassID.empty()) {
		cout << "ERROR: No class loaded.\n";
		return;
	}
	StudentList::Student * current = CurrentList.head;
	while (current != nullptr) {
		if (StudentID == current->ID) {
			cout << "ID: " << current->ID << "\n";
			cout << "Full Name: " << current->LastName << " " << current->FirstName << "\n";
			cout << "Gender: " << current->Gender << "\n";
			cout << "Date of birth (yyyy/mm/dd): " << current->DOB.y << '/' << current->DOB.m << '/' << current->DOB.d << "\n";
			return;
		}
		current = current->next;
	}
	cout << "Student " << StudentID << " not found.\n";
}

void UpdateClass(const StudentList & CurrentList, const string & ClassID)
{
	ofstream file;
	file.open(GetPath("Classes/" + ClassID + ".txt"));
	if (!file.is_open()) {
		cout << "ERROR: Unable to create file.\n";
		return;
	}
	file << ClassID;
	StudentList::Student * current = CurrentList.head;
	while (current != nullptr) {
		file << "\n"
			<< current->ID << ","
			<< current->LastName << ","
			<< current->FirstName << ","
			<< current->Gender << ","
			<< setw(4) << setfill('0') << current->DOB.y << "-"
			<< setw(2) << setfill('0') << current->DOB.m << "-"
			<< setw(2) << setfill('0') << current->DOB.d;
		current = current->next;
	}
	file.close();
	cout << "Successfully updated " << ClassID << ".\n";
}

void LoadClass(StudentList & CurrentList, const string & ClassID)
{
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
		CurrentList.Add(ID, LastName, FirstName, Gender, DOB);
	}

	cout << "Successfully loaded " << ClassID << ".\n";
}

void CreateStudent(StudentList & CurrentList, const string & ClassID, const StudentList::Student & Student_New)
{
	// rudimentary date checking
	if (
		Student_New.ID.empty()
		|| Student_New.LastName.empty()
		|| Student_New.FirstName.empty()
		|| Student_New.Gender.empty()
		|| Student_New.DOB.y < 0
		|| (Student_New.DOB.m < 1 || Student_New.DOB.m > 12)
		|| (Student_New.DOB.d < 1 || Student_New.DOB.d > 31)
	) {
		cout << "ERORR: Invalid input found.";
		return;
	}

	CurrentList.Add(Student_New.ID, Student_New.LastName, Student_New.FirstName, Student_New.Gender, Student_New.DOB);
	CreateLogin(Student_New.ID, ClassID);
	UpdateClass(CurrentList, ClassID);
	cout << "Successfully created student " << Student_New.ID << " in class " << ClassID << ".\n";
}

void EditStudent(StudentList & CurrentList, const string & ClassID, const string & StudentID)
{
	if (ClassID.empty()) {
		cout << "ERROR: No class loaded.\n";
		return;
	}
	StudentList::Student * current = CurrentList.head;
	while (current != nullptr) {
		if (current->ID == StudentID)
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
		<< "1. Last name" << "\n"
		<< "2. First name" << "\n"
		<< "3. Gender" << "\n"
		<< "4. Day of Birth" << "\n";
	cin >> info;

	while (cin.get() != '\n');
	switch (info) {
		case 1: {
			cout << "Enter new Last name: ";
			getline(cin, current->LastName, '\n');
			break;
		}
		case 2: {
			cout << "Enter new First name: ";
			getline(cin, current->FirstName, '\n');
			break;
		}
		case 3: {
			cout << "Enter new Gender: ";
			getline(cin, current->Gender);
			break;
		}
		case 4: {
			cout << "Enter new date of birth (yyyy/mm/dd)\n";
			cout << "Year: "; cin >> current->DOB.y;
			cout << "Month: "; cin >> current->DOB.m;
			cout << "Day: "; cin >> current->DOB.d;
			while (cin.get() != '\n');
			break;
		}
	}
	UpdateClass(CurrentList, ClassID);
	cout << "Student's info edited.\n";
}

void DeleteStudent(StudentList & CurrentList, const string & ClassID, const string & StudentID)
{
	if (ClassID.empty()) {
		cout << "ERROR: No class loaded.\n";
		return;
	}
	
	CurrentList.Delete(StudentID);
	
	DeleteLogin(StudentID, ClassID);
	UpdateClass(CurrentList, ClassID);
}

void ListStudents(const StudentList & CurrentList, const string & ClassID)
{
	if (ClassID.empty()) {
		cout << "ERROR: No class loaded.\n";
		return;
	}
	StudentList::Student * current = CurrentList.head;
	while (current != nullptr) {
		cout << current->ID << ", "
			<< current->LastName << " " << current->FirstName
			<< "\n";
		current = current->next;
	}
}

void MoveStudent(StudentList & CurrentList, const string & ClassID_Old, const string & ClassID_New, const string & StudentID)
{
	StudentList temp;
	LoadClass(temp, ClassID_New);
	if (temp.head == nullptr) {
		cout << "ERROR: Unable to open class " << ClassID_New << ". Check if the class exists.";
		return;
	}

	StudentList::Student CurrentStudent;
	StudentList::Student * current = CurrentList.head;
	while (current != nullptr) {
		if (current->ID == StudentID) {
			CurrentStudent = *current;
			break;
		}
		current = current->next;
	}
	if (current == nullptr) {
		cout << "ERROR: Student " << StudentID << " not found.\n";
		return;
	}

	DeleteStudent(CurrentList, ClassID_Old, CurrentStudent.ID);
	CreateStudent(temp, ClassID_New, CurrentStudent);

	temp.~StudentList();
}

void ListClass()
{
	fs::path p = GetPath("Classes");
	if (fs::is_empty(p)) {
		cout << "No classes available.\n";
		return;
	}
	for (auto& p : fs::directory_iterator(GetPath("Classes"))) {
		string FileName = p.path().string();
		FileName = FileName.substr(FileName.find_last_of('\\') + 1);
		FileName = FileName.substr(0, FileName.find_last_of('.'));
		cout << FileName << "\n";
	}
}
