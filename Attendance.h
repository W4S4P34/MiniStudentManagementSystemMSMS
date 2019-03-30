#pragma once
#include "_INCLUDES_.h"

struct AttendanceList
{
	struct Attendance {
		string ID;
		string CheckIns;
		Attendance * next;
	};
	Attendance * head = nullptr;

	void Add(const string & ID, const string & CheckIns);
	void Delete(const string & ID);
	~AttendanceList();
};

///////////////////////////////////////////////////////////////////////////////

void CheckIn(AttendanceList & List, const string & StudentID);

void LoadAttendance(AttendanceList & List, const string & CoursePath);
void UpdateAttendance(const AttendanceList & List, const string & CoursePath);

void ImportAttendance(const string & FileName, const string & CoursePath);
void ExportAttendance(const string & FileName, const AttendanceList & List, const string & CoursePath);
void ViewAttendance(const AttendanceList & List);
void ViewAttendance(const AttendanceList & List, const string & StudentID);
void EditAttendance(AttendanceList & List, const string & CoursePath, const string & StudentID, const size_t & Week, const bool & State);
