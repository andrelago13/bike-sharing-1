#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

int menu_start();
int menu_system();
void clear_screen();
int str_to_int(string &str);
void get_option(int &option, int min_range, int max_range);
int menu_regUsr();
int menu_ocUsr();
int menu_manager();

int main()
{
	return menu_system();
}

int menu_system()
{
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
			default:
				menu = -1;
				break;
			}
		}
		catch(string &error)
		{
			cout << endl << endl << error << endl << endl;
			return -1;
		}
	}

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
	cout << endl << endl << "==> Please select your type of login:" << endl;
	cout << "1 - Registered user" << endl;
	cout << "2 - Occasional user" << endl;
	cout << "3 - Management access" << endl;

	int option;
	get_option(option, 1, 3);

	switch (option)
	{
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 3;
	}

	return -1;
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
	return 0;
}

// TO-DO //
int menu_ocUsr()
{
	return 0;
}

// TO-DO //
int menu_manager()
{
	return 0;
}