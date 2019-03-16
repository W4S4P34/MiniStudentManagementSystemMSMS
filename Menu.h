#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "Login.h"
#include "Class.h"
using namespace std;

void ShowHelp_General();
void ShowHelp_Student();
// void ShowHelp_Lecturer();
void ShowHelp_Admin();

void Menu_Student(const string & ID);
// void Menu_Lecturer(const string & ID);
void Menu_Admin(const string & ID);