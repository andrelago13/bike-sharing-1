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

int Rede::menu_ocUsr()
{
	print_menu_header();
	cout << endl << endl << "===> Please select an option:" << endl;
	cout << " 1 - Rent a bike" << endl;
	cout << " 2 - Return a bike" << endl;
	cout << " 0 - Return to previous menu" << endl;

	int option, index, dias, custo;
	get_option(option, 0, 2);
	string nome, cartao, data;
	vector<Bicicleta*> bikes;
	Ut_ocasional user;
	Ut_ocasional *ptr;
	Registo reg;
	Registo *reg_ptr;


	switch (option)
	{
	case 1:
		if (postos.size() == 0)
		{
			cout << endl << " There are no service posts available." << endl << endl;
			system("pause");
			return MENU_ocUsr;
		}

		clear_screen();
		print_menu_header();
		cout << endl << "===> Select a service post." << endl;
		for (unsigned int i = 0; i < postos.size(); i++)
		{
			cout << " " << i + 1 << " - " << postos[i]->getID() << endl;
		}
		get_option(option, 1, postos.size());
		option--;

		bikes = postos[option]->getDisponiveis();

		if (bikes.size() == 0)
		{
			cout << endl << " There are no bikes available in the selected post." << endl << endl;
			system("pause");
			return MENU_ocUsr;
		}

		cout << endl << "===> Select a bike : " << endl;
		for (index = 0; index < bikes.size(); index++)
		{
			cout << " " << index+1 << " - " << bikes[index]->imprime();
			cout << endl;
		}

		cout << endl;
		get_option(index, 1, bikes.size());
		index--;

		cout << endl << " Please enter your name : ";
		getline(cin, nome);

		if (existeUtilizador(nome))
		{
			cout << endl << " That user already exists" << endl << endl;
			system("pause");
			return MENU_ocUsr;
		}

		cout << " Please enter your credit card number : ";
		getline(cin, cartao);
		user = Ut_ocasional(nome, 5, "", cartao);

		rented_bikes.push_back(bikes[index]);
		postos[option]->aluga(bikes[index]);
		ptr = new Ut_ocasional();
		*ptr = user;
		ocasionais.push_back(ptr);

		cout << " Please enter current date (YYYY/MM/DD) : ";
		getline(cin, data);
		if (data.size() != 10)
		{
			cout << endl << " Invalid date." << endl << endl;
			system("pause");
			return MENU_start;
		}
		
		reg.ID_Bicicleta = bikes[index]->getID();
		reg.ID_posto_origem = postos[option]->getID();
		reg.nome_utilizador = user.getNome();
		reg.levantamento = Data(data);
		

		reg_ptr = new Registo;
		*reg_ptr = reg;
		curr_rentals.push_back(reg_ptr);

		cout << endl << " Bike rented" << endl << endl;
		system("pause");
		return MENU_start;
	case 2:
		cout << endl << "Please enter your name : ";
		getline(cin, nome);

		for (index = 0; index < ocasionais.size(); index++)
		{
			if (ocasionais[index]->getNome() == nome)
				break;
		}

		if (index == ocasionais.size())
		{
			cout << endl << " No ocasional user was found with that name" << endl << endl;
			system("pause");
			return MENU_ocUsr;
		}

		cout << endl << endl << "===> Select a post to return the bike" << endl;
		for (unsigned int i = 0; i < postos.size(); i++)
		{
			cout << " " << i + 1 << " - " << postos[i]->getID() << endl;
		}
		get_option(option, 1, postos.size());
		option--;
		
		if (postos[option]->getEspacoLivre() <= 0)
		{
			cout << " This post has reached its occupation limit." << endl << endl;
			system("pause");
			return MENU_ocUsr;
		}

		cout << endl << " Insert current date (YYYY/MM/DD) : ";
		getline(cin, data);

		dias = dif_dias(curr_rentals[index]->levantamento, Data(data));
		
		if ((data.size() != 10) || (dias < 0))
		{
			cout << endl << " Invalid date." << endl << endl;
			system("pause");
			return MENU_ocUsr;
		}

		cout << endl << " Is this bike broken? (Y/N) : ";
		while (true)
		{
			char letter = _getch();
			if (toupper(letter) == 'Y')
			{
				rented_bikes[index]->setAvariada();
				cout << letter;
				break;
			}
			if (toupper(letter) == 'N')
				cout << letter;
				break;
		}

		custo = ocasionais[index]->getCusto();

		curr_rentals[index]->ficou_avariada = rented_bikes[index]->getAvariada();
		curr_rentals[index]->entrega = Data(data);
		curr_rentals[index]->ID_posto_chegada = postos[option]->getID();
		postos[option]->adicionaUtilizacao(curr_rentals[index]);
		ocasionais.erase(ocasionais.begin() + index);
		rented_bikes[index]->adicionaRegisto(curr_rentals[index]);
		postos[option]->adicionabicicleta(rented_bikes[index]);
		rented_bikes.erase(rented_bikes.begin() + index);
		curr_rentals.erase(curr_rentals.begin() + index);

		cout << endl << endl << " Bike returned. You were charged " << (dias + 1)*custo << " euros for " << dias + 1 << " day(s)" << endl << endl;
		system("pause");
		return MENU_start;

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

		int option, index, dias, custo, id;
		get_option(option, 0, 5);
		string old_pass, pass, nome, data;
		vector<Registo*> regs;

		//int option, index, dias, custo;
		//get_option(option, 0, 2);
		//string nome, cartao, data;
		vector<Bicicleta*> bikes;
		//Ut_ocasional user;
		Ut_ocasional *ptr;
		Registo reg;
		Registo *reg_ptr;

		switch (option)
		{
		case 1:
			reg_ptr = user->ultimoReg();
			//if ((reg_ptr->ID_posto_chegada == 0) || (reg_ptr->ID_posto_origem == 0))
			if (reg_ptr != NULL)
			{
				if ((reg_ptr->ID_posto_chegada <= 0))
				{
					cout << endl << " Every user can only rent a bike at a time." << endl << endl;
					system("pause");
					continue;
				}
			}


			if (postos.size() == 0)
			{
				cout << endl << " There are no service posts available." << endl << endl;
				system("pause");
				continue;
			}

			clear_screen();
			print_menu_header();
			cout << endl << "===> Select a service post." << endl;
			for (unsigned int i = 0; i < postos.size(); i++)
			{
				cout << " " << i + 1 << " - " << postos[i]->getID() << endl;
			}
			get_option(option, 1, postos.size());
			option--;

			bikes = postos[option]->getDisponiveis();

			if (bikes.size() == 0)
			{
				cout << endl << " There are no bikes available in the selected post." << endl << endl;
				system("pause");
				continue;
			}

			cout << endl << "===> Select a bike : " << endl;
			for (index = 0; index < bikes.size(); index++)
			{
				cout << " " << index + 1 << " - " << bikes[index]->imprime();
				cout << endl;
			}

			cout << endl;
			get_option(index, 1, bikes.size());
			index--;

			rented_bikes_freq.push_back(bikes[index]);
			postos[option]->aluga(bikes[index]);

			cout << " Please enter current date (YYYY/MM/DD) : ";
			getline(cin, data);
			if (data.size() != 10)
			{
				cout << endl << " Invalid date." << endl << endl;
				system("pause");
				return MENU_start;
			}

			reg.ID_Bicicleta = bikes[index]->getID();
			reg.ID_posto_origem = postos[option]->getID();
			reg.nome_utilizador = user->getNome();
			reg.levantamento = Data(data);


			reg_ptr = new Registo;
			*reg_ptr = reg;
			user->adicionaRegisto(reg_ptr);

			cout << endl << " Bike rented" << endl << endl;
			system("pause");
			continue;
		case 2:
			// Return bike
			reg_ptr = user->ultimoReg();
			if ((reg_ptr->ID_posto_chegada != 0) || (reg_ptr->ID_posto_origem == 0))
			{
				cout << endl << " You have no bike to return" << endl << endl;
				system("pause");
				continue;
			}

			cout << endl << endl << "===> Select a post to return the bike" << endl;
			for (unsigned int i = 0; i < postos.size(); i++)
			{
				cout << " " << i + 1 << " - " << postos[i]->getID() << endl;
			}
			get_option(option, 1, postos.size());
			option--;

			if (postos[option]->getEspacoLivre() <= 0)
			{
				cout << " This post has reached its occupation limit." << endl << endl;
				system("pause");
				return MENU_ocUsr;
			}

			cout << endl << " Insert current date (YYYY/MM/DD) : ";
			getline(cin, data);

			dias = dif_dias(reg_ptr->levantamento, Data(data));

			if ((data.size() != 10) || (dias < 0))
			{
				cout << endl << " Invalid date." << endl << endl;
				system("pause");
				return MENU_ocUsr;
			}

			cout << endl << " Is this bike broken? (Y/N) : ";
			while (true)
			{
				char letter = _getch();
				if (toupper(letter) == 'Y')
				{
					id = reg.ID_Bicicleta;
					for (index = 0; index < rented_bikes_freq.size(); index++)
					{
						if (rented_bikes_freq[index]->getID() == id)
						{
							rented_bikes_freq[index]->setAvariada();
							break;
						}
					}
					cout << letter;
					break;
				}
				if (toupper(letter) == 'N')
					cout << letter;
				break;
			}

			reg_ptr->ficou_avariada = rented_bikes[index]->getAvariada();
			reg_ptr->entrega = Data(data);
			reg_ptr->ID_posto_chegada = postos[option]->getID();
			postos[option]->adicionaUtilizacao(reg_ptr);
			rented_bikes_freq[index]->adicionaRegisto(reg_ptr);
			postos[option]->adicionabicicleta(rented_bikes_freq[index]);
			rented_bikes_freq.erase(rented_bikes_freq.begin() + index);

			cout << endl << endl << " Bike returned." << endl << endl;
			system("pause");
			continue;
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
	cout << " 1 - Show the time a user has rented a bike" << endl;
	cout << " 2 - Show money to charge a user" << endl;
	cout << " 3 - Show number of users served by a company" << endl;
	cout << " 4 - Show ongoing rentals" << endl;
	cout << " 5 - Show most frequent service user" << endl;

	int option;
	get_option(option, 0, 5);

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

bool Rede::existeUtilizador(string nome)
{
	for (unsigned int i = 0; i < utilizadores.size(); i++)
	{
		if (utilizadores[i]->getNome() == nome)
			return true;
	}

	for (unsigned int i = 0; i < ocasionais.size(); i++)
	{
		if (ocasionais[i]->getNome() == nome)
			return true;
	}

	return false;
}

int Rede::tipoUser(string nome)
{
	for (unsigned int i = 0; i < utilizadores.size(); i++)
	{
		if (utilizadores[i]->getNome() == nome)
			return utilizadores[i]->getTipo();
	}

	for (unsigned int i = 0; i < ocasionais.size(); i++)
	{
		if (ocasionais[i]->getNome() == nome)
			ocasionais[i]->getTipo();
	}

	return -1;
}