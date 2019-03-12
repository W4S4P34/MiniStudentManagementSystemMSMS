#include "Login.h"

// Student: ID-BirthDM
// Lecturer: the usual (nhminh)
// Admin: admin1337
char LoginMenu() {
	char r;
	do {
		string username, password;
		cout << "(Type \"quit\" in username to quit.)\n";
		cout << "Username: ";
		cin >> username;
		if (username == "quit") exit(EXIT_SUCCESS);
		cout << "Password: ";
		cin >> password;
		r = Authenticate(username, password);
	} while (r == -1 && cout << "Invalid login details.\n\n");
	return r;
}

// 0=admin, 1=student, 2=lecturer, -1=invalid
char Authenticate(string username, string password) {
	ifstream LoginList;

	// ADMIN
	if (username.substr(0, 5) == "admin") {
		LoginList.open(LOGIN_ADMIN);
		if (!LoginList.is_open()) {
			cout << "Unable to open file for login. Forcefully exiting...\n";
			exit(EXIT_FAILURE);
		}
		while (!LoginList.eof()) {
			string usernameToCompare, passwordToCompare;
			getline(LoginList, usernameToCompare, ',');
			getline(LoginList, passwordToCompare);
			if (username == usernameToCompare && password == passwordToCompare)
				return 0;
			else
				return -1;
		}
	}

	// STUDENT
	else if (username[0] >= '1' && username[0] <= '9') {
		LoginList.open(LOGIN_STUDENT);
		if (!LoginList.is_open()) {
			cout << "Unable to open file for login. Forcefully exiting...\n";
			exit(EXIT_FAILURE);
		}
		while (!LoginList.eof()) {
			string usernameToCompare, passwordToCompare;
			getline(LoginList, usernameToCompare, ',');
			getline(LoginList, passwordToCompare);
			if (username == usernameToCompare && password == passwordToCompare)
				return 1;
			else
				return -1;
		}
	}

	// LECTURER
	else if ((username[0] >= 'a' &&  username[0] <= 'z') || (username[0] >= 'A' && username[0] <= 'Z')) {
		LoginList.open(LOGIN_LECTURER);
		if (!LoginList.is_open()) {
			cout << "Unable to open file for login. Forcefully exiting...\n";
			exit(EXIT_FAILURE);
		}
		while (!LoginList.eof()) {
			string usernameToCompare, passwordToCompare;
			getline(LoginList, usernameToCompare, ',');
			getline(LoginList, passwordToCompare);
			if (username == usernameToCompare && password == passwordToCompare)
				return 2;
			else
				return -1;
		}
	}

	else {
		return -1;
	}
}
