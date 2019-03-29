#pragma once
#include "_INCLUDES_.h"

// General/common functions
void Capitalize(string & string);
void ShowHelp_General();

// Student
void ShowHelp_Student();
void Menu_Student(const string & ID);

// Lecturer
void ShowHelp_Lecturer();
void Menu_Lecturer(const string & ID);

// Admin
void ShowHelp_Admin();
void Menu_Admin(const string & ID);
