#include "Courses.h"


bool Courses::input(const char *path, vector <Courses> &a) {
	ifstream im;
	im.open(path);
	if (!im.is_open()) {
		return false;
	}
	else {
		string temp;
		getline(im, temp);
		while (!im.eof()) {
			string no, id, name, Class, lectureraccount, dayofweek, room ,sday, smonth, syear, eday, emonth, eyear, shour, sminute,ehour,eminute;
			getline(im, no, ',');
			getline(im, id, ',');
			getline(im, name, ',');
			getline(im, Class, ',');
			getline(im, lectureraccount, ',');
			getline(im, syear, '-');getline(im, smonth, '-');getline(im, sday, ',');
			getline(im, eyear, '-'); getline(im, emonth, '-'); getline(im, eday, ',');
			getline(im, dayofweek, ',');
			getline(im, shour, ':'); getline(im, sminute, ',');
			getline(im, ehour, ':'); getline(im, eminute, ',');
			getline(im, room);

			a.push_back(Courses(id, name, Class, lectureraccount, stoi(sday), stoi(smonth), stoi(syear), stoi(eday), stoi(emonth), stoi(eyear), dayofweek, stoi(shour), stoi(sminute), stoi(ehour), stoi(eminute), room));
		}
		im.close();
		return true;
	}
}

bool Courses::output(const char *path, const vector <Courses> &a) {
	ofstream ex;
	ex.open(path);
	if (!ex.is_open()) {
		return false;
	}
	else {
		for (int i = 0; i < a.size(); i++) {
			ex << i + 1 << ","
				<< a[i].ID << ","
				<< a[i].Name << ","
				<< a[i].Class << ","
				<< a[i].LecturerAccount << ","
				<< a[i].start.year << "-"
				<< a[i].start.month << "-"
				<< a[i].start.day << ","
				<< a[i].end.year << "-"
				<< a[i].end.month << "-"
				<< a[i].end.day << ","
				<< a[i].DayofWeek << ","
				<< a[i].Timestart.hour << ":"
				<< a[i].Timestart.minute << ","
				<< a[i].Timeend.hour << ":"
				<< a[i].Timeend.minute << ","
				<< a[i].Room << endl;

		}
	}
}