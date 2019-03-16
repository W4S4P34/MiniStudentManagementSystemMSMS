#pragma once

#include "_FILES_.h"
#include "Login.h"
#include <iostream>
#include <iomanip> // setw, setfill
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct Birth {
	short d, m;
	int y;
};

struct Student {
	string ID;
	string LastName, FirstName;
	string Gender;
	Birth DOB;
};

struct StudentList {
	struct node {
		Student data;
		node * next;
	};
	node * head = nullptr;

	void AddStudent(Student New);
	~StudentList();
};

// CurrentList, ClassID, StudentID

void ImportStudents(StudentList & CurrentList, string & ClassID);
void ShowInfo(const StudentList & CurrentList, const string & ClassID, const string & StudentID);

void UpdateStudentFile(const StudentList & CurrentList, const string & ClassID);
void LoadStudents(StudentList & CurrentList, string & ClassID);
void CreateStudent(StudentList & CurrentList, const string & ClassID);

// void ExportStudents(const char * filepath, const StudentList & list);
void EditStudent(StudentList & CurrentList, const string & ClassID, const string & StudentID);
void DeleteStudent(StudentList & CurrentList, const string & ClassID, const string & StudentID);

void ListStudents(const StudentList & CurrentList, const string & ClassID);
