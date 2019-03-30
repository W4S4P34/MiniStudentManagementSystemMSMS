#pragma once
#include "_INCLUDES_.h"

struct ScoreList
{
	struct Score {
		string ID;
		float Midterm, Final, Lab, Bonus;
		Score * next;
	};
	Score * head = nullptr;

	void Add(const string & ID, const float & Midterm, const float & Final, const float & Lab, const float & Bonus);
	void Delete(const string & ID);
	~ScoreList();
};

///////////////////////////////////////////////////////////////////////////////

void LoadScore(ScoreList & List, const string & CoursePath);
void UpdateScore(const ScoreList & List, const string & CoursePath);

void ImportScore(const string & FileName, const string & CoursePath);
void ExportScore(const string & FileName, const ScoreList & List, const string & CoursePath);
void ViewScore(const ScoreList & List);
void ViewScore(const ScoreList & List, const string & StudentID);
void EditScore(ScoreList & List, const string & CoursePath, const string & StudentID, const float & Midterm, const float & Final, const float & Lab, const float & Bonus);
