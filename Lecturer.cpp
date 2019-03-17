#include "Lecturer.h"

void LecturerList::AddLecturer(Lecturer New) {
	node * newnode = new node{ New, nullptr };
	newnode->next = head;
	head = newnode;
}

LecturerList::~LecturerList() {
	while (head != nullptr) {
		node * current = head;
		head = current->next;
		delete current;
	}
}

void LowerString(string & string) {
	for (size_t i = 0; i < string.length(); i++)
		string[i] = ::tolower(string[i]);
}

string GenerateID(const string & LecturerLastName, const string & LecturerFirstName)
{
	string tempLastName = LecturerLastName;
	LowerString(tempLastName);
	string ID;
	while (tempLastName.length() != 0)
	{
		ID += tempLastName.substr(0, 1);
		int cut = tempLastName.find_first_of(" ");
		if (cut != -1)
			tempLastName.erase(0, cut + 1);
		else
			break;
	}
	string tempFirstName = LecturerFirstName;
	LowerString(tempFirstName);
	return ID + tempFirstName;
}

void ImportLecturer(const string & FilePath) {
	fstream ExistingFile;
	ExistingFile.open(GetPath("Lecturers/Lecturers.txt"), fstream::in);
	if (ExistingFile.is_open()) {
		ExistingFile.close();
		cout << "Lecturer's data file already exists. Operation aborted.\n";
		return;
	}

	ifstream file;
	file.open(GetPath("../import/Lecturers/" + FilePath));

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
		temp.AddLecturer({ ID, LastName, FirstName, Gender});
		CreateLogin(ID);
	}

	UpdateLecturerFile(temp);

	temp.~LecturerList();
	cout << "Successfully imported Lecturers's data.\n";
}

void ShowInfo(const LecturerList & CurrentList, const string & LecturerID)
{
	if (CurrentList.head == nullptr) {
		cout << "ERROR: No lecturer loaded.\n";
		return;
	}
	LecturerList::node * current = CurrentList.head;
	while (current != nullptr) {
		if (LecturerID == current->data.ID) {
			cout << "ID: " << current->data.ID << endl;
			cout << "Full Name: " << current->data.LastName << " " << current->data.FirstName << endl;
			cout << "Gender: " << current->data.Gender << endl;
			return;
		}
		current = current->next;
	}
	cout << "Lecturer " << LecturerID << " not found.\n";
}

void UpdateLecturerFile(const LecturerList & CurrentList)
{
	ofstream file;
	file.open(GetPath("Classes/Lecturers/Lecturers.txt"));
	if (!file.is_open()) {
		cout << "ERROR: Unable to create file.\n";
		return;
	}
	LecturerList::node * current = CurrentList.head;
	while (current != nullptr) {
		file << current->data.ID << ","
			<< current->data.LastName << ","
			<< current->data.FirstName << ","
			<< current->data.Gender << endl;
		current = current->next;
	}
	file.close();
	cout << "Successfully updated Lecturers's data\n";
}

void LoadLecturer(LecturerList & CurrentList)
{
	ifstream file;
	file.open(GetPath("Lecturers/Lecturers.txt"));

	if (!file.is_open()) {
		cout << "ERROR: Unable to load Lecturers. Check if this file exists.\n";
		return;
	}


	CurrentList.~LecturerList();

	string ID, LastName, FirstName, Gender;
	string Check;
	while (!file.eof()) {
		getline(file, Check);
		if (
			Check.empty()
			|| Check == "\n" // trailing newline
			) continue;
		getline(file, ID, ',');
		getline(file, LastName, ',');
		getline(file, FirstName, ',');
		getline(file, Gender, ',');
		CurrentList.AddLecturer({ ID, LastName, FirstName, Gender });
	}

	cout << "Successfully loaded Lecturers's data.\n";
}

void CreateLecturer(LecturerList & CurrentList, const Lecturer & Lecturer_New) {
	if (CurrentList.head == nullptr) {
		cout << "ERROR: No lecturer loaded.\n";
		return;
	}
	CurrentList.AddLecturer({ Lecturer_New.ID, Lecturer_New.LastName, Lecturer_New.FirstName, Lecturer_New.Gender });
	CreateLogin(Lecturer_New.ID);
	UpdateLecturerFile(CurrentList);
	cout << "Successfully created lecturer " << Lecturer_New.ID << ".\n";
}

void EditLecturer(LecturerList & CurrentList, const string & LecturerID) {
	if (CurrentList.head == nullptr) {
		cout << "ERROR: No lecturer loaded.\n";
		return;
	}
	LecturerList::node * current = CurrentList.head;
	while (current != nullptr) {
		if (current->data.ID == LecturerID)
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
	}
	current->data.ID = GenerateID(current->data.LastName, current->data.FirstName);
	UpdateLecturerFile(CurrentList);
	cout << "Lecturer's info edited.\n";
}

void DeleteLecturer(LecturerList & CurrentList, const string & LecturerID) {
	if (CurrentList.head == nullptr) {
		cout << "ERROR: No lecturer loaded.\n";
		return;
	}
	LecturerList::node * current = CurrentList.head;
	LecturerList::node * previous = nullptr;

	while (current != nullptr)
	{
		if (current->data.ID == LecturerID)
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

	DeleteLogin(LecturerID);
	UpdateLecturerFile(CurrentList);
}

void ListLecturers(const LecturerList & CurrentList) {
	if (CurrentList.head == nullptr) {
		cout << "ERROR: No lecturer loaded.\n";
		return;
	}
	LecturerList::node * current = CurrentList.head;
	while (current != nullptr) {
		cout << current->data.ID << ", "
			<< current->data.LastName << " " << current->data.FirstName
			<< endl;
		current = current->next;
	}
}