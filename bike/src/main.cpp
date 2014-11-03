#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

//Test 2

using namespace std;

int menu_start();
int menu_system();
void clear_screen();   ////////// Pending due to problems with system("cls"); ////////////

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

void clear_screen() {} /////// PENDING ////////////////////////////////////77


int menu_start()
{
	cout << endl << endl << "            Bike-sharing network" << endl << endl;
	cout << "   Welcome to our bike-sharing network! Pick up and drop bikes from several spots in the city and enjoy the fresh air in town!" << endl;
	cout << endl << endl << "==> Please select your type of login:" << endl;
	cout << "1 - Registered user" << endl;
	cout << "2 - Occasional user" << endl;
	cout << endl << "3 - Management access" << endl;

	string option;
	bool invalid = true;

	while(invalid)
	{
		getline(cin, option);
		cin.ignore(1000, '\n');
		
		switch(option)
		{
		case "1":
			return 1;
			invalid = false;
			break;
		case "2":
			return 2;
			invalid = false;
			break;
		case "3":
			return 3;
			invalid = false;
			break;
		default:
			cout << "Invalid option, please try again : ";
		}
	}


	return -1;
}


