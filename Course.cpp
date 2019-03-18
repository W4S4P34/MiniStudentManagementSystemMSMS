#include "Course.h"

void ListYears() {
	fs::path p = GetPath("Courses");
	if (fs::is_empty(p)) {
		cout << "No years available.\n";
		return;
	}
	for (auto& p : fs::directory_iterator(GetPath("Courses"))) {
		string FileName = p.path().string();
		FileName = FileName.substr(FileName.find_last_of('\\') + 1);
		cout << FileName << endl;
	}
}

void CreateYear(const string & Year) {
	fs::path p = GetPath("Courses/" + Year);
	if (fs::exists(p)) {
		cout << "Year " << Year << " already exists.\n";
		return;
	}
	fs::create_directory(p);
	cout << "Successfully created year " << Year << ".\n";
}

void EditYear(const string & Year_Old, const string & Year_New) {
	fs::path p_old = GetPath("Courses/" + Year_Old);
	fs::path p_new = GetPath("Courses/" + Year_New);
	if (!fs::exists(p_old)) {
		cout << "Year " << Year_Old << " does not exist.\n";
		return;
	}
	fs::rename(p_old, p_new);
	cout << "Successfully changed year " << Year_Old << " into year " << Year_New << ".\n";
}

void DeleteYear(const string & Year) {
	fs::path p = GetPath("Courses/" + Year);
	if (!fs::exists(p)) {
		cout << "Year " << Year << " does not exist.\n";
		return;
	}
	fs::remove_all(p);
	cout << "Successfully deleted year " << Year << ".\n";
}

void ListTerms(const string & Year) {
	fs::path p = GetPath("Courses/" + Year);
	if (!fs::exists(p)) {
		cout << "Year " << Year << " does not exist.\n";
		return;
	}
	if (fs::is_empty(p)) {
		cout << "No terms available.\n";
		return;
	}
	for (auto& p : fs::directory_iterator(GetPath("Courses/" + Year))) {
		string FileName = p.path().string();
		FileName = FileName.substr(FileName.find_last_of('\\') + 1);
		cout << FileName << endl;
	}
}

void CreateTerm(const string & Year, const string & Term) {
	fs::path p;
	p = GetPath("Courses/" + Year);
	if (!fs::exists(p)) {
		cout << "Year " << Year << " does not exist.\n";
		return;
	}
	p = GetPath("Courses/" + Year + "/" + Term);
	if (fs::exists(p)) {
		cout << "Term " << Term << " already exists.\n";
		return;
	}
	fs::create_directory(p);
	cout << "Successfully created term " << Term << ".\n";
}

void EditTerm(const string & Year, const string & Term_Old, const string & Term_New) {
	fs::path p_old = GetPath("Courses/" + Year + "/" + Term_Old);
	fs::path p_new = GetPath("Courses/" + Year + "/" + Term_New);
	if (!fs::exists(p_old)) {
		cout << "Year " << Year << " and/or term " << Term_Old << " does not exist.\n";
		return;
	}
	fs::rename(p_old, p_new);
	cout << "Succesfully renamed " << Term_Old << " into " << Term_New << ".\n";
}

void DeleteTerm(const string & Year, const string & Term) {
	fs::path p = GetPath("Courses/" + Year + "/" + Term);
	if (!fs::exists(p)) {
		cout << "Year " << Year << " and/or term " << Term << " does not exist.\n";
		return;
	}
	fs::remove_all(p);
	cout << "Successfully deleted year " << Term << ".\n";
}

void ListCourses(const string & Year, const string & Term) {
	fs::path p = GetPath("Courses/" + Year + "/" + Term);
	if (!fs::exists(p)) {
		cout << "Either year " << Year << " or term " << Term << " does not exist.\n";
		return;
	}
	if (fs::is_empty(p)) {
		cout << "No courses available.\n";
		return;
	}
	for (auto& p : fs::directory_iterator(GetPath("Courses/" + Year + "/" + Term))) {
		string FileName = p.path().string();
		FileName = FileName.substr(FileName.find_last_of('\\') + 1);
		// FileName = FileName.substr(0, FileName.find_last_of('.'));
		if (FileName.find_last_of('.') == FileName.npos)
			cout << FileName << endl;
	}
}

void CreateCourse(const string & Year, const string & Term, Course & Course_New) {
	fs::path p;

	p = GetPath("Courses/" + Year + "/" + Term);
	if (!fs::exists(p)) {
		cout << "Year " << Year << " and/or term " << Term << " does not exist.\n";
		return;
	}

	const char wday_name[][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	
	p = GetPath("Courses/" + Year + "/" + Term + "/" + Course_New.ID + "_" + Course_New.ClassID + "_" + wday_name[Course_New.Start.tm_wday]);
	fs::create_directory(p);

	ofstream InfoFile;
	InfoFile.open(GetPath("Courses/" + Year + "/" + Term + "/" + Course_New.ID + "_" + Course_New.ClassID + "_" + wday_name[Course_New.Start.tm_wday] + "/Info.txt"));
	InfoFile << Course_New.Name << endl;
	InfoFile << Course_New.Room << endl;
	InfoFile << Course_New.Start.tm_year + 1900
			<< "-" << Course_New.Start.tm_mon + 1
			<< "-" << Course_New.Start.tm_mday
			<< " " << Course_New.Start.tm_hour
			<< ":" << Course_New.Start.tm_min
			<< " " << wday_name[Course_New.Start.tm_wday] << endl;
	InfoFile << Course_New.End.tm_year + 1900
			<< "-" << Course_New.End.tm_mon + 1
			<< "-" << Course_New.End.tm_mday
			<< " " << Course_New.End.tm_hour
			<< ":" << Course_New.End.tm_min
			<< " " << wday_name[Course_New.End.tm_wday] << endl;
	InfoFile.close();

	StudentList temp;
	LoadStudents(temp, Course_New.ClassID);
	StudentList::node * current;

	ofstream AttendanceFile;
	AttendanceFile.open(GetPath("Courses/" + Year + "/" + Term + "/" + Course_New.ID + "_" + Course_New.ClassID + "_" + wday_name[Course_New.Start.tm_wday] + "/Attendance.txt"));
	current = temp.head;
	time_t Start = mktime(&Course_New.Start);
	time_t End = mktime(&Course_New.End);
	size_t DC = ceil((End-Start)/(60*60*24*7));
	while (current != nullptr) {
		AttendanceFile << current->data.ID << ",";
		for (size_t i = 0; i < DC; i++)
			AttendanceFile << "-";
		AttendanceFile << endl;
		current = current->next;
	}
	AttendanceFile.close();

	ofstream ScoreboardFile;
	ScoreboardFile.open(GetPath("Courses/" + Year + "/" + Term + "/" + Course_New.ID + "_" + Course_New.ClassID + "_Score.txt"));
	current = temp.head;
	while (current != nullptr) {
		ScoreboardFile << current->data.ID << ",0,0,0,0" << endl;
		current = current->next;
	}
	ScoreboardFile.close();

	temp.~StudentList();
	cout << "Successfully created course " << Course_New.ID << ".\n";
}

void ImportCourse(const string & FileName, const string & Year, const string & Term) {
	fs::path p;
	p = GetPath("../Import/Courses/" + FileName);
	if (!fs::exists(p)) {
		cout << "File does not exist.";
		return;
	}

	p = GetPath("Courses/" + Year + "/" + Term);
	if (!fs::exists(p)) {
		cout << "Year " << Year << " and/or term " << Term << " does not exist.\n";
		return;
	}

	ifstream file;
	file.open(GetPath("../Import/Courses/" + FileName));

	string skip;
	getline(file, skip);
	while (!file.eof()) {
		Course Course_New;
		string StartY, StartM, StartD, StartHH, StartMM;
		string EndY, EndM, EndD, EndHH, EndMM;
		string DoW;
		getline(file, skip, ',');
		getline(file, Course_New.ID, ',');
		getline(file, Course_New.Name, ',');
		getline(file, Course_New.ClassID, ',');
		getline(file, skip, ','); // LecturerID
		getline(file, StartY, '-');
		getline(file, StartM, '-');
		getline(file, StartD, ',');
		getline(file, EndY, '-');
		getline(file, EndM, '-');
		getline(file, EndD, ',');
		getline(file, DoW, ',');
		getline(file, StartHH, ':');
		getline(file, StartMM, ',');
		getline(file, EndHH, ':');
		getline(file, EndMM, ',');
		getline(file, Course_New.Room);

		Course_New.Start.tm_year = stoi(StartY); Course_New.Start.tm_year -= 1900;
		Course_New.Start.tm_mon = stoi(StartM); Course_New.Start.tm_mon -= 1;
		Course_New.Start.tm_mday = stoi(StartD);
		Course_New.Start.tm_hour = stoi(StartHH);
		Course_New.Start.tm_min = stoi(StartMM);
		if (DoW == "Sun") Course_New.Start.tm_wday = 0;
		else if (DoW == "Mon") Course_New.Start.tm_wday = 1;
		else if (DoW == "Tue") Course_New.Start.tm_wday = 2;
		else if (DoW == "Wed") Course_New.Start.tm_wday = 3;
		else if (DoW == "Thu") Course_New.Start.tm_wday = 4;
		else if (DoW == "Fri") Course_New.Start.tm_wday = 5;
		else if (DoW == "Sat") Course_New.Start.tm_wday = 6;

		Course_New.End.tm_year = stoi(EndY); Course_New.End.tm_year -= 1900;
		Course_New.End.tm_mon = stoi(EndM); Course_New.End.tm_mon -= 1;
		Course_New.End.tm_mday = stoi(EndD);
		Course_New.End.tm_hour = stoi(EndHH);
		Course_New.End.tm_min = stoi(EndMM);
		if (DoW == "Sun") Course_New.End.tm_wday = 0;
		else if (DoW == "Mon") Course_New.End.tm_wday = 1;
		else if (DoW == "Tue") Course_New.End.tm_wday = 2;
		else if (DoW == "Wed") Course_New.End.tm_wday = 3;
		else if (DoW == "Thu") Course_New.End.tm_wday = 4;
		else if (DoW == "Fri") Course_New.End.tm_wday = 5;
		else if (DoW == "Sat") Course_New.End.tm_wday = 6;

		CreateCourse(Year, Term, Course_New);
	}

	file.close();
	cout << "Successfully imported courses.\n";
}

void DeleteCourse(const string & Year, const string & Term, const string & CourseID, const string & ClassID) {
	bool found = false;
	for (auto& p : fs::directory_iterator(GetPath("Courses/" + Year + "/" + Term))) {
		string FileName = p.path().string();
		FileName = FileName.substr(FileName.find_last_of('\\') + 1);
		// 0-13
		if (FileName.substr(0, 13) == CourseID + "_" + ClassID) {
			found = true;
			fs::path deleteme = GetPath("Courses/" + Year + "/" + Term + "/" + FileName);
			fs::remove_all(deleteme);
		}
	}
	if (found) {
		cout << "Successfully deleted course.\n";
	}
	else {
		cout << "Course not found.\n";
	}
}
