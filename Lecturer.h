#pragma once

#include "Course.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void ListLecturers(CourseList & list);
void CreateLecturer(CourseList & list);
void EditLecturer(CourseList & list, string LecturerID);
void DeleteLecturer(CourseList & list, string LecturerID);
