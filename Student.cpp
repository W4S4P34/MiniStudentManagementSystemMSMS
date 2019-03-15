#include "Student.h"

void ImportStudents(const string & filepath, StudentList & CurrentList) {
	ifstream file;
	file.open(filepath);

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
	}

	string ClassID;
	do {
		cout << "Enter class ID: ";
		getline(cin, ClassID);
	} while (
		ClassID.empty()
		&& cout << "Invalid class ID.\n"
	);
	for (size_t i = 0; i < ClassID.length(); i++)
		ClassID[i] = ::toupper(ClassID[i]);
	UpdateStudentFile(ClassID, temp);
	cout << "Successfully imported.\n";

	temp.~StudentList();

	LoadStudents(ClassID, CurrentList);
}

void ShowInfo(const string & ID, const StudentList & list) {
	StudentList::node * current = list.head;
	while (current != nullptr) {
		if (ID == current->data.ID) {
			cout << "--------------------" << endl;
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
}

void LoadStudents(const string & ClassID, StudentList & CurrentList) {
	ifstream file;
	file.open(GetPath("Classes/" + ClassID + ".txt"));

	if (!file.is_open()) {
		cout << "ERROR: Unable to load " << ClassID << ". Check if this class exists.\n";
		return;
	}

	CurrentList.~StudentList();

	string skip;
	string ID, LastName, FirstName, Gender;
	Birth DOB;

	// skip the first line
	getline(file, skip);
	streamoff SeekPosition;
	while (!file.eof()) {
		//SeekPosition = file.tellg();
		//getline(file, skip);
		//if (skip == "\n") break;
		//file.seekg(SeekPosition);
		file.ignore(1); // \n
		getline(file, ID, ',');
		getline(file, LastName, ',');
		getline(file, FirstName, ',');
		getline(file, Gender, ',');
		file >> DOB.y;
		file.ignore(1);
		file >> DOB.m;
		file.ignore(1);
		file >> DOB.d;
		CurrentList.AddStudent({ ID, LastName, FirstName, Gender, DOB });
	}

	cout << "Successfully loaded " << ClassID << ".\n";
}

//void CreateStudent(StudentList & list) {
//	string str;
//	string ID, LN, FN, Ge;
//	Birth Bi;
//	cout << "User's Information:" << endl;
//	cout << "ID: ";
//	cin >> ID;
//	cout << "Last name: ";
//	cin >> LN;
//	cout << "First name: ";
//	cin >> FN;
//	cout << "Gender: ";
//	cin >> Ge;
//	cout << "Date of birth (yyyy/mm/dd):" <<endl;
//	cout << "Year: ";
//	cin >> Bi.y;
//	cout << "Month: ";
//	cin >> Bi.m;
//	cout << "Day: ";
//	cin >> Bi.d;
//	list.AddStudent({ ID, LN, FN, Ge, Bi, nullptr });
//}

//void EditStudent(StudentList & list, const string & ID)
//{
//	int info;
//
//	cout << "Enter the information you want to change (1-4):\n"
//		<< "1. Last name" << endl
//		<< "2. First name" << endl
//		<< "3. Gender" << endl
//		<< "4. Day of Birth" << endl;
//	cin >> info;
//
//	string option;
//	cout << "Are you sure? (Yes/No): ";
//	cin >> option;
//
//	for (size_t i = 0; i < option.length(); i++)
//		option[i] = tolower(option[i]);
//
//	if (option == "yes") {
//		StudentList::node * current = list.head;
//
//		while (current != nullptr)
//		{
//			if (current->data.ID == ID)
//			{
//				switch (info) {
//				case 1: {
//					cout << "Enter new Last name: ";
//					cin >> current->data.LastName;
//					cout << "Student's information is edited" << endl;
//					break;
//				}
//				case 2: {
//					cout << "Enter new First name: ";
//					cin >> current->data.FirstName;
//					cout << "Student's information is edited" << endl;
//					break;
//				}
//				case 3: {
//					cout << "Enter new Gender: ";
//					cin >> current->data.Gender;
//					cout << "Student's information is edited" << endl;
//					break;
//				}
//				case 4: {
//					cout << "Enter new Day of Birth (d m y): " << endl;
//					cin >> current->data.DOB.y >> current->data.DOB.m >> current->data.DOB.d;
//					cout << "Student's information is edited" << endl;
//					break;
//				}
//				}
//			}
//			else
//				current = current->next;
//		}
//	}
//	else
//		return;
//}

//void DeleteStudent(StudentList & list, const string & ID)
//{
//	StudentList::node * current = list.head;
//	StudentList::node * previous = nullptr;
//
//	while (current != nullptr)
//	{
//		if (current->data.ID == ID)
//		{
//			if (current == list.head)
//			{
//				list.head = list.head->next;
//				delete current;
//				break;
//			}
//			else
//			{
//				previous->next = current->next;
//				delete current;
//				break;
//			}
//		}
//		else
//		{
//			previous = current;
//			current = current->next;
//		}
//	}
//}