#include <iostream>
#include "Rede.h"

// TEST INCLUDES ------------- REMOVE
#include "Tools.h"

using namespace std;

int main()
{
	Rede network;

	Utilizador usr("Andre", 19, "123456");
	network.addUser(usr);

	network.menu_system();

	return 0;
}