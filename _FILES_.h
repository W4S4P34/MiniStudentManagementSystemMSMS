#pragma once

#include <string>
using namespace std;

// Thai's Base path
constexpr auto BASE_PATH = "/Users/HP/GitHub Source/MSMS--G1/data/";

// Base path
//constexpr auto BASE_PATH = "/Users/User/GitHub/MSMS/data/";

// Login files
constexpr auto LOGIN_LIST_ADMIN = "Login/Admin.txt";
constexpr auto LOGIN_LIST_LECTURER = "Login/Lecturer.txt";
constexpr auto LOGIN_LIST_STUDENT = "Login/Student.txt";

// get the abs path
// inline to avoid LNK2005
inline string GetPath(string path) {
	return BASE_PATH + path;
}