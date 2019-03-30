#pragma once
#include "_INCLUDES_.h"

struct Birth
{
	short d, m;
	int y;
};

struct StudentList
{
	struct Student {
		string ID;
		string LastName, FirstName;
		string Gender;
		Birth DOB;
		Student * next;
	};
	Student * head = nullptr;

	void Add(const string & ID, const string & LastName, const string & FirstName, const string & Gender, const Birth & DOB);
	void Delete(const string & ID);
	~StudentList();
};

///////////////////////////////////////////////////////////////////////////////

void ImportClass(const string & FilePath, const string & ClassID);
void ListClass();
void UpdateClass(const StudentList & CurrentList, const string & ClassID);
void LoadClass(StudentList & CurrentList, const string & ClassID);

void ListStudents(const StudentList & CurrentList, const string & ClassID);
void LookupStudent(const StudentList & CurrentList, const string & ClassID, const string & StudentID);
void CreateStudent(StudentList & CurrentList, const string & ClassID, const StudentList::Student & Student_New);
void EditStudent(StudentList & CurrentList, const string & ClassID, const string & StudentID);
void DeleteStudent(StudentList & CurrentList, const string & ClassID, const string & StudentID);
void MoveStudent(StudentList & CurrentList, const string & ClassID_Old, const string & ClassID_New, const string & StudentID);
