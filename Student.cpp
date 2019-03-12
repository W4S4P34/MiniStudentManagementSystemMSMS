#include "Student.h"


bool Student::input(const char *path, vector <Student> &a) {
	ifstream im;
	im.open(path);
	if (!im.is_open()) {
		return false;
	}
	else {
		string temp;
		getline(im, temp);
		while (!im.eof()) {
			string No, ID, LastName, FirstName, Gender, BirthDay, BirthMonth, BirthYear;
			getline(im, No, ',');
			getline(im, ID, ',');
			getline(im, LastName, ',');
			getline(im, FirstName, ',');
			getline(im, Gender, ',');
			getline(im, BirthYear, '-');
			getline(im, BirthMonth, '-');
			getline(im, BirthDay);

			a.push_back(Student(ID,LastName,FirstName, Gender, stoi(BirthDay), stoi(BirthMonth), stoi(BirthYear)));
		}
		im.close();
		return true;
	}
}

bool Student::output(const char *path, const vector <Student> &a) {
	ofstream ex;
	ex.open(path);
	if (!ex.is_open()) {
		return false;
	}
	else {
		for (int i = 0; i < a.size(); i++) {
			ex << i + 1 << ","
				<< a[i].id << ","
				<< a[i].lastname << ","
				<< a[i].firstname << ","
				<< a[i].gender << ","
				<< a[i].dob.year << "-"
				<< a[i].dob.month << "-"
				<< a[i].dob.day << endl;

		}
	}
}

