#pragma once

#include <string>
using namespace std;

struct ScoreboardList {
	string ClassID;
	string CourseID;

	// per student
	struct Scoreboard {
		string StudentID;
		float MidTerm, Final, Lab, Bonus;
		Scoreboard * next;
	};

	Scoreboard * head = nullptr;
};

void ImportScoreboard(const char * filepath, ScoreboardList & list);
void ExportScoreboard(const char * filepath, const ScoreboardList & list);
void GetScoreboard(const string & ClassID, const string & CourseID, ScoreboardList & list);
void ViewScoreboard(ScoreboardList & list);
void ViewScoreboard(ScoreboardList & list, const string & studentID);
void EditScoreboard(ScoreboardList & list, const string & StudentID);
