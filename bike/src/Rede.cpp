#include "Rede.h"
#include "Tools.h"
#include <iostream>
#include <conio.h>

using namespace std;

Rede::~Rede()
{
	for (unsigned int i = 0; i < utilizadores.size(); i++)
		delete utilizadores[i];

	for (unsigned int i = 0; i < postos.size(); i++)
		delete postos[i];
}

int Rede::addUser(Utilizador user)
{
	for (unsigned int i = 0; i < utilizadores.size(); i++)
	{
		if (*utilizadores[i] == user)
			return -1;
	}

	Utilizador *ptr = new Utilizador;
	*ptr = user;
	utilizadores.push_back(ptr);
	return 0;
}

int Rede::menu_system()
{
	/* The system in this function manages the interactions between menus, i.e., the transitions between them

	Each menu is assigned a number, its ID. Every menu has a corresponding function. This function's return
	specifies which menu must be loaded next, according to the user's actions during it's execution. For example,
	if a menu function wishes to return to the main menu, it must return 0, main menu's ID.*/

	int menu = 0;

	clear_screen();

	while (menu >= 0)
	{
		try
		{
			switch (menu)
			{
			case MENU_start:
				menu = menu_start();
				break;
			case MENU_regUsr:
				menu = menu_regUsr();
				break;
			case MENU_ocUsr:
				menu = menu_ocUsr();
				break;
			case MENU_manager:
				menu = menu_manager();
				break;
			case MENU_exit:
				menu = MENU_exit;
				break;
			default:
				string err = "ERROR : Unexpected function return.";
				throw err;
				break;
			}
		}
		catch (string &error)
		{
			cout << endl << endl << error << endl << endl;
			return -1;
		}

		clear_screen();
	}

	menu_exit_prog();
	system("pause");
	return 0;
}

int Rede::menu_start()
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

int Rede::menu_regUsr()
{
	print_menu_header();

	cout << endl << " User name : ";
	string username;
	getline(cin, username);

	int index = 0;
	bool existe = false;

	for (; index < utilizadores.size(); index++)
	{
		if (utilizadores[index]->getNome() == username)
		{
			existe = true;
			break;
		}
	}

	if (existe)
	{
		cout << " Password : ";
		string pass = readPassword();

		if (utilizadores[index]->getPassword() == pass)
		{
			while (true)
			{
				return menu_regUsr_logged(utilizadores[index]);
			}
		}
		else
		{
			cout << endl << endl << " Wrong password!" << endl << endl;
			system("pause");
			return MENU_start;
		}
	}
	else
	{
		cout << endl << endl << " No user was found with that name.\n Would you like to create a new one? (Y/N) ";

		while (true)
		{
			char letter = _getch();
			if (toupper(letter) == 'Y')
			{
				int result = createUser(username);
				if (result == 0)
					cout << endl << endl << "    User created successfully!" << endl;
				else
					cout << endl << endl << "    An error has occurred while creating user." << endl;
				system("pause");
				break;
			}
			if (toupper(letter) == 'N')
				return MENU_start;
		}
	}

	return MENU_start;
}

// TO-DO //
int Rede::menu_ocUsr()
{
	print_menu_header();
	cout << endl << endl << "===> Please select an option:" << endl;
	cout << " 1 - Rent a bike" << endl;
	cout << " 2 - Return a bike" << endl;
	cout << " 0 - Return to previous menu" << endl;

	int option;
	get_option(option, 0, 2);

	switch (option)
	{
	case 1:
		// Rent bike

		break;
	case 2:
		// Return bike

		break;
	case 0:
		return MENU_start;
	}

	return MENU_start;
}

// TO-DO //
int Rede::menu_manager()
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

// TO-DO //
int Rede::menu_regUsr_logged(Utilizador *user)
{
	while (true)
	{
		clear_screen();
		print_menu_header();

		cout << endl << endl << "===> Please select an option:" << endl;
		cout << " 1 - Rent a bike" << endl;
		cout << " 2 - Return a bike" << endl;
		cout << " 3 - Change password" << endl;
		cout << " 4 - View rental log" << endl;
		cout << " 0 - Return to previous menu" << endl;

		int option;
		get_option(option, 0, 4);
		string old_pass, pass;

		switch (option)
		{
		case 1:
			// Rent bike

			break;
		case 2:
			// Return bike

			break;
		case 3:
			cout << endl << " Enter old password : ";

			old_pass = readPassword();
			if (old_pass != user->getPassword())
			{
				cout << endl << "Wrong password" << endl;
				system("pause");
				continue;
			}
			cout << endl << " Enter new password : ";
			pass = readPassword();
			user->setPassword(pass);
			cout << endl << " Password changed successfully!" << endl;
			system("pause");
			break;
		case 4:

			break;
		case 0:
			return MENU_start;
		}
	}

	return MENU_start;
}

void Rede::print_menu_header()
{
	cout << "      __          ___     __             __          __  " << endl;
	cout << "     |__) | |__/ |__     /__` |__|  /\\  |__) | |\\ | / _`" << endl;
	cout << "     |__) | |  \\ |___    .__/ |  | /~~\\ |  \\ | | \\| \\__>" << endl << endl;
}

void Rede::menu_exit_prog()
{
	cout << endl << endl << "           _____                 _     ____" << endl;
	cout << "          / ____|               | |   |  _ \\" << endl;
	cout << "         | |  __  ___   ___   __| |   | |_) |" << endl;
	cout << "         | | |_ |/ _ \\ / _ \\ / _` |   |  _ <| | | |/ _ \\" << endl;
	cout << "         | |__| | (_) | (_) | (_| |   | |_) | |_| |  __/" << endl;
	cout << "          \\_____|\\___/ \\___/ \\__,_|   |____/ \\__, |\\___|" << endl;
	cout << "                                             __/ |     " << endl;
	cout << "                                            |___/      " << endl << endl << endl << endl;
}

int Rede::createUser(string nome)
{
	cout << endl << endl << " Enter your age : ";
	int age;

	while (true)
	{
		age = readInt();
		if ((age <= 0) || (age > 120))
		{
			cout << endl << "ERROR : Invalid age. Try again." << endl << " Enter your age : ";
			continue;
		}
		break;
	}

	cout << endl << endl << " Enter your password : ";
	string pass = readPassword();

	Utilizador usr(nome, age, pass);
	Utilizador *ptr = new Utilizador;
	*ptr = usr;
	utilizadores.push_back(ptr);

	return 0;
}