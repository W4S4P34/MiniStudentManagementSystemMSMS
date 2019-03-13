#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Student.h"
using namespace std;

class Lecturer : protected Student {
	protected:
		string ID;
		string LastName, FirstName;
		// list các môn giảng viên đang dạy, Class_Course

	public:
		// ID ở đây = student ID
		void ListCourses();
		void ListStudentsInCourse(string Class_Course);
		void ViewAttendance(string Class_Course);
		void EditAttendance(string Class_Course, string ID);
		void ViewScores(string Class_Course);
		void ImportScores(const char * filepath);
		void EditScores(string Class_Course, string ID);
};
