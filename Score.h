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
void ViewScoreboard(const string & CoursePath);
void LookupScoreboard(const string & CoursePath, const string & StudentID);
void EditScoreboard(const string & CoursePath, const string & StudentID, const float & Midterm, const float & Final, const float & Lab, const float & Bonus);

//void ImportScoreboard(const char * filepath, ScoreboardList & list);
//void ExportScoreboard(const char * filepath, const ScoreboardList & list);
//void GetScoreboard(const string & ClassID, const string & CourseID, ScoreboardList & list);
//void ViewScoreboard(ScoreboardList & list);
//void EditScoreboard(ScoreboardList & list, const string & StudentID);