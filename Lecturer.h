#pragma once
#include "_INCLUDES_.h"

struct Lecturer {
	string ID;
	string LastName, FirstName;
	string Gender;
};

struct LecturerList {
	struct node {
		Lecturer data;
		node * next;
	};
	node * head = nullptr;
	
	void AddLecturer(Lecturer New);
	~LecturerList();
};

void LowerString(string & string);
string GenerateID(const string & LecturerLastName, const string & LecturerFirstName);

void ImportLecturer(const string & FilePath, LecturerList & CurrentLecturerList);
void ShowInfo(const LecturerList & CurrentList, const string & LecturerID);

void UpdateLecturerFile(const LecturerList & CurrentList);
void LoadLecturer(LecturerList & CurrentList);
void CreateLecturer(LecturerList & CurrentList, const Lecturer & Lecturer_New);

void EditLecturer(LecturerList & CurrentList, const string & LecturerID);
void DeleteLecturer(LecturerList & CurrentList, const string & LecturerID);

void ListLecturers(const LecturerList & CurrentList);