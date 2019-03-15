#include "Login.h"

bool doLoginFilesExist() {
	ifstream test;
	bool check = true;

	test.open(GetPath(LOGIN_LIST_ADMIN));
	if (!test.is_open()) {
		cout << "Admin login list does not exist.\n";
		check = false;
	}
	test.close();

	test.open(GetPath(LOGIN_LIST_LECTURER));
	if (!test.is_open()) {
		cout << "Lecturer login list does not exist.\n";
		check = false;
	}
	test.close();

	test.open(GetPath(LOGIN_LIST_STUDENT));
	if (!test.is_open()) {
		cout << "Student login list does not exist.\n";
		check = false;
	}
	test.close();

	return check;
}

void LoginMenu(string & ID, char & AccessClass) {
	cout << "(Type \"quit\" in ID to quit.)\n\n";
	do {
		
		cout << "ID: ";
		getline(cin, ID);
		if (ID == "quit") exit(EXIT_SUCCESS);
		string Password;
		cout << "Password: ";
		Password = GetPassword();
		cout << "\n";
		AccessClass = Authenticate(ID, Password);
	} while (
		AccessClass == AC_INVALID
		&& cout << "Invalid login details.\n\n"
	);
}

string GetPassword() {
	const char BACKSPACE = 8; // BS
	const char RETURN = 13; // CR; 10=LF

	string Password;
	string skip;
	unsigned char c;
	while ((c = _getch()) != RETURN) {
		if (c == BACKSPACE) {
			if (Password.length() != 0) {
				cout << "\b \b";
				Password.resize(Password.size() - 1);
				// Password.pop_back() : C++11
			}
		}
		else if (c == 0 || c == 224) {
			// _getch();
			cin.clear();
			continue;
		}
		else if (c >= 32 && c <= 126) {
			cout << " \b*";
			Password.push_back(c);
		}
	}
	return Password;
}

char Authenticate(string & ID, const string & Password) {
	ifstream LoginList;
	char AccessClass;

	if (ID.substr(0, 5) == "admin") {
		LoginList.open(GetPath(LOGIN_LIST_ADMIN));
		AccessClass = AC_ADMIN;
	}
	else if ((ID[0] >= 'A' && ID[0] <= 'Z') || (ID[0] >= 'a' && ID[0] <= 'z')) {
		LoginList.open(GetPath(LOGIN_LIST_LECTURER));
		AccessClass = AC_LECTURER;
	}
	else if (ID[0] >= '1' && ID[0] <= '9') {
		LoginList.open(GetPath(LOGIN_LIST_STUDENT));
		AccessClass = AC_STUDENT;
	}
	else {
		return AC_INVALID;
	}

	if (!LoginList.is_open()) {
		cout << "ERROR: Something went wrong. Check if login files still exist.\n";
		return AC_INVALID;
	}

	if (AccessClass == AC_STUDENT) {
		string ID_compare, Password_compare, skip;
		while (!LoginList.eof()) {
			getline(LoginList, ID_compare, '@');
			getline(LoginList, skip, ',');
			getline(LoginList, Password_compare, '\n');
			if (ID_compare == ID && sha1(Password) == Password_compare) {
				LoginList.close();
				ID = ID_compare + '@' + skip;
				return AccessClass;
			}
		}
	}
	else {
		string ID_compare, Password_compare;
		while (!LoginList.eof()) {
			getline(LoginList, ID_compare, ',');
			getline(LoginList, Password_compare, '\n');
			if (ID_compare == ID && sha1(Password) == Password_compare) {
				LoginList.close();
				return AccessClass;
			}
		}
	}
	return AC_INVALID;
}

void ChangePassword(const string & ID, const char & AccessClass) {
	fstream LoginList;
	switch (AccessClass) {
		case AC_ADMIN:
			LoginList.open(GetPath(LOGIN_LIST_ADMIN));
			break;
		case AC_LECTURER:
			LoginList.open(GetPath(LOGIN_LIST_LECTURER));
			break;
		case AC_STUDENT:
			LoginList.open(GetPath(LOGIN_LIST_STUDENT));
			break;
	}

	if (!LoginList.is_open()) {
		cout << "ERROR: Something went wrong. Check if login files still exist.\n";
		return;
	}

	string Password_new;
	string Password_new_re;
	cout << "Enter new password: ";
	Password_new = GetPassword();
	cout << "\n";
	cout << "Re-enter new password: ";
	Password_new_re = GetPassword();
	cout << "\n";

	if (Password_new != Password_new_re) {
		cout << "Passwords do not match. Operation aborted.\n";
	}
	else {
		string ID_compare, skip;
		streamoff SeekPosition;
		while (!LoginList.eof()) {
			SeekPosition = LoginList.tellg();
			getline(LoginList, ID_compare, ',');
			getline(LoginList, skip);
			if (ID_compare == ID) {
				LoginList.seekg(SeekPosition);
				LoginList << ID << ',' << sha1(Password_new);
				cout << "Password changed.";
				break;
			}
		}
	}

	LoginList.close();
}

void CreateLogin(const string & StudentID, const string & ClassID) {
	fstream LoginList;
	LoginList.open(GetPath("Login/Student.txt"), fstream::app);
	LoginList << endl << StudentID << "@" << ClassID << ",da39a3ee5e6b4b0d3255bfef95601890afd80709";
}

void DeleteLogin(const string & StudentID, const string & ClassID) {
	ifstream LoginList;
	LoginList.open(GetPath("Login/Student.txt"));
	Login_LinkedList l;
	string ID, Password, skip;
	string ID_to_Compare = StudentID + '@' + ClassID;
	getline(LoginList, skip);
	while (!LoginList.eof()) {
		getline(LoginList, ID, ',');
		getline(LoginList, Password, '\n');
		l.Add(ID, Password);
	}
	l.Remove(ID_to_Compare);
	LoginList.close();

	//--------------------

	ofstream LoginList_new;
	LoginList_new.open(GetPath("Login/Student.txt"));
	Login_LinkedList::node * current = l.head;
	while (current != nullptr) {
		LoginList_new << endl << current->ID << ',' << current->Password;
		current = current->next;
	}

	LoginList_new.close();
}