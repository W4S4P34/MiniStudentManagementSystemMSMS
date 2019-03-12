#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "Login.h" // access classes and changing password
using namespace std;

void ShowMenu(const char & AccessClass); // to-do: include Student.h for info. Class?
void Interpret(const string & ID, const char & AccessClass);