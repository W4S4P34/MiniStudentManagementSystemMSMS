#pragma once

#include "Class.h"
#include <string>
using namespace std;

struct DateTime {
	short d, m;
	int y;
	string dow; // day of week
	short hh, mm;
};

struct Course {
	string ID;
	string Name;
	Class _Class; // change the name
	string LecturerID;
	DateTime Start, End;

	// machine-readable dates
	// TO-DO: UNIX timestamps
};

struct CourseList {
	Course * head = nullptr;
};

// #include <filesystem>
void ListYears();
void CreateYear();
void EditYear(); //?
void DeleteYear();

void ListTerms();
void CreateTerm();
void EditTerm(); //?
void DeleteTerm();

void ImportCourse(const char * filepath, CourseList & list);
void ListCourses();
void CreateCourse(CourseList & list);
void EditCourse(CourseList & list);
void DeleteCourse(CourseList & list);

void ListStudents_Course(CourseList & list, string CourseID);
void AddStudent_Course(CourseList & list, string StudentID);
void RemoveStudent_Course(CourseList & list, string StudentID); // Unenroll();

// da hell
void ViewSchedule(const CourseList & list, string StudentID);
