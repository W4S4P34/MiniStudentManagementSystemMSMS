#include "Login.h"

void LoginMenu(string & ID, char & AccessClass) {
	cout << "(Type \"quit\" in ID to quit.)\n\n";
	do {
		
		cout << "ID: ";
		getline(cin, ID);
		if (ID == "quit") exit(EXIT_SUCCESS);
		string Password;
		cout << "Password: ";
		// getline(cin, Password);
		Password = GetPassword();
		AccessClass = Authenticate(ID, Password);
	} while (
		AccessClass == AC_INVALID
		&& cout << "\nInvalid login details.\n\n"
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
				// Password.pop_back() : C++11
			}
		}
		else if (c == 0 || c == 224) {
			_getch();
			continue;
		}
		else if (c >= 32 && c <= 126) {
			cout << " \b*";
			Password.push_back(c);
		}
	}
	return Password;
}

char Authenticate(const string & ID, const string & Password) {
	ifstream LoginList;
	char AccessClass;

	if (ID.substr(0, 5) == "admin") {
		LoginList.open(LOGIN_LIST_ADMIN);
		AccessClass = AC_ADMIN;
	}
	else if ((ID[0] >= 'A' && ID[0] <= 'Z') || (ID[0] >= 'a' && ID[0] <= 'z')) {
		LoginList.open(LOGIN_LIST_LECTURER);
		AccessClass = AC_LECTURER;
	}
	else if (ID[0] >= '1' && ID[0] <= '9') {
		LoginList.open(LOGIN_LIST_STUDENT);
		AccessClass = AC_STUDENT;
	}
	else {
		return -1;
	}

	if (!LoginList.is_open()) {
		cerr << "ERROR: Unable to open login list. Forcefully quitting...\n";
		exit(EXIT_FAILURE);
	}

	string ID_compare, Password_compare;
	while (!LoginList.eof()) {
		getline(LoginList, ID_compare, ',');
		getline(LoginList, Password_compare, '\n');
		if (ID_compare == ID && sha1(Password) == Password_compare) {
				LoginList.close();
				return AccessClass;
		}
	}
	return -1;
}

void ChangePassword(const string & ID, const char & AccessClass) {
	fstream LoginList;
	switch (AccessClass) {
		case AC_ADMIN:
			LoginList.open(LOGIN_LIST_ADMIN);
			break;
		case AC_LECTURER:
			LoginList.open(LOGIN_LIST_LECTURER);
			break;
		case AC_STUDENT:
			LoginList.open(LOGIN_LIST_STUDENT);
			break;
	}

	if (!LoginList.is_open()) {
		cerr << "ERROR: Unable to open login list. Forcefully quitting...\n";
		exit(EXIT_FAILURE);
	}

	string Password_new;
	string Password_new_re;
	cout << "Enter new password: ";
	getline(cin, Password_new);
	cout << "Re-enter new password: ";
	getline(cin, Password_new_re);

	if (Password_new != Password_new_re) {
		cerr << "Passwords do not match. Operation aborted.\n";
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