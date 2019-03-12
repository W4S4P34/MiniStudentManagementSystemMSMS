#include "Menu.h"
#include "Login.h"

int main(void) {
	do {
		char r;
		do {
			r = LoginMenu();
		} while (r == -1);
		switch (r) {
			case 0: Menu_Admin(); break;
			case 1: Menu_Student(); break;
			case 2: Menu_Lecturer(); break;
			default: cout << "EXCEPTION FOUND ||||||_";
		}
		system("CLS");
	} while (1);

	system("PAUSE > NUL");
	return EXIT_SUCCESS;
}