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

void CheckIn(AttendanceList & list, const string & StudentID);

void ImportAttendance(const char * filepath, AttendanceList & list);
void ExportAttendance(const char * filepath, const AttendanceList & list);
void GetAttendance(const string & ClassID, const string & CourseID, AttendanceList & list);
void ViewAttendance(const AttendanceList & list);
void ViewAttendance(const AttendanceList & list, const string & StudentID);
void EditAttendance(AttendanceList & list, const string & StudentID);
