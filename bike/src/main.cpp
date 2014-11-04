#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

int menu_system();
#define MENU_exit -1
int menu_start();
#define MENU_start 0
int menu_regUsr();
#define MENU_regUsr 1
int menu_ocUsr();
#define MENU_ocUsr 2
int menu_manager();
#define MENU_manager 3
void menu_exit_prog();

void clear_screen();
int str_to_int(string &str);
void get_option(int &option, int min_range, int max_range);
void print_menu_header();

int main()
{
	return menu_system();
}

int menu_system()
{
	/* The system in this function manages the interactions between menus, i.e., the transitions between them

	 Each menu is assigned a number, its ID. Every menu has a corresponding function. This function's return
	 specifies which menu must be loaded next, according to the user's actions during it's execution. For example,
	 if a menu function wishes to return to the main menu, it must return 0, main menu's ID.*/

	int menu = 0;

	while(menu >= 0)
	{
		clear_screen();

		try
		{
			switch(menu)
			{
			case 0:
				menu = menu_start();
				break;
			case 1:
				menu = menu_regUsr();
				break;
			case 2:
				menu = menu_ocUsr();
				break;
			case 3:
				menu = menu_manager();
				break;
			case -1:
				break;
			default:
				menu = MENU_exit;
				break;
			}
		}
		catch(string &error)
		{
			cout << endl << endl << error << endl << endl;
			return -1;
		}
	}

	menu_exit_prog();
	system("pause");
	return 0;
}

void clear_screen()
{
	system("cls");
}

int menu_start()
{
	cout << endl << endl << "            ______ _ _              _                _" << endl;
	cout << "            | ___ (_) |            | |              (_)" << endl;
	cout << "            | |_/ /_| | _____   ___| |__   __ _ _ __ _ _ __   __ _" << endl;
	cout << "            | ___ \\ | |/ / _ \\ / __| '_ \\ / _` | '__| | '_ \\ / _` |" << endl;
	cout << "            | |_/ / |   <  __/ \\__ \\ | | | (_| | |  | | | | | (_| |" << endl;
	cout << "            \\____/|_|_|\\_\\___| |___/_| |_|\\__,_|_|  |_|_| |_|\\__, |" << endl;
	cout << "                                                              __/ |" << endl;
	cout << "                                                             |___/ " << endl << endl;
	cout << "   Welcome to our bike-sharing network!" << endl;
	cout << endl << endl << "===> Please select your type of login:" << endl;
	cout << " 1 - Registered user" << endl;
	cout << " 2 - Occasional user" << endl;
	cout << " 3 - Management access" << endl;
	cout << " 0 - Exit program" << endl;

	int option;
	get_option(option, 0, 3);

	switch (option)
	{
	case 1:
		return MENU_regUsr;
	case 2:
		return MENU_ocUsr;
	case 3:
		return MENU_manager;
	case 0:
		return MENU_exit;
	}

	return MENU_exit;
}

int str_to_int(string &str)
{
	int result = atoi(str.c_str());

	if ((result == 0) && (str != "0"))
	{
		string error = "ERROR : Invalid input, must be a number";
		throw error;
	}

	return result;
}

void get_option(int &option, int min_range, int max_range)
{
	string option_str;

	while (true)
	{
		cout << "Selection : ";
		getline(cin, option_str);
		option = 0;

		try
		{
			option = str_to_int(option_str);
		}
		catch (string error)
		{
			cout << error << endl;
			continue;
		}

		if ((option < min_range) || (option > max_range))
		{
			cout << "Invalid option, not in range." << endl;
			continue;
		}

		break;
	}
}

// TO-DO //
int menu_regUsr()
{
	// There must be a way for a user to login to the Rede
	/*
	print_menu_header();
	cout << "===> Registered user secion" << endl << endl << "Select an option:" << endl;
	cout << " 1 - Rent a bike" << endl;
	cout << " 2 - Return a bike" << endl;
	cout << " 3 - Report bike malfunction" << endl;
	cout << " 0 - Return to previous menu" << endl;

	int option;
	get_option(option, 0, 5);

	switch (option)
	{
	case 0:
		return MENU_start;
	}*/

	return MENU_exit;
}

// TO-DO //
int menu_ocUsr()
{
	return 0;
}

// TO-DO //
int menu_manager()
{
	print_menu_header();
	cout << "===> Management section" << endl << endl << "Select an option:" << endl;
	cout << " 1 - Supplying companies" << endl;
	cout << " 2 - Service spots" << endl;
	cout << " 3 - Bicicles" << endl;
	cout << " 4 - Registered users" << endl;
	cout << " 5 - Event logs" << endl;
	cout << " 0 - Return to previous menu" << endl;

	int option;
	get_option(option, 0, 5);

	switch (option)
	{
	case 0:
		return MENU_start;
	}

	return MENU_exit;
}

void print_menu_header()
{
	cout << "      __          ___     __             __          __  " << endl;
	cout << "     |__) | |__/ |__     /__` |__|  /\\  |__) | |\\ | / _`" << endl;
	cout << "     |__) | |  \\ |___    .__/ |  | /~~\\ |  \\ | | \\| \\__>" << endl << endl;
}

void menu_exit_prog()
{
	clear_screen();
	cout << endl << endl <<  "           _____                 _     ____" << endl;
	cout << "          / ____|               | |   |  _ \\" << endl;
	cout << "         | |  __  ___   ___   __| |   | |_) |" << endl;
	cout << "         | | |_ |/ _ \\ / _ \\ / _` |   |  _ <| | | |/ _ \\" << endl;
	cout << "         | |__| | (_) | (_) | (_| |   | |_) | |_| |  __/" << endl;
	cout << "          \\_____|\\___/ \\___/ \\__,_|   |____/ \\__, |\\___|" << endl;
	cout << "                                             __/ |     " << endl;
	cout << "                                            |___/      " << endl << endl << endl << endl;
}