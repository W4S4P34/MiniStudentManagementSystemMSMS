#pragma once

#include "_FILES_.h"
#include <iostream>
#include <iomanip> // setprecision
#include <fstream>
#include <string>
using namespace std;

struct Scoreboard {
	struct node {
		string ID;
		float Midterm, Final, Lab, Bonus;
		node * next;
	};
	node * head = nullptr;

	void Add(string ID, float Midterm, float Final, float Lab, float Bonus);
	void Delete(string ID);
	~Scoreboard();
};

// internal
void LoadScoreboard(Scoreboard & list, const string & CoursePath);
void UpdateScoreboard(const Scoreboard & list, const string & CoursePath);

// public
void ImportScoreboard(const string & filepath, const string & CoursePath);
void ExportScoreboard(const string & filepath, const string & CoursePath);
//void ViewScoreboard(const string & CoursePath);
void ViewScoreboard(const Scoreboard & list);
//void ViewScoreboard(const string & CoursePath, const string & StudentID);
void ViewScoreboard(const Scoreboard & list, const string & StudentID);
//void EditScoreboard(const string & CoursePath, const string & StudentID, const float & Midterm, const float & Final, const float & Lab, const float & Bonus);
void EditScoreboard(const Scoreboard & list, const string & CoursePath, const string & StudentID, const float & Midterm, const float & Final, const float & Lab, const float & Bonus);
