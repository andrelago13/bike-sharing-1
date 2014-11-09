#include <iostream>
#include "Rede.h"

using namespace std;

int main()
{
	Rede network;
	try
	{
		network.menu_system();
	}
	catch (string e)
	{
		cout << e << endl << endl;
		system("pause");
		return -1;
	}

	return 0;
}