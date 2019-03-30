#include "Score.h"

void ScoreList::Add(const string & ID, const float & Midterm, const float & Final, const float & Lab, const float & Bonus)
{
	Score * newnode = new Score{ ID, Midterm, Final, Lab, Bonus, nullptr };
	if (head == nullptr) {
		head = newnode;
	}
	else {
		Score * append = head;
		while (append->next != nullptr) append = append->next;
		append->next = newnode;
	}
}

void ScoreList::Delete(const string & ID)
{
	ScoreList::Score * current = head;
	ScoreList::Score * previous = nullptr;

	while (current != nullptr) {
		if (current->ID == ID) {
			if (current == head) {
				head = head->next;
				delete current;
				break;
			}
			else if (current->next == nullptr) {
				previous->next = nullptr;
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
			previous = current;
			current = current->next;
		}
	}
}

ScoreList::~ScoreList()
{
	while (head != nullptr) {
		Score * current = head;
		head = current->next;
		delete current;
	}
}

///////////////////////////////////////////////////////////////////////////////

void LoadScore(ScoreList & List, const string & CoursePath) {
	ifstream file;
	file.open(GetPath("Courses/" + CoursePath + "_" + "Score.txt"));
	if (!file.is_open()) {
		cout << "ERROR: Unable to open scoreboard.";
		return;
	}

	string test;
	string ID, Midterm, Final, Lab, Bonus;
	streamoff BeginOfLine;
	while (!file.eof()) {
		BeginOfLine = file.tellg();
		getline(file, test);
		if (test.empty() || test == "\n")
			break;
		file.seekg(BeginOfLine);

		getline(file, ID, ',');
		getline(file, Midterm, ',');
		getline(file, Final, ',');
		getline(file, Lab, ',');
		getline(file, Bonus, '\n');

		List.Add(ID, stof(Midterm), stof(Final), stof(Lab), stof(Bonus));
	}

	file.close();
}

void UpdateScore(const ScoreList & List, const string & CoursePath) {
	ofstream file;
	file.open(GetPath("Courses/" + CoursePath + "_" + "Score.txt"));
	if (!file.is_open()) {
		cout << "ERROR: Unable to open scoreboard.";
		return;
	}

	ScoreList::Score * current = List.head;
	while (current != nullptr) {
		file << current->ID << ","
			<< current->Midterm << ","
			<< current->Final << ","
			<< current->Lab << ","
			<< current->Bonus
			<< "\n";
		current = current->next;
	}
	file.close();
}

void ImportScore(const string & FileName, const string & CoursePath) {
	ifstream file_in;
	file_in.open(GetPath("../Import/Scores/" + FileName + ".csv"));
	ofstream file_out;
	file_out.open(GetPath("Courses/" + CoursePath + "_" + "Score.txt"));
	if (!file_in.is_open() || !file_out.is_open()) {
		cout << "ERROR: Unable to open import scoreboard.";
		return;
	}

	string skip, copy;
	getline(file_in, skip);
	while (!file_in.eof()) {
		getline(file_in, copy);
		file_out << copy << endl;
	}
	file_in.close();
	file_out.close();
}

void ExportScore(const string & FileName, const ScoreList & List, const string & CoursePath) {
	ofstream file;
	file.open(GetPath("../Export/Score/" + FileName + ".csv"));
	if (!file.is_open()) {
		cout << "ERROR: Unable to export scoreboard.";
		return;
	}

	file << "ID,Midterm,Final,Lab,Bonus" << endl;

	ScoreList::Score * current = List.head;
	while (current != nullptr) {
		file << current->ID << ","
			<< setprecision(3) << current->Midterm << ","
			<< setprecision(3) << current->Final << ","
			<< setprecision(3) << current->Lab << ","
			<< setprecision(3) << current->Bonus
			<< endl;
		current = current->next;
	}
	file.close();
}

void ViewScore(const ScoreList & List) {
	cout << "Sequential order in each entry: Midterm, Final, Lab, Bonus.\n";
	ScoreList::Score * current = List.head;
	while (current != nullptr) {
		cout << current->ID << " : "
			<< setprecision(3) << current->Midterm << "; "
			<< setprecision(3) << current->Final << "; "
			<< setprecision(3) << current->Lab << "; "
			<< setprecision(3) << current->Bonus
			<< "\n";
		current = current->next;
	}
}

void ViewScore(const ScoreList & List, const string & StudentID) {
	ScoreList::Score * current = List.head;
	while (current != nullptr && current->ID != StudentID)
		current = current->next;
	if (current == nullptr) {
		cout << "Student " << StudentID << " not found.\n";
		return;
	}

	cout << "Score for ID " << StudentID << ":\n"
		<< setprecision(3) << "Midterm = " << current->Midterm << "\n"
		<< setprecision(3) << "Final = " << current->Final << "\n"
		<< setprecision(3) << "Lab = " << current->Lab << "\n"
		<< setprecision(3) << "Bonus = " << current->Bonus << "\n";
}

void EditScore(const ScoreList & List, const string & CoursePath, const string & StudentID, const float & Midterm, const float & Final, const float & Lab, const float & Bonus) {
	bool found = false;
	ScoreList::Score * current = List.head;
	while (current != nullptr) {
		if (current->ID == StudentID) {
			current->Midterm = Midterm;
			current->Final = Final;
			current->Lab = Lab;
			current->Bonus = Bonus;
			found = true;
			break;
		}
		current = current->next;
	}

	if (!found) {
		cout << "Student " << StudentID << " not found.";
		return;
	}

	UpdateScore(List, CoursePath);
	cout << "Successfully edited scores for " << StudentID << ".";
}
