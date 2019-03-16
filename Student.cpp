#include "Student.h"

void ImportStudents(string & ClassID, StudentList & CurrentList) {
	cout << "Enter filename: ";
	string filename;
	getline(cin, filename);
	cout << GetPath("../import/student_info/" + filename) << endl;

	cout << "Enter class ID: ";
	getline(cin, ClassID);
	if (ClassID.empty()) {
		cout << "Invalid class ID.\n";
		return;
	}
	for (size_t i = 0; i < ClassID.length(); i++)
		ClassID[i] = ::toupper(ClassID[i]);

	fstream ExistingClass;
	ExistingClass.open(GetPath("Classes/" + ClassID + ".txt"), fstream::in);
	if (ExistingClass.is_open()) {
		ExistingClass.close();
		cout << "Class " << ClassID << " already exists. Operation aborted.\n";
		return;
	}

	ifstream file;
	file.open(GetPath("../import/student_info/" + filename));

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

	UpdateStudentFile(ClassID, temp);
	cout << "Successfully imported.\n";

	temp.~StudentList();

	LoadStudents(ClassID, CurrentList);
}

void ShowInfo(const string & ID, const StudentList & list) {
	StudentList::node * current = list.head;
	while (current != nullptr) {
		if (ID == current->data.ID) {
			cout << "ID: " << current->data.ID << endl;
			cout << "Full Name: " << current->data.LastName << " " << current->data.FirstName << endl;
			cout << "Gender: " << current->data.Gender << endl;
			cout << "Date of birth (yyyy/mm/dd): " << current->data.DOB.y << '/' << current->data.DOB.m << '/' << current->data.DOB.d << endl;
			return;
		}
		current = current->next;
	}
	cout << "Student " << ID << " not found.\n";
}

void UpdateStudentFile(const string & ClassID, const StudentList & list) {
	ofstream file;
	file.open(GetPath("Classes/" + ClassID + ".txt"));
	if (!file.is_open()) {
		cout << "ERROR: Unable to create file.\n";
		return;
	}
	file << ClassID;
	StudentList::node * current = list.head;
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

void LoadStudents(string & ClassID, StudentList & CurrentList) {
	for (size_t i = 0; i < ClassID.length(); i++)
		ClassID[i] = ::toupper(ClassID[i]);

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

void CreateStudent(const string & ClassID, StudentList & list) {
	string ID, LastName, FirstName, Gender;
	Birth DOB;
	cout << "ID: "; getline(cin, ID);
	cout << "Last name: "; getline(cin, LastName);
	cout << "First name: "; getline(cin, FirstName);
	cout << "Gender: "; getline(cin, Gender);
	cout << "Birth/Year: "; cin >> DOB.y;
	cout << "Birth/Month: "; cin >> DOB.m;
	cout << "Birth/Day: "; cin >> DOB.d;
	while (cin.get() != '\n');
	list.AddStudent({ ID, LastName, FirstName, Gender, DOB });
	CreateLogin(ID, ClassID);
	UpdateStudentFile(ClassID, list);
	cout << "Successfully created student " << ID << " in class " << ClassID << ".\n";
}

void EditStudent(StudentList & list, const string & ID, const string & ClassID) {
	StudentList::node * current = list.head;
	while (current != nullptr) {
		if (current->data.ID == ID)
			break;
		else
			current = current->next;
	}
	if (current == nullptr) {
		cout << "Student " << ID << " not found.\n";
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
	UpdateStudentFile(ClassID, list);
	cout << "Student's info edited.\n";
	UpdateStudentFile(ClassID, list);
}

void DeleteStudent(StudentList & list, const string & ID, const string & ClassID)
{
	StudentList::node * current = list.head;
	StudentList::node * previous = nullptr;

	while (current != nullptr)
	{
		if (current->data.ID == ID)
		{
			if (current == list.head)
			{
				list.head = list.head->next;
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

	DeleteLogin(ID, ClassID);
	UpdateStudentFile(ClassID, list);
}

void ListStudents(const StudentList & list) {
	StudentList::node * current = list.head;
	while (current != nullptr) {
		cout << current->data.ID << ", "
			<< current->data.LastName << " " << current->data.FirstName
			<< endl;
		current = current->next;
	}
}