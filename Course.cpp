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
		FileName = FileName.substr(0, FileName.find_last_of('.'));
		cout << FileName << endl;
	}
}
