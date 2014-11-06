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
			case MENU_mngr_supplyers:
				menu = menu_mngr_users();
				break;
			case MENU_mngr_spots:
				menu = menu_mngr_spots();
				break;
			case MENU_mngr_bikes:
				menu = menu_mngr_bikes();
				break;
			case MENU_mngr_users:
				menu = menu_mngr_users();
				break;
			case MENU_mngr_logs:
				menu = menu_mngr_logs();
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
	string pass;

	switch (option)
	{
	case 1:
		return MENU_regUsr;
	case 2:
		return MENU_ocUsr;
	case 3:
		cout << endl << " Please insert system password : ";
		pass = readPassword();
		if (pass == sys_password)
			return MENU_manager;
		cout << endl << endl << " Wrong password!" << endl << endl;
		system("pause");
		return MENU_start;
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

int Rede::menu_manager()
{
	print_menu_header();
	cout << "===> Management section" << endl << endl << "Select an option:" << endl;
	cout << " 1 - Supplying companies" << endl;
	cout << " 2 - Service spots" << endl;
	cout << " 3 - Bicicles" << endl;
	cout << " 4 - Registered users" << endl;
	cout << " 5 - Event logs" << endl;
	cout << " 6 - Change system password" << endl;
	cout << " 0 - Return to previous menu" << endl;

	int option;
	get_option(option, 0, 6);
	string pass;

	switch (option)
	{
	case 1:
		return MENU_mngr_supplyers;
	case 2:
		return MENU_mngr_spots;
	case 3:
		return MENU_mngr_bikes;
	case 4:
		return MENU_mngr_users;
	case 5:
		return MENU_mngr_logs;
	case 6:
		cout << endl << " Old password : ";
		pass = readPassword();
		if (pass != sys_password)
		{
			cout << endl << " ERROR : Wrong password" << endl << endl;
			system("pause");
			return MENU_start;
		}
		cout << endl << " New password : ";
		pass = readPassword();
		sys_password = pass;
		cout << endl << " Password successfully changed" << endl << endl;
		system("pause");
		return MENU_manager;
	}

	return MENU_start;
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
		cout << " 5 - See monthly service cost" << endl;
		cout << " 0 - Return to previous menu" << endl;

		int option;
		get_option(option, 0, 5);
		string old_pass, pass;
		vector<Registo*> regs;

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
			regs = user->getRegs();
			if (regs.size() == 0)
			{
				cout << endl << "Rental log is empty." << endl << endl;
				system("pause");
			}
			else
			{
				clear_screen();
				cout << endl << "===> Rental record:" << endl << endl;
				for (unsigned int i = 0; i < regs.size(); i++)
				{
					regs[i]->print_sem_user();
					cout << endl << endl;
				}
				system("pause");
			}
			break;
		case 5:
			cout << endl << " Monthly cost is 40 euros for all registered users." << endl << endl;
			system("pause");
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
	cout << endl << endl << " Enter user age : ";
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

	cout << endl << endl << " Enter user password : ";
	string pass = readPassword();

	Utilizador usr(nome, age, pass);
	Utilizador *ptr = new Utilizador;
	*ptr = usr;
	utilizadores.push_back(ptr);

	return 0;
}

// TO-DO //
int Rede::menu_mngr_supplyers()
{
	print_menu_header();

	cout << endl << endl << "===> Please select an option:" << endl;
	cout << " 1 - List all supplyers" << endl;
	cout << " 2 - Add new supplier" << endl;
	cout << " 3 - Edit existing supplier" << endl;
	cout << " 4 - Delete supplier" << endl;
	cout << " 0 - Return to previous menu" << endl;

	int option, index;
	get_option(option, 0, 4);
	string nome;

	switch (option)
	{
	case 0:
		return MENU_manager;
	case 1:
		// List suppliers
	case 2:
		cout << endl << " Insert new supplier's name : ";
		getline(cin, nome);
		// Adicionar nova empresa ao vetor

		return MENU_manager;
	case 3:
		// Edit supplier

		return MENU_manager;
	case 4:
		cout << endl << " Insert the name of the supplier to delete : ";
		getline(cin, nome);
		
		// Delete supplier

		return MENU_manager;
	}


	return MENU_start;
}

// TO-DO //
int Rede::menu_mngr_bikes()
{
	print_menu_header();

	cout << endl << endl << "===> Please select an option:" << endl;
	cout << " 1 - List all bikes" << endl;
	cout << " 2 - List available bikes" << endl;
	cout << " 3 - List broken bikes" << endl;
	cout << " 4 - List rented bikes" << endl;
	cout << " 5 - Repair all bikes" << endl;
	cout << " 6 - Add a new bike" << endl;
	cout << " 7 - Delete a bike" << endl;
	cout << " 0 - Return to previous menu" << endl;

	int option;
	get_option(option, 0, 7);

	switch (option)
	{
		// COMPLETAR
	}

	return MENU_manager;
}

// TO-DO //
int Rede::menu_mngr_logs()
{
	print_menu_header();

	cout << endl << endl << "===> Please select an option:" << endl;
	cout << " 1 - List all bikes" << endl;
	cout << " 2 - List available bikes" << endl;
	cout << " 3 - List broken bikes" << endl;
	cout << " 4 - List rented bikes" << endl;
	cout << " 5 - Repair all bikes" << endl;
	cout << " 6 - Add a new bike" << endl;
	cout << " 7 - Delete a bike" << endl;
	cout << " 0 - Return to previous menu" << endl;

	int option;
	get_option(option, 0, 7);

	return MENU_manager;
}

// TO-DO //
int Rede::menu_mngr_spots()
{
	return MENU_start;
}

// TO-DO //   Falta delete_user das outras classes
int Rede::menu_mngr_users()
{
	print_menu_header();

	cout << endl << endl << "===> Please select an option:" << endl;
	cout << " 1 - List all users" << endl;
	cout << " 2 - Create a new user" << endl;
	cout << " 3 - Edit existing user" << endl;
	cout << " 4 - Delete user" << endl;
	cout << " 0 - Return to previous menu" << endl;

	int option, index, idade;
	get_option(option, 0, 4);
	string nome, pass;

	switch (option)
	{
	case 0:
		return MENU_manager;
	case 1:
		if (utilizadores.size() == 0)
		{
			cout << endl << "There are no registered users." << endl << endl;
			system("pause");
			return MENU_mngr_users;
		}

		clear_screen();
		print_menu_header();
		cout << endl << "===> List of all users" << endl << endl;
		for (unsigned int i = 0; i < utilizadores.size(); i++)
		{
			cout << *utilizadores[i] << endl;
		}
		cout << endl;
		system("pause");
		return MENU_mngr_users;
	case 2:
		cout << endl << "Please enter new user name : ";
		getline(cin, nome);
		for (unsigned int i = 0; i < utilizadores.size(); i++)
		{
			if (utilizadores[i]->getNome() == nome)
			{
				cout << endl << "ERROR : That username already exists" << endl;
				system("pause");
				return MENU_mngr_users;
			}
		}

		createUser(nome);
		return MENU_mngr_users;
	case 3:
		cout << endl << " Enter name of user to edit : ";
		getline(cin, nome);
		
		for (index = 0; index < utilizadores.size(); index++)
		{
			if (utilizadores[index]->getNome() == nome)
				break;
		}
		if (index == utilizadores.size())
		{
			cout << endl << " ERROR : That user does not exit" << endl << endl;
			system("pause");
			return MENU_mngr_users;
		}
		cout << " Current user age : " << utilizadores[index]->getIdade();
		cout << endl << " New user age : ";
		while (true)
		{
			idade = readInt();
			if ((idade <= 0) || (idade > 120))
			{
				cout << endl << "ERROR : Invalid age. Try again." << endl << " New user age : ";
				continue;
			}
			break;
		}
		utilizadores[index]->setIdade(idade);
		cout << endl << " Current user password : " << utilizadores[index]->getPassword() << endl;
		cout << " New user password : ";
		pass = readPassword();
		utilizadores[index]->setPassword(pass);
		cout << endl << " User successfully edited." << endl << endl;
		system("pause");
		return MENU_mngr_users;
	case 4:
		cout << endl << " Enter name of user to delete : ";
		getline(cin, nome);

		/*
		Must verify:
			- if user exists
			- if user is currently renting a bike

		Then, call user deletion for Rede, Posto and Bicicleta
		*/
	}


	return MENU_start;
}