#include "Student.h"

Student *getStudent(string ID, string LN, string FN, string Ge, Birth Bi) {
	Student *Stu = new Student;
	if (Stu != NULL)
	{
		Stu->ID = ID;
		Stu->LastName = LN;
		Stu->FirstName = FN;
		Stu->Gender = Ge;
		Stu->DOB = Bi;
		Stu->next = NULL;
	}
	return Stu;
}

void ImportStudents(const char * filepath, StudentList & list) {
	
	string str;
	string ID, LN, FN, Ge;
	Birth Bi;
	ifstream f;
	f.open(filepath);

	if (!f.is_open()) {
		cerr << "ERROR: Unable to open student list. Forcefully quitting...\n";
		exit(EXIT_FAILURE);
	}

	getline(f, str); // skip the first line
	
	while (!EOF)
	{
		getline(f, str, ',');
		getline(f, ID, ',');
		getline(f, LN, ',');
		getline(f, FN, ',');
		getline(f, Ge, ',');
		f >> Bi.y;
		f.ignore(1);
		f >> Bi.m;
		f.ignore(1);
		f >> Bi.d;
		Student *St = getStudent(ID, LN, FN, Ge, Bi);
		if (St == NULL)
			return;
		if (list.head == NULL) {
			list.head = St;
		}
		else {
			list.head->next = St;
			list.head = St;
		}
	}
}

void ShowInfo(const string ID, const StudentList &list) {
	Student *Cur = list.head;
	while (!Cur) {
		if (ID == Cur->ID) {
			cout << "User's Information:" << endl;
			cout << "ID: ";
			cout << Cur->ID << endl;
			cout << "Last name: ";
			cout << Cur->LastName << endl;
			cout << "First name: ";
			cout << Cur->FirstName << endl;
			cout << "Gender: ";
			cout << Cur->Gender << endl;
			cout << "Date of birth (yyyy/mm/dd): ";
			cout << Cur->DOB.y << '/' << Cur->DOB.m << '/' << Cur->DOB.d;
		}
		Cur = Cur->next;
	}
}

void CreateStudent(StudentList & list) {
	string str;
	string ID, LN, FN, Ge;
	Birth Bi;
	cout << "User's Information:" << endl;
	cout << "ID: ";
	cin >> ID;
	cout << "Last name: ";
	cin >> LN;
	cout << "First name: ";
	cin >> FN;
	cout << "Gender: ";
	cin >> Ge;
	cout << "Date of birth (yyyy/mm/dd):" <<endl;
	cout << "Year: ";
	cin >> Bi.y;
	cout << "Month: ";
	cin >> Bi.m;
	cout << "Day: ";
	cin >> Bi.d;
	Student *St = getStudent(ID, LN, FN, Ge, Bi);
	if (St == NULL)
		return;
	if (list.head == NULL) {
		list.head = St;
	}
	else {
		list.head->next = St;
		list.head = St;
	}
}

#include "Student.h"

void EditStudent(StudentList & list, const string & ID)
{
	int info;

	cout << "Enter the information you want to change (1-4):\n"
		<< "1. Last name" << endl
		<< "2. First name" << endl
		<< "3. Gender" << endl
		<< "4. Day of Birth" << endl;
	cin >> info;

	string option;
	cout << "Are you sure? (Yes/No): ";
	cin >> option;

	for (int i = 0; i < option.length(); i++)
		option[i] = tolower(option[i]);

	if (option == "yes") {
		Student * current = list.head;

		while (current != nullptr)
		{
			if (current->ID == ID)
			{
				switch (info) {
				case 1: {
					cout << "Enter new Last name: ";
					cin >> current->LastName;
					cout << "Student's information is edited" << endl;
					break;
				}
				case 2: {
					cout << "Enter new First name: ";
					cin >> current->FirstName;
					cout << "Student's information is edited" << endl;
					break;
				}
				case 3: {
					cout << "Enter new Gender: ";
					cin >> current->Gender;
					cout << "Student's information is edited" << endl;
					break;
				}
				case 4: {
					cout << "Enter new Day of Birth (d m y): " << endl;
					cin >> current->DOB.y >> current->DOB.m >> current->DOB.d;
					cout << "Student's information is edited" << endl;
					break;
				}
				}
			}
			else
				current = current->next;
		}
	}
	else
		return;
}

void DeleteStudent(StudentList & list, const string & ID)
{
	Student * current = list.head;
	Student * previous = nullptr;

	while (current != nullptr)
	{
		if (current->ID == ID)
		{
			if (current == list.head)
			{
				list.head = list.head->next;
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
}