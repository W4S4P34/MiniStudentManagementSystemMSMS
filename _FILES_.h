#pragma once

#include <string>
using namespace std;

// Logins
//constexpr auto LOGIN_LIST_ADMIN = "/Users/User/GitHub/MSMS/data/Login/Admin.txt";
//constexpr auto LOGIN_LIST_LECTURER = "/Users/User/GitHub/MSMS/data/Login/Lecturer.txt";
//constexpr auto LOGIN_LIST_STUDENT = "/Users/User/GitHub/MSMS/data/Login/Student.txt";

// Base path
	//Base path of Alec: E:/Github/StudentManagerProgram-SMP--G1/data
constexpr auto BASE_PATH = "/Users/User/GitHub/MSMS/data/";

// Login files
constexpr auto LOGIN_LIST_ADMIN = "Login/Admin.txt";
constexpr auto LOGIN_LIST_LECTURER = "Login/Lecturer.txt";
constexpr auto LOGIN_LIST_STUDENT = "Login/Student.txt";

// get the abs path
// inline to avoid LNK2005
inline string GetPath(string path) {
	return BASE_PATH + path;
}