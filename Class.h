#pragma once

#include "Student.h"
#include <string>
using namespace std;

struct Class {
	string ID;
	StudentList Students;
};

struct ClassList {
	struct node {
		Class data;
		node * next;
	};
	node * head = nullptr;
};

void ListClasses(const ClassList & list);
void ListStudents(const ClassList & list, string ClassID);
