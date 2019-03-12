#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct date1 {
	int day;
	int month;
	int year;
};

struct time {
	int hour;
	int minute;
};

class Courses {
	//attribute
private:
	string ID;
	string Name;
	string Class;
	string LecturerAccount;
	date1 start;
	date1 end;
	string DayofWeek;
	time Timestart;
	time Timeend;
	string Room;
	//constructors
public:
	Courses(string id, string name, string CLASS, string lectureraccount, int sday, int smonth, int syear, int eday, int emonth, int eyear, string dayofweek, int shour, int sminute, int ehour, int eminute, string room) {
		ID = id;
		Name = name;
		Class = CLASS;
		LecturerAccount = lectureraccount;
		start.day = sday;start.month = smonth;start.year = syear;
		end.day = eday;end.month = emonth;end.year = eyear;
		DayofWeek = dayofweek;
		Timestart.hour = shour; Timestart.minute = sminute;
		Timeend.hour = ehour; Timeend.minute = eminute;
		Room = room;
	}
public:
	static bool input(const char *path, vector <Courses> &course);
	static bool output(const char *path, const vector <Courses> &course);
};
