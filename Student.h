#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Student {
	private:
		struct Birth {
			short d, m;
			int y;
		};
		bool isFemale;
		
	protected:
		string ID;
		string LastName, FirstName;
		// list các lớp-môn sinh viên có mặt, Class_Course

	public:
		void CheckIn();
		void ViewAttendance(string CourseID);
		void ViewSchedules();
		void ViewScores();
};
