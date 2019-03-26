#pragma once

#include <string>
using namespace std;

class AttendanceList {
	string ClassID;
	string CourseID;
	
	// per student
	struct Attendance {
		string StudentID;
		string Marks; // list of check-ins
		Attendance * next;
	};

	Attendance * head = nullptr;
};

// student
void CheckIn(AttendanceList & list, const string & StudentID);

// internal
void LoadAttendance(AttendanceList & list, const string & CoursePath);
void UpdateAttendance(const AttendanceList & list, const string & CoursePath);

// public
void ImportAttendance(const string & filepath, const string & CoursePath);
void ExportAttendance(const string & filepath, const string & CoursePath);
void ViewAttendance(const AttendanceList & list);
void ViewAttendance(const AttendanceList & list, const string & StudentID);
void EditAttendance(AttendanceList & list, const string & StudentID);
