#include "Login.h"
#include "Menu.h"
#include "Student.h"
using namespace std;

int main(void) {
	string ID;
	char AccessClass;

	do {
		if (!LoginFilesExist()) {
			cout << "Press any key to exit.\n";
			_getch();
			break;
		}
		LoginMenu(ID, AccessClass);
		system("CLS");
		switch (AccessClass) {
			case AC_STUDENT: { Menu_Student(ID); break; }
			case AC_ADMIN: { Menu_Admin(ID); break; }
		}
		system("CLS");
	} while (1);
	
	return EXIT_SUCCESS;
}