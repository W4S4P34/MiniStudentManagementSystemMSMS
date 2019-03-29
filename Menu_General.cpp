#include "Menu.h"

void Capitalize(string & string) {
	for (size_t i = 0; i < string.length(); i++)
		string[i] = ::toupper(string[i]);
}

void ShowHelp_General() {
	cout << "[SHARED COMMANDS]\n"
		<< "logout : Log out\n"
		<< "-      : Log out\n"
		<< "quit   : Exit\n"
		<< "cls    : Clear the screen\n"
		<< "info   : Show current user information (not available for admins)\n"
		<< "help   : Show this command list and other user-specific commands\n"
		<< "passwd : Change password\n"
		<< "\n";
}
