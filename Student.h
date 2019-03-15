#pragma once

#include "_FILES_.h"
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

	void AddStudent(Student New) {
		node * newnode = new node {New, nullptr};
		newnode->next = head;
		head = newnode;
	}
};

void ImportStudents(const string & filepath, StudentList & CurrentList);
void ShowInfo(const string & ID, const StudentList & list);

void UpdateStudentFile(const string & ClassID, const StudentList & list);
void LoadStudents(const string & ClassID, StudentList & CurrentList);

// void ExportStudents(const char * filepath, const StudentList & list);
// void CreateStudent(StudentList & list);
// void EditStudent(StudentList & list, const string & ID);
//void DeleteStudent(StudentList & list, const string & ID);
