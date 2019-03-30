#pragma once
#include "_INCLUDES_.h"

struct LecturerList {
	struct Lecturer {
		string ID;
		string LastName, FirstName;
		string Gender;
		Lecturer * next;
	};
	Lecturer * head = nullptr;

	void Add(const string & ID, const string & LastName, const string & FirstName, const string & Gender);
	void Delete(const string & ID);
	~LecturerList();
};

///////////////////////////////////////////////////////////////////////////////

void LowerString(string & string);
string GenerateID(const string & LastName, const string & FirstName);

///////////////////////////////////////////////////////////////////////////////

void ImportLecturer(const string & FilePath, LecturerList & List);
void UpdateLecturerFile(const LecturerList & List);

void ListLecturer(const LecturerList & List);
void LookupLecturer(const LecturerList & List, const string & LecturerID);
void LoadLecturer(LecturerList & List);
void CreateLecturer(LecturerList & List, const string & LastName, const string & FirstName, const string & Gender);
void EditLecturer(LecturerList & List, const string & LecturerID);
void DeleteLecturer(LecturerList & List, const string & LecturerID);
