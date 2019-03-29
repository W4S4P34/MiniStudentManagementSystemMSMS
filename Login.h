#pragma once
#include "_INCLUDES_.h"

// SHA-1: 80 bits
// Empty password (default): da39a3ee5e6b4b0d3255bfef95601890afd80709
// Use constexpr auto instead of using #define

constexpr auto AC_ADMIN = 0;
constexpr auto AC_LECTURER = 1;
constexpr auto AC_STUDENT = 2;
constexpr auto AC_INVALID = -1;

struct LoginList {
	struct node {
		string ID, Password;
		node * next;
	};
	node * head = nullptr;

	void Add(string ID, string Password);
	void Remove(string ID);
};

// Functions interact with identification
bool LoginFilesExist();
void LoginMenu(string & ID, char & AccessClass);
string GetPassword();
char Authenticate(string & ID, const string & Password);
void ChangePassword(const string & ID, const char & AccessClass, const string & Password_New);

// Student
void CreateLogin(const string & StudentID, const string & ClassID);
void DeleteLogin(const string & StudentID, const string & ClassID);

// Lecturer
void CreateLogin(const string & LecturerID);
void DeleteLogin(const string & LecturerID);