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

int main()
{
	return menu_system();
}

int menu_system()
{
	int menu = 0;

	while(menu >= 0)
	{
		try
		{
			switch(menu)
			{
			case 0:
				menu = menu_start();
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
	cout << endl << endl << "            Bike-sharing network" << endl << endl;
	cout << "   Welcome to our bike-sharing network! Pick up and drop bikes from several spots in the city and enjoy the fresh air in town!" << endl;
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
