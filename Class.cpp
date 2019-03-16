#include "Class.h"

void ListClasses() {
	for (auto& p : fs::directory_iterator(GetPath("Classes"))) {
		string FileName = p.path().string();
		FileName = FileName.substr(FileName.find_last_of('\\') + 1);
		FileName = FileName.substr(0, FileName.find_last_of('.'));
		if (FileName.empty()) {
			cout << "No classes available.\n";
			return;
		}
		cout << FileName << endl;
	}
}