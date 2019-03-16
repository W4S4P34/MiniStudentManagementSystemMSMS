#include "Login.h"

bool LoginFilesExist() {
	ifstream test;
	bool check = true;

	test.open(GetPath(LOGIN_LIST_ADMIN));
	if (!test.is_open()) {
		cout << "Admin login list does not exist.\n";
		check = false;
	}

	test.open(GetPath(LOGIN_LIST_LECTURER));
	if (!test.is_open()) {
		cout << "Lecturer login list does not exist.\n";
		check = false;
	}

	test.open(GetPath(LOGIN_LIST_STUDENT));
	if (!test.is_open()) {
		cout << "Student login list does not exist.\n";
		check = false;
	}

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
	unsigned char c;
	while ((c = _getch()) != RETURN) {
		if (c == BACKSPACE) {
			if (Password.length() != 0) {
				cout << "\b \b";
				Password.resize(Password.size() - 1);
			}
		}
		else if (c == 0 || c == 224) {
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
	ifstream LoginFile;
	char AccessClass;

	if (ID.substr(0, 5) == "admin") {
		LoginFile.open(GetPath(LOGIN_LIST_ADMIN));
		AccessClass = AC_ADMIN;
	}
	else if ((ID[0] >= 'A' && ID[0] <= 'Z') || (ID[0] >= 'a' && ID[0] <= 'z')) {
		LoginFile.open(GetPath(LOGIN_LIST_LECTURER));
		AccessClass = AC_LECTURER;
	}
	else if (ID[0] >= '1' && ID[0] <= '9') {
		LoginFile.open(GetPath(LOGIN_LIST_STUDENT));
		AccessClass = AC_STUDENT;
	}
	else {
		return AC_INVALID;
	}

	if (!LoginFile.is_open()) {
		cout << "ERROR: Something went wrong. Check if login files still exist.\n";
		return AC_INVALID;
	}

	if (AccessClass == AC_STUDENT) {
		string ID_compare, Password_compare, ClassID;
		while (!LoginFile.eof()) {
			getline(LoginFile, ID_compare, '@');
			getline(LoginFile, ClassID, ',');
			getline(LoginFile, Password_compare, '\n');
			if (ID_compare == ID && sha1(Password) == Password_compare) {
				LoginFile.close();
				ID = ID_compare + '@' + ClassID;
				return AccessClass;
			}
		}
	}
	else {
		string ID_compare, Password_compare;
		while (!LoginFile.eof()) {
			getline(LoginFile, ID_compare, ',');
			getline(LoginFile, Password_compare, '\n');
			if (ID_compare == ID && sha1(Password) == Password_compare) {
				LoginFile.close();
				return AccessClass;
			}
		}
	}
	return AC_INVALID;
}

void ChangePassword(const string & ID, const char & AccessClass, const string & Password_New) {
	fstream LoginFile;
	switch (AccessClass) {
		case AC_ADMIN:
			LoginFile.open(GetPath(LOGIN_LIST_ADMIN));
			break;
		case AC_LECTURER:
			LoginFile.open(GetPath(LOGIN_LIST_LECTURER));
			break;
		case AC_STUDENT:
			LoginFile.open(GetPath(LOGIN_LIST_STUDENT));
			break;
	}

	if (!LoginFile.is_open()) {
		cout << "ERROR: Something went wrong. Check if login files still exist.\n";
		return;
	}
	else {
		string ID_compare, skip;
		streamoff SeekPosition;
		while (!LoginFile.eof()) {
			SeekPosition = LoginFile.tellg();
			getline(LoginFile, ID_compare, ',');
			getline(LoginFile, skip);
			if (ID_compare == ID) {
				LoginFile.seekg(SeekPosition);
				LoginFile << ID << ',' << sha1(Password_New);
				cout << "Password changed.";
				break;
			}
		}
	}

	LoginFile.close();
}

void LoginList::Add(string ID, string Password) {
	node * newnode = new node{ ID, Password, nullptr };
	newnode->next = head;
	head = newnode;
}

void LoginList::Remove(string ID) {
	node * current = head;
	node *previous = nullptr;
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

void CreateLogin(const string & StudentID, const string & ClassID) {
	fstream LoginFile;
	LoginFile.open(GetPath(LOGIN_LIST_STUDENT), fstream::app);
	LoginFile << StudentID << '@' << ClassID << ",da39a3ee5e6b4b0d3255bfef95601890afd80709" << endl;
	LoginFile.close();
}

void CreateLogin(const string & LecturerID) {
	fstream LoginFile;
	LoginFile.open(GetPath(LOGIN_LIST_LECTURER), fstream::app);
	LoginFile << LecturerID << ",da39a3ee5e6b4b0d3255bfef95601890afd80709" << endl;
	LoginFile.close();
}

void DeleteLogin(const string & StudentID, const string & ClassID) {
	string ID, Password, Check;
	string ID_to_Compare = StudentID + '@' + ClassID;
	fstream LoginFile;
	LoginList LoginList;

	LoginFile.open(GetPath(LOGIN_LIST_STUDENT), fstream::in);
	while (!LoginFile.eof()) {
		getline(LoginFile, Check);
		if (
			Check.empty()
			|| Check == "\n" // trailing newline
		) continue;
		ID = Check.substr(0, Check.find_first_of(','));
		Password = Check.substr(Check.find_first_of(',') + 1);
		LoginList.Add(ID, Password);
	}
	LoginList.Remove(ID_to_Compare);
	LoginFile.close();

	LoginFile.open(GetPath(LOGIN_LIST_STUDENT), fstream::out);
	LoginList::node * current = LoginList.head;
	while (current != nullptr) {
		LoginFile << current->ID << ',' << current->Password << endl;
		current = current->next;
	}
	LoginFile.close();
}

void DeleteLogin(const string & LecturerID) {
	string ID, Password, Check;
	fstream LoginFile;
	LoginList LoginList;

	LoginFile.open(GetPath(LOGIN_LIST_LECTURER), fstream::in);
	while (!LoginFile.eof()) {
		getline(LoginFile, Check);
		if (
			Check.empty()
			|| Check == "\n" // trailing newline
			) continue;
		ID = Check.substr(0, Check.find_first_of(','));
		Password = Check.substr(Check.find_first_of(',') + 1);
		LoginList.Add(ID, Password);
	}
	LoginList.Remove(LecturerID);
	LoginFile.close();

	LoginFile.open(GetPath(LOGIN_LIST_LECTURER), fstream::out);
	LoginList::node * current = LoginList.head;
	while (current != nullptr) {
		LoginFile << current->ID << ',' << current->Password << endl;
		current = current->next;
	}
	LoginFile.close();
}
