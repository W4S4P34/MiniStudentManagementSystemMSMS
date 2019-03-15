#include "Login.h"
#include "Menu.h"
using namespace std;

int main(void) {
	string ID;
	char AccessClass;

	do {
		if (!doLoginFilesExist()) {
			cout << "Press any key to exit.\n";
			_getch();
			break;
		}
		LoginMenu(ID, AccessClass);
		system("CLS");
		ShowMenu(AccessClass);
		cout << "\n";
		Interpret(ID, AccessClass);
		system("CLS");
	} while (1);
	
	return EXIT_SUCCESS;
}