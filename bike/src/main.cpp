#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int menu_start();

int main()
{
	int menu = 0;

	while(menu >= 0)
	{
		switch(menu)
		{
		case 0:
			menu = menu_start();
			break;
		}

	}


	return 0;
}

int menu_start()
{
	cout << endl << endl << "            Bike-sharing network" << endl << endl;
	cout << "   Welcome to our bike-sharing network! Pick up and drop bikes from several spots in the city and enjoy the fresh air in town!" << endl;

	return -1;
}


