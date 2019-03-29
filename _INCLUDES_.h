#pragma once

// C/Windows-specific
#include <conio.h>
#include <ctime>

// C++
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::experimental::filesystem;

// Externals
#include "sha1/sha1.h"

// MSMS
#include "_FILES_.h"
#include "Login.h"
#include "Menu.h"
#include "Student.h"
#include "Lecturer.h"
#include "Course.h"
#include "Attendance.h"
#include "Score.h"
