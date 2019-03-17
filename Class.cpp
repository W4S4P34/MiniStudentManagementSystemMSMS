#include "Class.h"

void ListClasses() {
	fs::path p = GetPath("Classes");
	if (fs::is_empty(p)) {
		cout << "No classes available.\n";
		return;
	}
	for (auto& p : fs::directory_iterator(GetPath("Classes"))) {
		string FileName = p.path().string();
		FileName = FileName.substr(FileName.find_last_of('\\') + 1);
		FileName = FileName.substr(0, FileName.find_last_of('.'));
		cout << FileName << endl;
	}
}