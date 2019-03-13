#pragma once

#include <iostream>
#include <fstream>
#include <string>
// #include <filesystem>
#include "Student.h"
#include "Login.h"
using namespace std;

class Admin : protected Student {
	private:
		// subroutine tự động
		void CreateAccount(string ID, char AccessClass);

		// học kì admin đã chọn mở
		string Year, Term;

		// một list để chứa các lớp-môn có trong học kì hiện tại admin đang làm việc?

	public:
		string ChooseWorkingTerm();

		void ResetPassword(string ID, char AccessClass);

		void ImportStudents(const char * filepath);
		void CreateStudents();
		void EditStudent(string ID); // thêm/sửa/xóa các lớp-môn tham gia và thông tin SV?
		void RemoveStudent(string ID, string Class_Course);
		
		void ListClasses();
		void ListStudentsInClass(string ClassID);

		void ListYears();
		void CreateYear();
		// void EditYear(string Year); // edit gì ở đây?
		void DeleteYear(string Year);

		void ListTerms();
		void CreateTerms();
		// void EditTerms(string Year, string Term); // câu hỏi tương tự trên
		void DeleteTerm(string Year, string Term);

		void ListCourses();
		void ListStudentsInCourse();
		void ImportCourse(const char * filepath);
		void CreateCourse();
		void EditCourse(string CourseID);
		void RemoveCourse(string CourseID);

		void ListLecturers();
		void CreateLecturer();
		void EditLecturer(string LecturerID);
		void DeleteLecturer(string LecturerID);

		void ViewScores(string CourseID);
		void ExportScores(string CourseID);

		void ViewAttendance(string CourseID);
		void ExportAttendance(string CourseID);
};
