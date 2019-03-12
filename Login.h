#pragma once

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define LOGIN_STUDENT "D:/Login.Student.csv"
#define LOGIN_LECTURER "D:/Login.Lecturer.csv"
#define LOGIN_ADMIN "D:/Login.Admin.csv"

char LoginMenu();
char Authenticate(string username, string password);