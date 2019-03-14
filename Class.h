#pragma once

#include "Student.h"
#include <string>
using namespace std;

struct Class {
	string ID;
	StudentList Students;
	Class * next;
};

struct ClassList {
	struct ClassNode {
		Class data;
		ClassNode * next;
	};
	ClassNode * head = nullptr;
};

void ListClasses(const ClassList & list);
void ListStudents(const ClassList & list, string ClassID);
