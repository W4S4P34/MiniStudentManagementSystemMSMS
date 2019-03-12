#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


struct date {
	int day;
	int month;
	int year;
};

class Student {
	//attributes
private:
	string id;
	string lastname;
	string firstname;
	string gender;
	date dob;
	//constructors
public:
	Student( string ID, string LASTNAME, string FIRSTNAME, string GENDER, int day, int month, int year) {
		id = ID;
		lastname = LASTNAME;
		firstname = FIRSTNAME;
		gender = GENDER;
		dob.day = day; dob.month = month; dob.year = year;
	}
	//method
public:
	static bool input(const char *path, vector <Student> &a);
	static bool output(const char *path, const vector <Student> &a);
};

