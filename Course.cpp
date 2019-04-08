#include "Course.h"

void Timetable::Add(const string & StudentID, const string & CoursePath) {
	Timetable::node * newnode = new node{ StudentID, CoursePath, nullptr };
	if (head == nullptr) {
		head = newnode;
	}
	else {
		Timetable::node * append = head;
		while (append->next != nullptr) append = append->next;
		append->next = newnode;
	}
}

void Timetable::Remove(const string & CourseID, const string & ClassID)
{
	node * previous = nullptr;
	node * current = head;
	while (current != nullptr) {
		if (current->CoursePath.find(CourseID + "_" + ClassID) != current->CoursePath.npos) break;
		previous = current;
		current = current->next;
	}

	if (current == head) {
		head = head->next;
	}
	else {
		previous->next = current->next;
	}
	delete current;
}

void Timetable::Load(const string & StudentID)
{
	fstream TimetableFile;
	TimetableFile.open(GetPath("Courses/Timetable.txt"), fstream::in);
	if (!TimetableFile.is_open()) {
		cout << "ERROR: Unable to open shared timetable file.";
		return;
	}

	string check, StudentID_Compare, CoursePath;
	streamoff BeginOfLine;
	while (!TimetableFile.eof()) {	
		BeginOfLine = TimetableFile.tellg();
		getline(TimetableFile, check);
		if (check.empty() || check == "\n") break;
		TimetableFile.seekg(BeginOfLine);

		getline(TimetableFile, StudentID_Compare, ',');
		getline(TimetableFile, CoursePath);
		if (StudentID_Compare == StudentID)
			Add(StudentID, CoursePath);
	}

	TimetableFile.close();
}

void Timetable::LoadAll()
{
	fstream TimetableFile;
	TimetableFile.open(GetPath("Courses/Timetable.txt"), fstream::in);
	if (!TimetableFile.is_open()) {
		cout << "ERROR: Unable to open shared timetable file.";
		return;
	}

	string check, StudentID, CoursePath;
	streamoff BeginOfLine;
	while (!TimetableFile.eof()) {
		BeginOfLine = TimetableFile.tellg();
		getline(TimetableFile, check);
		if (check.empty() || check == "\n") break;
		TimetableFile.seekg(BeginOfLine);

		getline(TimetableFile, StudentID, ',');
		getline(TimetableFile, CoursePath);
		Add(StudentID, CoursePath);
	}

	TimetableFile.close();
}

void Timetable::Update()
{
	fstream TimetableFile;
	TimetableFile.open(GetPath("Courses/Timetable.txt"), fstream::out | fstream::trunc);
	
	node * current = head;
	while (current != nullptr) {
		TimetableFile << current->StudentID << "," << current->CoursePath << "\n";
		current = current->next;
	}

	TimetableFile.close();
}

Timetable::~Timetable() {
	while (head != nullptr) {
		Timetable::node * current = head;
		head = current->next;
		delete current;
	}
}


///////////////////////////////////////////////////////////////////////////////

void ListYears() {
	fs::path p = GetPath("Courses");
	if (fs::is_empty(p)) {
		cout << "No years available.\n";
		return;
	}
	for (auto& p : fs::directory_iterator(GetPath("Courses"))) {
		string FileName = p.path().string();
		FileName = FileName.substr(FileName.find_last_of('\\') + 1);
		if (FileName == "Timetable.txt") continue;
		cout << FileName << "\n";
	}
}

void CreateYear(const string & Year) {
	fs::path p = GetPath("Courses/" + Year);
	if (fs::exists(p)) {
		cout << "Year " << Year << " already exists.";
		return;
	}
	fs::create_directory(p);
	cout << "Created " << Year << ".";
}

void EditYear(const string & Year_Old, const string & Year_New) {
	fs::path p_old = GetPath("Courses/" + Year_Old);
	fs::path p_new = GetPath("Courses/" + Year_New);
	if (!fs::exists(p_old)) {
		cout << "Year " << Year_Old << " does not exist.\n";
		return;
	}
	fs::rename(p_old, p_new);
	cout << "Renamed year " << Year_Old << " into year " << Year_New << ".\n";
}

void DeleteYear(const string & Year) {
	fs::path p = GetPath("Courses/" + Year);
	if (!fs::exists(p)) {
		cout << "Year " << Year << " does not exist.\n";
		return;
	}
	fs::remove_all(p);
	cout << "Deleted year " << Year << ".\n";
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
		cout << FileName << "\n";
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
	cout << "Created term " << Term << ".\n";
}

void EditTerm(const string & Year, const string & Term_Old, const string & Term_New) {
	fs::path p_old = GetPath("Courses/" + Year + "/" + Term_Old);
	fs::path p_new = GetPath("Courses/" + Year + "/" + Term_New);
	if (!fs::exists(p_old)) {
		cout << "Year " << Year << " and/or term " << Term_Old << " does not exist.\n";
		return;
	}
	fs::rename(p_old, p_new);
	cout << "Renamed " << Term_Old << " into " << Term_New << ".\n";
}

void DeleteTerm(const string & Year, const string & Term) {
	fs::path p = GetPath("Courses/" + Year + "/" + Term);
	if (!fs::exists(p)) {
		cout << "Year " << Year << " and/or term " << Term << " does not exist.\n";
		return;
	}
	fs::remove_all(p);
	cout << "Deleted term " << Term << ".\n";
}

void ListCourses(const string & Year, const string & Term) {
	fs::path p = GetPath("Courses/" + Year + "/" + Term);
	if (!fs::exists(p)) {
		cout << "Either year " << Year << " or term " << Term << " does not exist.";
		return;
	}
	if (fs::is_empty(p)) {
		cout << "No courses available.";
		return;
	}

	for (auto& p : fs::directory_iterator(GetPath("Courses/" + Year + "/" + Term))) {
		string FileName = p.path().string();
		FileName = FileName.substr(FileName.find_last_of('\\') + 1);
		if (FileName.find("_Attendance.txt") == FileName.npos && FileName.find("_Score.txt") == FileName.npos) {
			FileName = FileName.substr(0, FileName.find_last_of('_'));
			cout << FileName << "\n";
		}
	}
}

void CreateCourse(Course & NewCourse)
{
	// VALIDATE INPUT /////////////////////////////////////////////////////////////

	StudentList StudentList;
	StudentList::Student * current;
	LoadClass(StudentList, NewCourse.ClassID);
	if (StudentList.head == nullptr) {
		cout << "Course not imported: Class " << NewCourse.ClassID << " does not exist.";
		return;
	}

	fs::path YearTermPath = GetPath("Courses/" + NewCourse.Year + "/" + NewCourse.Term);
	if (!fs::exists(YearTermPath)) {
		cout << "Course not imported: Year " << NewCourse.Year << " and/or Term " << NewCourse.Term << " does not exist.";
		return;
	}

	const char wday_name[][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	fstream InfoFile, AttendanceFile, ScoreFile;

	InfoFile.open(GetPath("Courses/" + NewCourse.Year + "/" + NewCourse.Term + "/" + NewCourse.ID + "_" + NewCourse.ClassID + "_" + wday_name[NewCourse.Start.tm_wday] + "_Info.txt"), fstream::in);
	AttendanceFile.open(GetPath("Courses/" + NewCourse.Year + "/" + NewCourse.Term + "/" + NewCourse.ID + "_" + NewCourse.ClassID + "_" + wday_name[NewCourse.Start.tm_wday] + "_Attendance.txt"), fstream::in);
	if (InfoFile.is_open() || AttendanceFile.is_open()) {
		cout << "Course not imported: Course " << (NewCourse.ID + "_" + NewCourse.ClassID + "_" + wday_name[NewCourse.Start.tm_wday]) << " already exists.\n";
		return;
	}

	// apparently mktime() destroys tm after conversion
	tm CourseStartTime_tm = {0}, CourseEndTime_tm = {0};

	// CREATE INFO FILE ///////////////////////////////////////////////////////////

	CourseStartTime_tm = NewCourse.Start;
	CourseEndTime_tm = NewCourse.End;

	InfoFile.close();
	InfoFile.open(GetPath("Courses/" + NewCourse.Year + "/" + NewCourse.Term + "/" + NewCourse.ID + "_" + NewCourse.ClassID + "_" + wday_name[NewCourse.Start.tm_wday] + "_Info.txt"), fstream::out);
	InfoFile << NewCourse.Name << "\n";
	InfoFile << NewCourse.Room << "\n";
	InfoFile << mktime(&CourseStartTime_tm) << "\n";

	InfoFile << mktime(&CourseEndTime_tm) << "\n";
	/*InfoFile << NewCourse.Start.tm_year + 1900
		<< "-" << NewCourse.Start.tm_mon + 1
		<< "-" << NewCourse.Start.tm_mday
		<< " " << NewCourse.Start.tm_hour
		<< ":" << NewCourse.Start.tm_min
		<< " " << wday_name[NewCourse.Start.tm_wday] << "\n";
	InfoFile << NewCourse.End.tm_year + 1900
		<< "-" << NewCourse.End.tm_mon + 1
		<< "-" << NewCourse.End.tm_mday
		<< " " << NewCourse.End.tm_hour
		<< ":" << NewCourse.End.tm_min
		<< " " << wday_name[NewCourse.End.tm_wday] << "\n";*/
	InfoFile.close();

	// CREATE ATTENDANCE FILE /////////////////////////////////////////////////////

	CourseStartTime_tm = NewCourse.Start;
	CourseEndTime_tm = NewCourse.End;
	AttendanceFile.close();
	AttendanceFile.open(GetPath("Courses/" + NewCourse.Year + "/" + NewCourse.Term + "/" + NewCourse.ID + "_" + NewCourse.ClassID + "_" + wday_name[NewCourse.Start.tm_wday] + "_Attendance.txt"), fstream::out);
	current = StudentList.head;
	time_t Start = mktime(&CourseStartTime_tm);
	time_t End = mktime(&CourseEndTime_tm);
	size_t DC = ceil((End - Start) / (60 * 60 * 24 * 7));
	while (current != nullptr) {
		AttendanceFile << current->ID << ",";
		for (size_t i = 0; i < DC; i++)
			AttendanceFile << "-";
		AttendanceFile << "\n";
		current = current->next;
	}
	AttendanceFile.close();

	// CREATE SCOREBOARD FILE /////////////////////////////////////////////////////

	ScoreFile.close();
	ScoreFile.open(GetPath("Courses/" + NewCourse.Year + "/" + NewCourse.Term + "/" + NewCourse.ID + "_" + NewCourse.ClassID + "_Score.txt"), fstream::out);
	current = StudentList.head;
	while (current != nullptr) {
		ScoreFile << current->ID << ",0,0,0,0" << "\n";
		current = current->next;
	}
	ScoreFile.close();

	// ADD ENTRY TO TIMETABLE /////////////////////////////////////////////////////

	fstream SharedTimetable;
	SharedTimetable.open(GetPath("Courses/Timetable.txt"), fstream::out | fstream::app);
	current = StudentList.head;
	while (current != nullptr) {
		SharedTimetable << current->ID << "," << (NewCourse.Year + "/" + NewCourse.Term + "/" + NewCourse.ID + "_" + NewCourse.ClassID + "_" + wday_name[NewCourse.Start.tm_wday]) << "\n";
		current = current->next;
	}
	SharedTimetable.close();

	// All done
	StudentList.~StudentList();
	cout << "Successfully created course " << (NewCourse.ID + "_" + NewCourse.ClassID + "_" + wday_name[NewCourse.Start.tm_wday]) << "\n";
}

void ImportCourse(const string & FileName, const string & Year, const string & Term)
{
	// VALIDATE INPUT /////////////////////////////////////////////////////////////

	fstream CourseFile;
	CourseFile.open(GetPath("../Import/Courses/" + FileName), fstream::in);
	if (!CourseFile.is_open()) {
		cout << "File does not exist.";
		return;
	}

	fs::path YearTermPath = GetPath("Courses/" + Year + "/" + Term);
	if (!fs::exists(YearTermPath)) {
		cout << "Course not imported: Year " << Year << " and/or Term " << Term << " does not exist.";
		return;
	}

	// CREATE COURSES FROM FILE ///////////////////////////////////////////////////

	string skip;
	getline(CourseFile, skip);
	while (!CourseFile.eof()) {
		Course Course_New;
		string StartY, StartM, StartD, StartHH, StartMM;
		string EndY, EndM, EndD, EndHH, EndMM;
		string DoW;
		getline(CourseFile, skip, ',');
		getline(CourseFile, Course_New.ID, ',');
		getline(CourseFile, Course_New.Name, ',');
		getline(CourseFile, Course_New.ClassID, ',');
		getline(CourseFile, Course_New.LecturerID, ',');
		getline(CourseFile, StartY, '-');
		getline(CourseFile, StartM, '-');
		getline(CourseFile, StartD, ',');
		getline(CourseFile, EndY, '-');
		getline(CourseFile, EndM, '-');
		getline(CourseFile, EndD, ',');
		getline(CourseFile, DoW, ',');
		getline(CourseFile, StartHH, ':');
		getline(CourseFile, StartMM, ',');
		getline(CourseFile, EndHH, ':');
		getline(CourseFile, EndMM, ',');
		getline(CourseFile, Course_New.Room);

		Course_New.Start = {0};

		Course_New.Start.tm_year = stoi(StartY); Course_New.Start.tm_year -= 1900;
		Course_New.Start.tm_mon = stoi(StartM); Course_New.Start.tm_mon -= 1;
		Course_New.Start.tm_mday = stoi(StartD);
		Course_New.Start.tm_hour = stoi(StartHH);
			// test
			// Course_New.Start.tm_hour += 1;
		Course_New.Start.tm_min = stoi(StartMM);
		if (DoW == "Sun") Course_New.Start.tm_wday = 0;
		else if (DoW == "Mon") Course_New.Start.tm_wday = 1;
		else if (DoW == "Tue") Course_New.Start.tm_wday = 2;
		else if (DoW == "Wed") Course_New.Start.tm_wday = 3;
		else if (DoW == "Thu") Course_New.Start.tm_wday = 4;
		else if (DoW == "Fri") Course_New.Start.tm_wday = 5;
		else if (DoW == "Sat") Course_New.Start.tm_wday = 6;

		Course_New.End = {0};

		Course_New.End.tm_year = stoi(EndY); Course_New.End.tm_year -= 1900;
		Course_New.End.tm_mon = stoi(EndM); Course_New.End.tm_mon -= 1;
		Course_New.End.tm_mday = stoi(EndD);
		Course_New.End.tm_hour = stoi(EndHH);
			// test
			// Course_New.End.tm_hour += 1;
		Course_New.End.tm_min = stoi(EndMM);
		if (DoW == "Sun") Course_New.End.tm_wday = 0;
		else if (DoW == "Mon") Course_New.End.tm_wday = 1;
		else if (DoW == "Tue") Course_New.End.tm_wday = 2;
		else if (DoW == "Wed") Course_New.End.tm_wday = 3;
		else if (DoW == "Thu") Course_New.End.tm_wday = 4;
		else if (DoW == "Fri") Course_New.End.tm_wday = 5;
		else if (DoW == "Sat") Course_New.End.tm_wday = 6;

		Course_New.Year = Year;
		Course_New.Term = Term;

		CreateCourse(Course_New);
	}

	CourseFile.close();
}

void DeleteCourse(const string & Year, const string & Term, const string & CourseID, const string & ClassID)
{	
	// DELETE COURSE FILES ////////////////////////////////////////////////////////
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

	// DELETE ENTRIES FROM TIMETABLE //////////////////////////////////////////////
	Timetable SharedTimetable;
	SharedTimetable.LoadAll();
	
	Timetable::node * current = SharedTimetable.head;
	while (current != nullptr) {
		if (current->CoursePath.find(CourseID + "_" + ClassID) != current->CoursePath.npos) {
			SharedTimetable.Remove(CourseID, ClassID);
			current = SharedTimetable.head;
		}
		else {
			current = current->next;
		}
	}
	SharedTimetable.Update();
}
