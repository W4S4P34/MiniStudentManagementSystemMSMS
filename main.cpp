#include "_INCLUDES_.h"

int main() {
	string ID;
	char AccessClass;

	do {
		// Check whether Login Files are exist
		if (!LoginFilesExist()) {
			cout << "Press any key to exit.\n";
			_getch();
			break;
		}
		// Login entries including ID entry and Passwork entry
		LoginMenu(ID, AccessClass);
		system("CLS");
		// Open the control menu which depends on AccessClass
		switch (AccessClass) {
			case AC_STUDENT: { Menu_Student(ID); break; }
			case AC_LECTURER: { Menu_Lecturer(ID); break; }
			case AC_ADMIN: { Menu_Admin(ID); break; }
		}
		system("CLS");
	} while (1);
	
	return EXIT_SUCCESS;
}