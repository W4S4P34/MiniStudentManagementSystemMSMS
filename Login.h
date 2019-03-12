#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "sha1/sha1.h"
using namespace std;

// SHA-1: 80 bits
// Empty password: da39a3ee5e6b4b0d3255bfef95601890afd80709

// File list
constexpr auto LOGIN_LIST_ADMIN = "D:/data/Login/Admin.txt";
constexpr auto LOGIN_LIST_LECTURER = "D:/data/Login/Lecturer.txt";
constexpr auto LOGIN_LIST_STUDENT = "D:/data/Login/Student.txt";

// Access class
constexpr auto AC_ADMIN = 0;
constexpr auto AC_LECTURER = 1;
constexpr auto AC_STUDENT = 2;
constexpr auto AC_INVALID = -1;

void LoginMenu(string & ID, char & AccessClass); // also returns access class
string GetPassword(); // masked password field
char Authenticate(const string & ID, const string & Password);
void ChangePassword(const string & ID, const char & AccessClass);