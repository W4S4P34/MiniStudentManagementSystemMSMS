#pragma once

#include "Student.h"
#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::experimental::filesystem;

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
void ListClasses();
void ListStudents(const ClassList & list, string ClassID);
