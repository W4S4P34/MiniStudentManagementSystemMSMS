#include "Score.h"

void Scoreboard::Add(string ID, float Midterm, float Final, float Lab, float Bonus) {
	node * newnode = new node {ID, Midterm, Final, Lab, Bonus, nullptr};
	if (head == nullptr)
		head = newnode;
	else {
		node * append = head;
		while (append->next != nullptr)
			append = append->next;
		append->next = newnode;
	}
}

void Scoreboard::Delete(string ID) {
	if (head == nullptr)
		return;

	node * current = head;
	node * previous = nullptr;

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

Scoreboard::~Scoreboard() {
	while (head != nullptr) {
		node * deleteme = head;
		head = head->next;
		delete deleteme;
	}
}

// internal
void LoadScoreboard(Scoreboard & list, const string & CoursePath) {
	ifstream file;
	file.open(GetPath("Courses/" + CoursePath + "_" + "Score.txt"));

	if (!file.is_open()) {
		cout << "ERROR: Unable to open scoreboard.\n"
			<< "Check if provided year, term, course ID, and/or class ID exists.\n";
		return;
	}

	string ID, Midterm, Final, Lab, Bonus;
	string test;
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

		list.Add(ID, stof(Midterm), stof(Final), stof(Lab), stof(Bonus));
	}

	file.close();
}

// internal
void UpdateScoreboard(const Scoreboard & list, const string & CoursePath) {
	ofstream file;
	file.open(GetPath("Courses/" + CoursePath + "_" + "Score.txt"));

	if (!file.is_open()) {
		cout << "ERROR: Unable to open scoreboard.\n"
			<< "Check if provided year, term, course ID, and/or class ID exists.\n";
		return;
	}

	Scoreboard::node * current = list.head;
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

// thêm họ tên SV thay vì chỉ ID?
void ViewScoreboard(const Scoreboard & list) {
	cout << "Sequential order in each entry: Midterm, Final, Lab, Bonus.\n";
	Scoreboard::node * current = list.head;
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

void ViewScoreboard(const Scoreboard & list, const string & StudentID) {
	Scoreboard::node * target = list.head;
	while (target != nullptr && target->ID != StudentID)
		target = target->next;
	if (target == nullptr) {
		cout << "Student " << StudentID << " not found.\n";
		return;
	}

	cout << "Scoreboard for ID " << StudentID << ":\n"
		<< setprecision(3) << "Midterm = " << target->Midterm << "\n"
		<< setprecision(3) << "Final = " << target->Final << "\n"
		<< setprecision(3) << "Lab = " << target->Lab << "\n"
		<< setprecision(3) << "Bonus = " << target->Bonus;

	cout << "\n";
}

void EditScoreboard(const Scoreboard & list, const string & CoursePath, const string & StudentID, const float & Midterm, const float & Final, const float & Lab, const float & Bonus) {
	bool found = false;
	Scoreboard::node * current = list.head;
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
		cout << "Student " << StudentID << " not found.\n";
		return;
	}

	UpdateScoreboard(list, CoursePath);
	cout << "Successfully edited scores for " << StudentID << ".\n";
}

void ImportScoreboard(const string & filepath, const string & CoursePath) {
	ifstream importfile;
	ofstream exportfile;
	importfile.open(GetPath("../Import/Scoreboards/" + filepath + ".csv"));
	exportfile.open(GetPath("Courses/" + CoursePath + "_" + "Score.txt"));

	if (!importfile.is_open()) {
		cout << "Unable to open file. Check your filename.\n";
		return;
	}

	string skip, copy;
	getline(importfile, skip);
	while (!importfile.eof()) {
		getline(importfile, copy);
		exportfile << copy << endl;
	}
	importfile.close();
	exportfile.close();
}


void ExportScoreboard(const string & filepath, const string & CoursePath) {
	ofstream file;
	file.open(GetPath("Courses/" + CoursePath + "_" + "Score.txt"));
	
}