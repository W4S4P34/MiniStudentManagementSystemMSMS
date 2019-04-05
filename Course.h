#pragma once
#include "_INCLUDES_.h"

struct Course {
	string Year;
	string Term;
	string ID;
	string ClassID; // Year/Term/CourseID_ClassID

	string Name;
	string LecturerID;
	tm Start, End; // _DoW
	string Room;
};

struct Timetable {
	struct node {
		string StudentID;
		string CoursePath;
		node * next;
	};
	node * head = nullptr;

	void Add(const string & StudentID, const string & CoursePath);
	void Remove(const string & CourseID, const string & ClassID);
	void LoadAll();
	void Load(const string & StudentID);
	void Update();
	~Timetable();
};

///////////////////////////////////////////////////////////////////////////////

void ListYears();
void CreateYear(const string & Year);
void EditYear(const string & Year_Old, const string & Year_New);
void DeleteYear(const string & Year);

void ListTerms(const string & Year);
void CreateTerm(const string & Year, const string & Term);
void EditTerm(const string & Year, const string & Term_Old, const string & Term_New);
void DeleteTerm(const string & Year, const string & Term);

void ListCourses(const string & Year, const string & Term);
void ImportCourse(const string & FileName, const string & Year, const string & Term);
void CreateCourse(Course & NewCourse);
void DeleteCourse(const string & Year, const string & Term, const string & CourseID, const string & ClassID);

//void EditCourse(CourseList & list);

//void ListStudents_Course(CourseList & list, string CourseID);
//void AddStudent_Course(CourseList & list, string StudentID);
//void RemoveStudent_Course(CourseList & list, string StudentID); // Unenroll();
