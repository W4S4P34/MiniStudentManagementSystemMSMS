#include "Lecturer.h"

void LecturerList::Add(const string & ID, const string & LastName, const string & FirstName, const string & Gender)
{
	Lecturer * newLecturer = new Lecturer{ ID, LastName, FirstName, Gender };

	if (head == nullptr) {
		head = newLecturer;
	}
	else {
		Lecturer * append = head;
		while (append->next != nullptr) append = append->next;
		append->next = newLecturer;
	}
}

void LecturerList::Delete(const string & ID)
{
	LecturerList::Lecturer * current = head;
	LecturerList::Lecturer * previous = nullptr;

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

LecturerList::~LecturerList() {
	while (head != nullptr) {
		Lecturer * current = head;
		head = current->next;
		delete current;
	}
}

///////////////////////////////////////////////////////////////////////////////

void LowerString(string & string)
{
	for (size_t i = 0; i < string.length(); i++)
		string[i] = ::tolower(string[i]);
}

string GenerateID(const string & LastName, const string & FirstName)
{
	string ID;

	string LastName_copy = LastName;
	LowerString(LastName_copy);
	while (LastName_copy.length() != 0)
	{
		ID += LastName_copy.substr(0, 1);
		int cut = LastName_copy.find_first_of(" ");
		if (cut != -1)
			LastName_copy.erase(0, cut + 1);
		else
			break;
	}

	string FirstName_copy = FirstName;
	LowerString(FirstName_copy);
	ID += FirstName_copy;

	return ID;
}

///////////////////////////////////////////////////////////////////////////////

void ImportLecturer(const string & FilePath, LecturerList & CurrentLecturerList) {
	fstream ExistingFile;
	ExistingFile.open(GetPath("Lecturers/Lecturers.txt"), fstream::in);
	if (ExistingFile.is_open()) {
		ExistingFile.close();
		cout << "Lecturer's data file already exists. Operation aborted.\n";
		return;
	}

	ifstream file;
	file.open(GetPath("../Import/Lecturers/" + FilePath));
	if (!file.is_open()) {
		cout << "ERROR: Unable to open lecturer list.\n";
		return;
	}

	LecturerList temp;
	string ID, LastName, FirstName, Gender;
	while (!file.eof())
	{
		getline(file, LastName, ',');
		getline(file, FirstName, ',');
		getline(file, Gender);
		ID = GenerateID(LastName, FirstName);
		temp.Add(ID, LastName, FirstName, Gender);
		CreateLogin(ID);
	}

	UpdateLecturerFile(temp);
	LoadLecturer(CurrentLecturerList);

	temp.~LecturerList();
	cout << "Successfully imported Lecturers's \n";
}

void LookupLecturer(const LecturerList & List, const string & LecturerID)
{
	if (List.head == nullptr) {
		cout << "ERROR: No lecturer loaded.\n";
		return;
	}
	LecturerList::Lecturer * current = List.head;
	while (current != nullptr) {
		if (LecturerID == current->ID) {
			cout << "ID: " << current->ID << endl;
			cout << "Full Name: " << current->LastName << " " << current->FirstName << endl;
			cout << "Gender: " << current->Gender << endl;
			return;
		}
		current = current->next;
	}
	cout << "Lecturer " << LecturerID << " not found.\n";
}

void UpdateLecturerFile(const LecturerList & List)
{
	ofstream file;
	file.open(GetPath("Lecturers/Lecturers.txt"));
	if (!file.is_open()) {
		cout << "ERROR: Unable to create file.\n";
		return;
	}
	LecturerList::Lecturer * current = List.head;
	while (current != nullptr) {
		file << current->ID << ","
			<< current->LastName << ","
			<< current->FirstName << ","
			<< current->Gender << endl;
		current = current->next;
	}
	file.close();
	cout << "Successfully updated Lecturers's data\n";
}

void LoadLecturer(LecturerList & List)
{
	ifstream file;
	file.open(GetPath("Lecturers/Lecturers.txt"));
	if (!file.is_open()) {
		cout << "ERROR: Unable to load Lecturers. Check if this file exists.\n";
		return;
	}

	List.~LecturerList();

	string ID, LastName, FirstName, Gender;
	string Check;
	while (!file.eof()) {
		streamoff BeginOfLine = file.tellg();
		getline(file, Check);
		if (
			Check.empty()
			|| Check == "\n" // trailing newline
			) continue;
		file.seekg(BeginOfLine);
		getline(file, ID, ',');
		getline(file, LastName, ',');
		getline(file, FirstName, ',');
		getline(file, Gender);
		List.Add(ID, LastName, FirstName, Gender);
	}

	cout << "Successfully loaded Lecturers's \n";
}

void CreateLecturer(LecturerList & List, const string & LastName, const string & FirstName, const string & Gender)
{
	if (List.head == nullptr) {
		cout << "ERROR: No lecturer loaded.\n";
		return;
	}
	string ID = GenerateID(LastName, FirstName);
	List.Add(ID, LastName, FirstName, Gender);
	CreateLogin(ID);
	UpdateLecturerFile(List);
	cout << "Successfully created lecturer " << ID << ".\n";
}

void EditLecturer(LecturerList & List, const string & LecturerID)
{
	if (List.head == nullptr) {
		cout << "ERROR: No lecturer loaded.\n";
		return;
	}
	LecturerList::Lecturer * current = List.head;
	while (current != nullptr) {
		if (current->ID == LecturerID)
			break;
		else
			current = current->next;
	}
	if (current == nullptr) {
		cout << "Lecturer " << LecturerID << " not found.\n";
		return;
	}

	size_t info;
	cout << "Enter the information you want to change: \n"
		<< "1. Last name" << endl
		<< "2. First name" << endl
		<< "3. Gender" << endl;
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
	}
	current->ID = GenerateID(current->LastName, current->FirstName);
	UpdateLecturerFile(List);
	cout << "Lecturer's info edited.\n";
}

void DeleteLecturer(LecturerList & List, const string & LecturerID)
{
	if (List.head == nullptr) {
		cout << "ERROR: No lecturer loaded.\n";
		return;
	}
	LecturerList::Lecturer * current = List.head;
	LecturerList::Lecturer * previous = nullptr;

	while (current != nullptr)
	{
		if (current->ID == LecturerID)
		{
			if (current == List.head)
			{
				List.head = List.head->next;
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

	DeleteLogin(LecturerID);
	UpdateLecturerFile(List);
}

void ListLecturer(const LecturerList & List)
{
	if (List.head == nullptr) {
		cout << "ERROR: No lecturer loaded.\n";
		return;
	}
	LecturerList::Lecturer * current = List.head;
	while (current != nullptr) {
		cout << current->ID << ", "
			<< current->LastName << " " << current->FirstName
			<< endl;
		current = current->next;
	}
}
