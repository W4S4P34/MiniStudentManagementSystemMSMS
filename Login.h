#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "_FILES_.h"
#include "sha1/sha1.h"
using namespace std;

// SHA-1: 80 bits
// Empty password: da39a3ee5e6b4b0d3255bfef95601890afd80709

// Access class
constexpr auto AC_ADMIN = 0;
constexpr auto AC_LECTURER = 1;
constexpr auto AC_STUDENT = 2;
constexpr auto AC_INVALID = -1;

struct Login_LinkedList {
	struct node {
		string ID, Password;
		node * next;
	};
	node * head = nullptr;

	void Add(string ID, string Password) {
		node * newnode = new node {ID, Password, nullptr};
		newnode->next = head;
		head = newnode;
	}

	void Remove(string ID) {
		node * current = head;
		node *previous = nullptr;
		while (current != nullptr) {
			if (current->ID == ID) {
				if (current == head) {
					head = head->next;
					delete current;
					break;
				}
				else if (current->next == nullptr) {
					previous->next=nullptr;
					delete current;
					break;
				}
				else {
					previous->next = current->next;
					delete current;
					break;
				}
			}
			else {
				previous=current;
				current=current->next;
			}
			}
	}
};

bool doLoginFilesExist();
void LoginMenu(string & ID, char & AccessClass);
string GetPassword();
char Authenticate(string & ID, const string & Password);
void ChangePassword(const string & ID, const char & AccessClass);

// Student
void CreateLogin(const string & StudentID, const string & ClassID);
void DeleteLogin(const string & StudentID, const string & ClassID);