#pragma once

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct Birth {
	short d, m;
	int y;
};

struct Student {
	// ID and info of current node
	string ID;
	string LastName, FirstName;
	string Gender;

	// next node
	Student * next;
};

struct StudentList {
	// each student is a node
	Student * head = nullptr;
};

Student *getStudent();
void ImportStudents(const char * filepath, StudentList & list);
void ExportStudents(const char * filepath, const StudentList & list);
void CreateStudent(StudentList & list);
void EditStudent(StudentList & list, const string & ID);
void DeleteStudent(StudentList & list, const string & ID);
