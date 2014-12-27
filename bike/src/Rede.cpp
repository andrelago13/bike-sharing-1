#include "Rede.h"
#include "Tools.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <boost/tr1/unordered_set.hpp>

using namespace std;

			/////////////////////////
			// Main Rede functions //
			/////////////////////////

Rede::~Rede()
{
	for (unsigned int i = 0; i < utilizadores.size(); i++)
		delete utilizadores[i];

	for (unsigned int i = 0; i < postos.size(); i++)
		delete postos[i];

	for (unsigned int i = 0; i < ocasionais.size(); i++)
		delete ocasionais[i];

	for (unsigned int i = 0; i < curr_rentals.size(); i++)
		delete curr_rentals[i];

	for (unsigned int i = 0; i < rented_bikes.size(); i++)
		delete rented_bikes[i];

	for (unsigned int i = 0; i < rented_bikes_freq.size(); i++)
		delete rented_bikes_freq[i];
}



/**
* \brief Store Rede information from text files.
* Stores information on rede.txt, rede_bikes.txt, rede_spots.txt and rede_user.txt according to format specified by function storeInfo.
*/
void Rede::storeInfo()
{
	//////////////////////////////////////////////////////////
	/////////////// Main file - rede.txt /////////////////////
	//////////////////////////////////////////////////////////

	/*
	This file saves Rede password, supplyer's names and add Rede Registo's
	in the following format:

	1 - Rede password
	2 - LOOP : supplyer company names
	3 - '-' to separate 2 from 4
	4 - LOOP : all Rede Registo's from completed rentals
	5 - '#' to separate 4 from 6
	6 - LOOP : all Rede Registo's from ongoing rentals
	*/

	ofstream main_file("rede.txt");
	
	// Store password
	main_file << sys_password << endl;

	// Store supplyer company's names
	for (unsigned int i = 0; i < empresas.size(); i++)
	{
		main_file << empresas[i].getNome() << endl;
	}

	main_file << "-" << endl;
	vector<Registo *> all_regs = get_regs();

	// Store Registo's from completed rentals
	for (unsigned int i = 0; i < all_regs.size(); i++)
	{
		string temp = all_regs[i]->get_str();
		main_file << temp;
	}

	main_file << "#" << endl;

	// Store Registo's from ongoing rentals
	for (unsigned int i = 0; i < curr_rentals.size(); i++)
	{
		string temp = curr_rentals[i]->get_str();
		main_file << temp;
	}

	main_file.close();

	//////////////////////////////////////////////////////////
	////////////// Spots file - rede_spots.txt ///////////////
	//////////////////////////////////////////////////////////

	/*
	This file saves all Rede PostoServico objects in the following format:

	LOOP:
		1 - Posto ID
		2 - Posto lotacao
		3 - LOOP : Bicicleta objects stored in this PostoServico (see Bicicleta file)
		4 - '#' to separate from other Postos
	*/

	ofstream spots_file("rede_spots.txt");

	for (unsigned int i = 0; i < postos.size(); i++)
	{
		// Store Posto ID and lotacao
		spots_file << postos[i]->getID() << endl << postos[i]->getLotacao() << endl;
		vector<Bicicleta *> bicis = postos[i]->getBicicletas();

		// Store Posto Bicicleta's
		for (unsigned int j = 0; j < bicis.size(); j++)
		{
			spots_file << bicis[j]->get_str();
		}
		spots_file << "#" << endl;
	}

	spots_file.close();

	//////////////////////////////////////////////////////////
	////////////// Users file - rede_user.txt ////////////////
	//////////////////////////////////////////////////////////

	/*
	This file savesall Rede Utilizador and Ut_ocasional objects in the following format:

	LOOP:
	1 - Utilizador nome
	2 - Password
	3 - Idade
	4 - Tipo
	(5) - If Tipo==0, this line does not existe, if Tipo==1, this line is Ut_ocasional's cartao
	*/

	ofstream user_file("rede_user.txt");

	// Store registered users
	for (unsigned int i = 0; i < utilizadores.size(); i++)
	{
		user_file << utilizadores[i]->get_str();
	}
	// Store occasional users
	for (unsigned int i = 0; i < ocasionais.size(); i++)
	{
		user_file << ocasionais[i]->get_str();
	}

	user_file.close();

	//////////////////////////////////////////////////////////
	////////////// Bikes file - rede_bikes.txt ///////////////
	//////////////////////////////////////////////////////////

	/*
	This file saves all Rede Bicicleta objects, corresponding to currently
	rented bikes, in the following format:

	LOOP - bikes rented by occasional users:
		1 - Bicicleta ID
		2 - Tipo
		3 - Tamanho
		4 - Velocidades
		5 - Preco
		6 - Empresa
	'#' - to separate from next loop
	LOOP - bikes rented by registered users (same format as before)
	*/

	ofstream bike_file("rede_bikes.txt");

	// Store bikes rented by occasional users
	for (unsigned int i = 0; i < rented_bikes.size(); i++)
	{
		bike_file << rented_bikes[i]->get_str();
	}

	bike_file << "#" << endl;

	// Store bikes rented by registered users
	for (unsigned int i = 0; i < rented_bikes_freq.size(); i++)
	{
		bike_file << rented_bikes_freq[i]->get_str();
	}

	bike_file.close();
}

/**
* \brief Load Rede information from text files.
* Loads information on rede.txt, rede_bikes.txt, rede_spots.txt and rede_user.txt according to format specified by function storeInfo.
*/
void Rede::loadInfo()

{
	//////////////////////////////////////////////////////////
	/////////////// Main file - rede.txt /////////////////////
	//////////////////////////////////////////////////////////

	ifstream main_file("rede.txt");

	string temp;
	if (main_file.is_open() == true)
		getline(main_file, temp);
	sys_password = temp;

	while ((main_file.peek() != ((int) '-')) && (main_file.peek() != EOF) && (main_file.is_open() == true))
	{
		getline(main_file, temp);
		Empresa emp(temp);
		empresas.push_back(temp);
	}

	vector<Registo *> all_regs;

	getline(main_file, temp);  // To remove character '-' from file

	while ((main_file.peek() != '#') && (main_file.peek() != EOF) && (main_file.is_open() == true))
	{
		stringstream ss(ios_base::app | ios_base::out);
		string temp;
		ss.clear();
		for (unsigned int i = 0; i < 7; i++)
		{
			getline(main_file, temp);
			ss << temp << endl;
		}
		Registo reg, *reg_ptr;
		reg.make_from_str(ss.str());
		reg_ptr = new Registo;
		*reg_ptr = reg;
		all_regs.push_back(reg_ptr);
	}

	getline(main_file, temp);  // To remove character '#' from file

	while ((main_file.peek() != EOF) && (main_file.is_open() == true))  // Detect end of file
	{
		stringstream ss;
		string temp;
		ss.clear();
		for (unsigned int i = 0; i < 7; i++)
		{
			getline(main_file, temp);
			ss << temp << endl;
		}
		Registo reg, *reg_ptr;
		reg.make_from_str(ss.str());
		reg_ptr = new Registo;
		*reg_ptr = reg;
		curr_rentals.push_back(reg_ptr);
	}

	main_file.close();

	//////////////////////////////////////////////////////////
	///////////// Spots file - rede_spots.txt ////////////////
	//////////////////////////////////////////////////////////

	// Loads information on rede_spots.txt according to format specified by function storeInfo

	ifstream spots_file("rede_spots.txt");


	if (spots_file.is_open())
	{
		while ((spots_file.peek() != EOF) && (!spots_file.eof())) // Detect end of file
		{
			string temp;
			int id, lotacao;
			getline(spots_file, temp);
			id = str_to_int(temp);
			getline(spots_file, temp);
			lotacao = str_to_int(temp);

			PostoServico posto(id, 0, lotacao);
			PostoServico *posto_ptr;
			posto_ptr = new PostoServico;
			*posto_ptr = posto;

			if (spots_file.peek() == '#')
			{
				postos.push_back(posto_ptr);
				getline(spots_file, temp);  // to remove character '#' from file
				continue;
			}

			while ((spots_file.peek() != '#') && (spots_file.peek() != EOF) && (!spots_file.eof()))
			{
				stringstream ss;
				for (int i = 0; i < 7; i++)
				{
					getline(spots_file, temp);
					ss << temp << endl;
				}
				Bicicleta bici, *bici_ptr;
				bici.make_str(ss.str());
				bici_ptr = new Bicicleta;
				*bici_ptr = bici;
				posto_ptr->adicionabicicleta(bici_ptr);

				for (unsigned int i = 0; i < empresas.size(); i++)
				{
					if (empresas[i].getNome() == bici_ptr->getEmpresa())
						empresas[i].adicionaBicicleta(bici_ptr);
				}
			}
			postos.push_back(posto_ptr);
			getline(spots_file, temp); // to remove character '#' from file
		}
	}

	spots_file.close();

	//////////////////////////////////////////////////////////
	///////////// Users  file - rede_user.txt ////////////////
	//////////////////////////////////////////////////////////

	// Loads information on rede_user.txt according to format specified by function storeInfo

	ifstream user_file("rede_user.txt");
	string nome, pass, cartao, morada;
	int idade, tipo, contacto;

	if (user_file.is_open())
	{
		while ((user_file.peek() != EOF) && (!user_file.eof()))  // Detect end of file
		{
			getline(user_file, nome);
			getline(user_file, pass);
			getline(user_file, temp);
			idade = str_to_int(temp);
			getline(user_file, temp);
			if (temp == "0")
			{
				getline(user_file, morada);
				getline(user_file, temp);
				contacto = str_to_int(temp);
				Utilizador user(nome, idade, pass, contacto, morada);
				Utilizador *user_ptr;
				user_ptr = new Utilizador;
				*user_ptr = user;
				utilizadores.push_back(user_ptr);
			}
			else
			{
				getline(user_file, temp);
				getline(user_file, temp);
				getline(user_file, cartao);
				Ut_ocasional oc(nome, idade, pass, cartao);
				Ut_ocasional *oc_ptr;
				oc_ptr = new Ut_ocasional;
				*oc_ptr = oc;
				ocasionais.push_back(oc_ptr);
			}
		}
	}

	user_file.close();

	//////////////////////////////////////////////////////////
	///////////// Bikes file - rede_bikes.txt ////////////////
	//////////////////////////////////////////////////////////

	// Loads information on rede_bikes.txt according to format specified by function storeInfo

	ifstream bike_file("rede_bikes.txt");

	if (bike_file.is_open())
	{
		while (bike_file.peek() != '#')
		{
			stringstream ss;
			ss.clear();
			for (int i = 0; i < 7; i++)
			{
				getline(bike_file, temp);
				ss << temp << endl;
			}
			Bicicleta bici, *bici_ptr;
			bici.make_str(ss.str());
			bici_ptr = new Bicicleta;
			*bici_ptr = bici;
			rented_bikes.push_back(bici_ptr);

			for (unsigned int i = 0; i < empresas.size(); i++)
			{
				if (empresas[i].getNome() == bici_ptr->getEmpresa())
					empresas[i].adicionaBicicleta(bici_ptr);
			}
		}

		getline(bike_file, temp); // to remove character '#' from file

		while ((bike_file.peek() != EOF) || (!bike_file.eof()))
		{
			stringstream ss;
			ss.clear();
			for (int i = 0; i < 7; i++)
			{
				getline(bike_file, temp);
				ss << temp << endl;
			}
			Bicicleta bici, *bici_ptr;
			bici.make_str(ss.str());
			bici_ptr = new Bicicleta;
			*bici_ptr = bici;
			rented_bikes_freq.push_back(bici_ptr);

			for (unsigned int i = 0; i < empresas.size(); i++)
			{
				if (empresas[i].getNome() == bici_ptr->getEmpresa())
					empresas[i].adicionaBicicleta(bici_ptr);
			}
		}
	}

	bike_file.close();

	assign_regs(all_regs);  // See function documentation
}

/**
* \brief Add's a Utilizador object to the system
* \param user - Utilizador object to be added
* \return 0 if successfull, 1 if Utilizador already exists
* Add a user to the registered users vector, if there is none equal to it
*/
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
	cout << "User created sucessfully!";
	return 0;
}

/**
* \brief Create and add a Utilizador object
* \param nome - name of the Utilizador object to create
* \return 0 if successfull, 1 if Utilizador already exists
* Creates a Utilizador object and inserts it in the vector, without repetitions
*/
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

	cout << endl << endl << " Enter user contact : ";
	int contact;

	while (true)
	{
		contact = readInt();
		if ((contact <= 0) || (contact > 999999999))
		{
			cout << endl << "ERROR : Invalid contact. Try again." << endl << " Enter your contact : ";
			continue;
		}
		break;
	}

	cout << endl << endl << " Enter user address : ";
	string address;
	getline(cin, address);

	Utilizador usr(nome, age, pass, contact, address);
	Utilizador *ptr = new Utilizador;
	*ptr = usr;
	utilizadores.push_back(ptr);
	cout << endl << "User created sucessfully!" << endl;
	return 0;
}

/**
* \brief Create and add a Bicicleta object to a PostoServico
* \return 0 if successfull, 1 if Bicicleta already exists
* Creates a Bicicleta object and inserts it in the correct vector, in this case, of a PostoServico
*/
int Rede::create_add_bike()
{
	clear_screen();
	print_menu_header();
	cout << endl << " Please enter bike ID : ";
	int id = readInt();
	vector<Bicicleta *> bikes;

	for (unsigned int i = 0; i < empresas.size(); i++)
	{
		bikes = empresas[i].getBicicletas();
		for (unsigned int j = 0; j < bikes.size(); j++)
		{
			if (bikes[j]->getID() == id)
			{
				cout << endl << " There already is a bike with that ID";
				return -1;
			}
		}
	}

	cout << endl << endl << " Please select a bike type : " << endl;
	cout << " 1 - Eletrica" << endl;
	cout << " 2 - Com cesto" << endl;
	cout << " 3 - Sem cesto" << endl;
	cout << " 4 - Passeio" << endl;
	cout << " 5 - Montanha" << endl;
	cout << " 6 - Corrida" << endl;

	int option, preco, velocidades;
	get_option(option, 1, 6);
	string tipo, tamanho, empresa;

	switch (option)
	{
	case 1:
		tipo = "eletrica";
		break;
	case 2:
		tipo = "com cesto";
		break;
	case 3:
		tipo = "sem cesto";
		break;
	case 4:
		tipo = "passeio";
		break;
	case 5:
		tipo = "montanha";
		break;
	case 6:
		tipo = "corrida";
		break;
	}

	cout << endl << endl << " Please select a bike size : " << endl;
	cout << " 1 - Crianca" << endl;
	cout << " 2 - Adulto" << endl;

	get_option(option, 1, 2);

	switch (option)
	{
	case 1:
		tamanho = "crianca";
		break;
	case 2:
		tamanho = "adulto";
		break;
	}

	cout << endl << endl << " Please indicate bike shifts (1-5)  : ";

	get_option(option, 1, 5);

	velocidades = option;

	cout << endl << endl << " Please indicate a bike price : ";
	preco = readInt();

	cout << endl << " Please indicate a company to associate the bike : ";
	getline(cin, empresa);

	int index;
	bool found = false;

	for (unsigned int i = 0; i < empresas.size(); i++)
	{
		if (empresas[i].getNome() == empresa)
		{
			found = true;
			index = i;
		}
	}

	if (!found)
	{
		cout << endl << " No company was found with that name.";
		return -1;
	}

	int posto_id;

	cout << endl << " Please select a post to insert the bike : ";

	for (unsigned int i = 1; i <= postos.size(); i++)
	{
		cout << " " << i << " -> Posto " << postos[i - 1]->getID() << endl;
	}
	cout << endl;
	get_option(posto_id, 1, postos.size());

	if (postos[option - 1]->getEspacoLivre() <= 0)
	{
		cout << endl << " That post has no room for one more bike.";
		return -1;
	}

	Bicicleta bike(id, tipo, tamanho, velocidades, false, preco);
	bike.setEmpresa(empresa);
	Bicicleta *bike_ptr = new Bicicleta;
	*bike_ptr = bike;

	empresas[index].adicionaBicicleta(bike_ptr);
	postos[posto_id-1]->adicionabicicleta(bike_ptr);

	cout << endl << " Bike added successfully.";
	return 0;
}

/**
* \brief Resets all Rede information
* Restarts all Rede information by clearing all vector members of the class
*/
void Rede::reset()
{
	empresas.clear();
	postos.clear();
	utilizadores.clear();
	ocasionais.clear();
	curr_rentals.clear();
	rented_bikes.clear();
	rented_bikes_freq.clear();
	sys_password = "";
}

/**
* \brief Assing Registo object pointers in a vector to the class members
* \param regs - vector of Registo pointers to assign to class members
* This function is meant for the load information process.
*	During the store information process, the program saves all Registo's from completed rentals in a vector, and later
* saves it in the text file.
*	At the load information process, this function gets the vector with all the meantioned above Registo's, and add's this Registo's
* to the correct objects (Bicicleta, PostoServico and Utilizador).
*/
void Rede::assign_regs(vector<Registo *> &regs)
{
	// Assign to PostoServico and corresponding Bicicleta's
	for (unsigned int i = 0; i < postos.size(); i++)
	{
		for (unsigned int j = 0; j < regs.size(); j++)
		{
			if ((regs[j]->ID_posto_chegada == postos[i]->getID()) || (regs[j]->ID_posto_origem == postos[i]->getID()))
				postos[i]->adicionaUtilizacao(regs[j]);
		}

		vector<Bicicleta *> bikes = postos[i]->getBicicletas();

		for (unsigned int j = 0; j < bikes.size(); j++)
		{
			for (unsigned int k = 0; k < regs.size(); k++)
			{
				if (regs[k]->ID_Bicicleta == bikes[j]->getID())
					bikes[j]->adicionaRegisto(regs[k]);
			}
		}
	}

	// Assign to Utilizador
	for (unsigned int i = 0; i < utilizadores.size(); i++)
	{
		for (unsigned int j = 0; j < regs.size(); j++)
		{
			if (regs[j]->nome_utilizador == utilizadores[i]->getNome())
				utilizadores[i]->adicionaRegisto(regs[j]);
		}
	}

	// Assign to Bicicleta's on rented_bikes vector
	for (unsigned int i = 0; i < rented_bikes.size(); i++)
	{
		for (unsigned int j = 0; j < regs.size(); j++)
		{
			if (regs[j]->ID_Bicicleta == rented_bikes[i]->getID())
				rented_bikes[i]->adicionaRegisto(regs[j]);
		}
	}

	// Assign to Bicicleta's on rented_bikes_freq vector
	for (unsigned int i = 0; i < rented_bikes_freq.size(); i++)
	{
		for (unsigned int j = 0; j < regs.size(); j++)
		{
			if (regs[j]->ID_Bicicleta == rented_bikes_freq[i]->getID())
				rented_bikes_freq[i]->adicionaRegisto(regs[j]);
		}
	}
}


			/////////////////////////
			// Auxiliary functions //
			/////////////////////////


/**
* \brief Checks if user exists
\param nome - name of Utilizador to search
* Searches for the existance of a Utilizador with that name
\return true is Utilizador already exists, false otherwise
*/
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

// Returns the user type if it exists, or -1 if it doesn't
/**
* \brief Find type of a user
* \return user type if it exists, -1 otherwise
\param nome - name of Utilizador whose type must be determined
* Searches for a user with the given name to find out it's type (occasional or registered)
*/
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

/**
\brief Determine if a bike is rented and by whom
\param id_bici - ID of Bicicleta to search
\param print - decide wether to print messages to the user or not
\return name of user renting the Bicicleta, or an empty string if Bicicleta is available
*/
string Rede::is_busy(int id_bici, bool print) const
{
	for (unsigned int i = 0; i < curr_rentals.size(); i++)
	{
		if (rented_bikes[i]->getID() == id_bici)
		{
			if (print)
				cout << " This bike is currently rented by occasional user " << curr_rentals[i]->nome_utilizador << endl;
			return curr_rentals[i]->nome_utilizador;
		}
	}

	for (unsigned int i = 0; i < utilizadores.size(); i++)
	{
		Registo *reg_ptr;
		reg_ptr = utilizadores[i]->ultimoReg();

		if ((reg_ptr != NULL) && (reg_ptr->ID_Bicicleta == id_bici) && (reg_ptr->ID_posto_chegada == 0))
		{
			if (print)
				cout << " This bike is currently rented by registered user " << utilizadores[i]->getNome() << endl;
			return utilizadores[i]->getNome();;
		}
	}

	return "";
}

/**
\brief Get pointers to all Registo objects relative to completed rentals in the system
\return vector with mentioned Registo pointers, without repeated ones
This function is useful for storeInfo
*/
vector<Registo *> Rede::get_regs() const
{
	vector<Registo *> result;

	for (unsigned int i = 0; i < postos.size(); i++)
	{
		insert_no_repeat(result, postos[i]->getUtlizacao());
	}

	for (unsigned int i = 0; i < utilizadores.size(); i++)
	{
		insert_no_repeat(result, utilizadores[i]->getRegs());
	}

	for (unsigned int i = 0; i < rented_bikes.size(); i++)
	{
		insert_no_repeat(result, rented_bikes[i]->getRegsBicis());
	}

	for (unsigned int i = 0; i < rented_bikes_freq.size(); i++)
	{
		insert_no_repeat(result, rented_bikes_freq[i]->getRegsBicis());
	}

	return result;
}

void Rede::update_old_users(Data data_atual)
{
	for (unsigned int i = 0; i < utilizadores.size(); i++)
	{
		Data d1;
		vector<Registo *> regs = utilizadores[i]->getRegs();
		if (!regs.empty())
		{
			Registo last_reg = *utilizadores[i]->ultimoReg();
			if (dif_meses(last_reg.entrega, data_atual) >= USER_MONTHS_LIMIT)
				util_antigos.insert(*utilizadores[i]);
		}
		else
			util_antigos.insert(*utilizadores[i]);
	}
}

			////////////////
			// Rede menus //
			////////////////


/**
\brief Menu controller function
This function controls the whole menu system, by calling the function corresponding to the pretended menu.
Basically, it consists of a while(true) cycle that keeps calling the menu functions and analyzes their return values.
The return of all menu functions indicates the menu that should be loaded next.
Each menu is assigned a number. For example, if a menu function wishes to return to the main menu, it must return 0, main menu's number.
This function also calls loadInfo and storeInfo
*/
int Rede::menu_system()
{
	loadInfo();

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
				menu = menu_mngr_supplyers();
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
	storeInfo();
	return 0;
}

/**
\brief Rede starting menu
Main Rede menu. This is the menu loaded upon system startup, and allows access to all the other menus
*/
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
	// Registered user menu
	case 1:
		return MENU_regUsr;
	// Occasional user menu
	case 2:
		return MENU_ocUsr;
	// Management menu. Requires access by password
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

/**
\brief Registered user menu
This is the menu where registered users perform login, and where new users are registered
*/
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

	if (existe) // If user exists, authenticates it
	{
		cout << " Password : ";
		string pass = readPassword();

		if (utilizadores[index]->getPassword() == pass)
		{
			return menu_regUsr_logged(utilizadores[index]);
		}
		else
		{
			cout << endl << endl << " Wrong password!" << endl << endl; // wrong password message
			system("pause");
			return MENU_start;
		}
	}
	else
	{
		cout << endl << endl << " No user was found with that name.\n Would you like to create a new one? (Y/N) "; // if inexistant user, asks if it should create a new one

		while (true)
		{
			char letter = _getch();
			if (toupper(letter) == 'Y') // create new user
			{
				int result = createUser(username);
				if (result != 0)
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

/**
\brief Ocasional user menu
This is the menu where occasional users rent and return bikes
*/
int Rede::menu_ocUsr()
{
	
	print_menu_header();
	cout << endl << endl << "===> Please select an option:" << endl;
	cout << " 1 - Rent a bike" << endl;
	cout << " 2 - Return a bike" << endl;
	cout << " 0 - Return to previous menu" << endl;

	int option, index, dias, custo, cartao_int;
	stringstream ss;
	get_option(option, 0, 2);
	string nome, cartao, data;
	vector<Bicicleta*> bikes;
	Ut_ocasional user;
	Ut_ocasional *ptr;
	Registo reg;
	Registo *reg_ptr;


	switch (option)
	{
	// Rent a bike
	case 1:
		if (postos.size() == 0)
		{
			cout << endl << " There are no service posts available." << endl << endl;
			system("pause");
			return MENU_ocUsr;
		}

		clear_screen();
		print_menu_header();
		// Service post selection
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

		// Bike selection
		cout << endl << "===> Select a bike : " << endl;
		for (index = 0; index < bikes.size(); index++)
		{
			cout << " " << index+1 << " - " << bikes[index]->imprime();
			cout << endl;
		}

		cout << endl;
		get_option(index, 1, bikes.size());
		index--;

		// Enter name, used to keep track of user
		cout << endl << " Please enter your name : ";
		getline(cin, nome);

		if (existeUtilizador(nome))
		{
			cout << endl << " That user already exists" << endl << endl;
			system("pause");
			return MENU_ocUsr;
		}

		// User credit card
		cout << " Please enter your credit card number : ";
		cartao_int = readInt();
		ss.clear();
		ss << cartao_int;
		cartao = ss.str();
		user = Ut_ocasional(nome, 5, "", cartao);

		// Current date
		cout << " Please enter current date (YYYY/MM/DD) : ";
		getline(cin, data);
		//if (data.size() != 10)
		if (!valid_date(data))
		{
			cout << endl << " Invalid date." << endl << endl;
			system("pause");
			return MENU_start;
		}
		else
		{
			reg_ptr = bikes[index]->ultimo_reg();
			if ((reg_ptr != NULL) && (Data(data) < reg_ptr->entrega))
			{
				cout << endl << " Current date must be greater than date of last bike rental" << endl << endl;
				system("pause");
				return MENU_start;
			}
		}

		rented_bikes.push_back(bikes[index]);
		postos[option]->aluga(bikes[index]);
		ptr = new Ut_ocasional();
		*ptr = user;
		ocasionais.push_back(ptr);
		
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
	// Return a bike
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

		// Return post selection
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
		
		if (!valid_date(data))
		{
			cout << endl << " Invalid date." << endl << endl;
			system("pause");
			return MENU_ocUsr;
		}
		dias = dif_dias(curr_rentals[index]->levantamento, Data(data));
		if (dias < 0)
		{
			cout << endl << " Return date must be after rental date." << endl << endl;
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

/**
\brief Management main menu
This is the menu for system management. For it to be accessed, a system password is requested on menu_start().
This menu allows CRUD operations on all members of the Rede
*/
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
	cout << " 7 - Reset network" << endl;
	cout << " 0 - Return to previous menu" << endl;

	int option;
	get_option(option, 0, 7);
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
	case 7:
		cout << endl << " Are you sure you wish to reset the network system? (Y/N) ";

		while (true)
		{
			char letter = _getch();
			if (toupper(letter) == 'Y')
			{
				reset();
				cout << endl << endl << " System and password have been reset." << endl << endl;
				system("pause");
				return MENU_start;
			}
			if (toupper(letter) == 'N')
				return MENU_manager;
		}
	}

	return MENU_start;
}

/**
\brief Logged in registered user menu
This is a slightly different menu, because it needed to receive an argument, the logged in user. Therefore, it's return is "analyzed" by
menu_regUsr() and not by menu_system(), but it's return means the same.
This menu allows the logged in registered user to rent and return bikes, change his password, view his rental log and see his
monthly service cost
\param user - pointer to the user that just logged in, that allows the function to know which Utilizador object to modify
\return Same as other menu functions, it's effect will be the same
*/
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
		cout << " 6 - Edit user info" << endl;
		cout << " 0 - Return to previous menu" << endl;

		int option, index, dias, custo, id, idade, numero;
		get_option(option, 0, 6);
		string old_pass, pass, nome, data, morada;
		vector<Registo*> regs;

		vector<Bicicleta*> bikes;
		Ut_ocasional *ptr;
		Registo reg;
		Registo *reg_ptr, *reg_ptr2;

		hashUtilizador::iterator it;

		switch (option)
		{
		// Rent a bike
		case 1:
			reg_ptr = user->ultimoReg();
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

			cout << " Please enter current date (YYYY/MM/DD) : ";
			getline(cin, data);

			if (!valid_date(data))
			{
				cout << endl << " Invalid date." << endl << endl;
				system("pause");
				continue;
			}
			reg_ptr = user->ultimoReg();
			reg_ptr2 = bikes[index]->ultimo_reg();
			if ((reg_ptr != NULL) && (reg_ptr2 != NULL ) & ((Data(data) < reg_ptr->entrega) || (Data(data) < reg_ptr2->entrega)))
			{
				cout << endl << " Current date must be later than last bike and user rentals." << endl << endl;
				system("pause");
				continue;
			}

			rented_bikes_freq.push_back(bikes[index]);
			postos[option]->aluga(bikes[index]);

			reg.ID_Bicicleta = bikes[index]->getID();
			reg.ID_posto_origem = postos[option]->getID();
			reg.nome_utilizador = user->getNome();
			reg.levantamento = Data(data);


			reg_ptr = new Registo;
			*reg_ptr = reg;
			user->adicionaRegisto(reg_ptr);

			it = util_antigos.find(*user);
			if (it != util_antigos.end())
				util_antigos.erase(it);

			cout << endl << " Bike rented" << endl << endl;
			system("pause");
			continue;
		// Return a bike
		case 2:
			reg_ptr = user->ultimoReg();
			if ((reg_ptr == NULL) || (reg_ptr->ID_posto_chegada != 0) || (reg_ptr->ID_posto_origem == 0))
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
				continue;
			}

			cout << endl << " Insert current date (YYYY/MM/DD) : ";
			getline(cin, data);

			if (!valid_date(data))
			{
				cout << endl << " Invalid date." << endl << endl;
				system("pause");
				continue;
			}
			dias = dif_dias(reg_ptr->levantamento, Data(data));

			if (dias < 0)
			{
				cout << endl << " Invalid date." << endl << endl;
				system("pause");
				continue;
			}

			id = reg_ptr->ID_Bicicleta;
			for (index = 0; index < rented_bikes_freq.size(); index++)
			{
				if (rented_bikes_freq[index]->getID() == id)
					break;
			}

			cout << endl << " Is this bike broken? (Y/N) : ";
			while (true)
			{
				char letter = _getch();
				if (toupper(letter) == 'Y')
				{
					rented_bikes_freq[index]->setAvariada();
					cout << letter;
					break;
				}
				if (toupper(letter) == 'N')
				{
					cout << letter;
					break;
				}
			}

			reg_ptr->ficou_avariada = rented_bikes_freq[index]->getAvariada();
			reg_ptr->entrega = Data(data);
			reg_ptr->ID_posto_chegada = postos[option]->getID();
			postos[option]->adicionaUtilizacao(reg_ptr);
			rented_bikes_freq[index]->adicionaRegisto(reg_ptr);
			postos[option]->adicionabicicleta(rented_bikes_freq[index]);
			rented_bikes_freq.erase(rented_bikes_freq.begin() + index);

			it = util_antigos.find(*user);
			if (it != util_antigos.end())
				util_antigos.erase(it);

			cout << endl << endl << " Bike returned." << endl << endl;
			system("pause");
			continue;
		// Change user password
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
		// See user rental log
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
		// See monthly service cost
		case 5:
			cout << endl << " Monthly cost is 40 euros for all registered users." << endl << endl;
			system("pause");
			break;
		// Edit user info
		case 6:
			cout << " Current user age : " << user->getIdade();
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
			user->setIdade(idade);

			cout << endl << " Current user address : " << user->getMorada();
			cout << endl << " New user address : ";
			getline(cin, morada);
			user->setMorada(morada);

			cout << " Current user contact : " << user->getContacto();
			cout << endl << " New user contact : ";
			while (true)
			{
				numero = readInt();
				if ((numero <= 0) || (numero > 999999999))
				{
					cout << endl << "ERROR : Invalid contact. Try again." << endl << " New user contact : ";
					continue;
				}
				break;
			}
			user->setContacto(numero);

			cout << endl << " User successfully edited." << endl << endl;
			system("pause");

			break;
		case 0:
			return MENU_start;
		}
	}

	return MENU_start;
}

/**
\brief Prints menu header
This is a very simple function that only prints a small "Bike Sharing" header that appears in all Rede menus, except
for the start menu, which has it's own, bigger, header
*/
void Rede::print_menu_header()
{
	cout << "      __          ___     __             __          __  " << endl;
	cout << "     |__) | |__/ |__     /__` |__|  /\\  |__) | |\\ | / _`" << endl;
	cout << "     |__) | |  \\ |___    .__/ |  | /~~\\ |  \\ | | \\| \\__>" << endl << endl;
}

/**
\brief Print goodbye message
This is a very simple function that prints a big "Goodbye" message upon program exit, through the menu system
*/
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

/**
\brief Management menu for supplying companies
Allows the system manager to perform CRUD operations on Empresa objects. It also allows the listing of all
bikes for a supplying company
*/
int Rede::menu_mngr_supplyers()
{
	print_menu_header();

	cout << endl << endl << "===> Please select an option:" << endl;
	cout << " 1 - List all supplyers" << endl;
	cout << " 2 - Add new supplier" << endl;
	cout << " 3 - Edit existing supplier" << endl;
	cout << " 4 - Delete supplier" << endl;
	cout << " 5 - List all bikes for a supplyer" << endl;
	cout << " 0 - Return to previous menu" << endl;

	int option, index;
	get_option(option, 0, 5);
	string nome;
	Empresa emp;
	vector<int> id_s;
	vector<Bicicleta *> bicis;

	switch (option)
	{
	// List all supplyers
	case 1:
		if (empresas.size() == 0)
		{
			cout << endl << " There are no registered supplyers." << endl << endl;
			system("pause");
			return MENU_mngr_supplyers;
		}

		cout << endl << "===> List of supplyers:" << endl << endl;
		for (unsigned int i = 0; i < empresas.size(); i++)
		{
			cout << " -> " << empresas[i].getNome() << endl;
		}
		cout << endl;
		system("pause");
		return MENU_mngr_supplyers;

	// Add new supplyer
	case 2:
		cout << endl << " Insert new supplier's name : ";
		getline(cin, nome);

		for (unsigned int i = 0; i < empresas.size(); i++)
		{
			if (empresas[i].getNome() == nome)
			{
				cout << endl << " There already is a supplyer with that name." << endl << endl;
				system("pause");
				return MENU_mngr_supplyers;
			}
		}
		
		emp = Empresa(nome);
		empresas.push_back(emp);

		cout << endl << endl << " Supplyer added to the network." << endl << endl;
		system("pause");
		return MENU_mngr_supplyers;

	// Edit a supplyer
	case 3:
		cout << endl << " Please insert name of supplyer to edit : ";
		getline(cin, nome);

		for (unsigned int i = 0; i < empresas.size(); i++)
		{
			if (empresas[i].getNome() == nome)
			{
				cout << endl << " Insert new supplyer name : ";
				getline(cin, nome);

				for (unsigned int j = 0; j < empresas.size(); j++)
				{
					if ((empresas[j].getNome() == nome) && (j != i))
					{
						cout << endl << " There already is a supplyer with that name." << endl << endl;
						system("pause");
						return MENU_mngr_supplyers;
					}
				}

				empresas[i].setNome(nome);
				cout << endl << endl << " Supplyer edited successfully." << endl << endl;
				system("pause");
				return MENU_mngr_supplyers;
			}
		}

		cout << endl << endl << " No supplyer was found with that name." << endl << endl;
		system("pause");
		return MENU_mngr_supplyers;

	// Delete a supplyer
	case 4:
		cout << endl << " Insert the name of the supplier to delete : ";
		getline(cin, nome);

		index = -1;
		for (unsigned int i = 0; i < empresas.size(); i++)
		{
			if (empresas[i].getNome() == nome)
			{
				index = i;
			}
		}

		if (index == -1)
		{
			cout << endl << endl << " No supplyer was found with that name." << endl << endl;
			system("pause");
			return MENU_mngr_supplyers;
		}

		bicis = empresas[index].getBicicletas();
		for (unsigned int i = 0; i < bicis.size(); i++)
		{
			id_s.push_back(bicis[i]->getID());
		}

		for (unsigned int i = 0; i < id_s.size(); i++)
		{
			if (is_busy(id_s[i], false).size() != 0)
			{
				cout << endl << " It is impossible to delete this supplyer because one or more bikes are currently being rented." << endl << endl;
				system("pause");
				return MENU_mngr_supplyers;
			}
		}

		for (unsigned int i = 0; i < id_s.size(); i++)
		{
			for (unsigned int j = 0; j < utilizadores.size(); j++)
				utilizadores[j]->remove_bici(id_s[i]);
			for (unsigned int j = 0; j < postos.size(); j++)
				postos[j]->removebicicleta(id_s[i]);
		}

		empresas.erase(empresas.begin() + index);
		
		cout << endl << " Supplyer successfully removed." << endl << endl;
		system("pause");
		return MENU_mngr_supplyers;

	// List all bikes for a supplyer
	case 5:
		cout << endl << " Insert the name of the supplier to list : ";
		getline(cin, nome);

		index = -1;
		for (unsigned int i = 0; i < empresas.size(); i++)
		{
			if (empresas[i].getNome() == nome)
			{
				index = i;
				bicis = empresas[i].getBicicletas();
			}
		}

		if (index == -1)
		{
			cout << endl << endl << " No supplyer was found with that name." << endl << endl;
			system("pause");
			return MENU_mngr_supplyers;
		}

		if (bicis.size() == 0)
		{
			cout << endl << endl << " This supplyer has no bikes." << endl << endl;
			system("pause");
			return MENU_mngr_supplyers;
		}

		cout << endl;
		for (unsigned int i = 0; i < bicis.size(); i++)
		{
			cout << bicis[i]->imprime() << endl;
		}
		cout << endl;
		system("pause");
		return MENU_mngr_supplyers;
	}


	return MENU_manager;
}

/**
\brief Management menu for bikes
Allows the system manager to perform CRUD operation on Bicicleta objects. It also allows the listing of all available and broken bikes,
as well as rented bikes. It's based on the principle that \b all bikes must be assigned to an Empresa object
*/
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

	int option, id;
	get_option(option, 0, 7);
	vector<Bicicleta *> bikes, bikes_dispo, bikes_avariadas;
	bool imprimiu, apagou;
	string nome;

	switch (option)
	{
	// List all bikes on registered companies
	case 1:	
		imprimiu = false;
		for (unsigned int i = 0; i < empresas.size(); i++)
		{
			bikes = empresas[i].getBicicletas();
			for (unsigned int i = 0; i < bikes.size(); i++)
			{
				if (!imprimiu)
				{
					imprimiu = true;
					cout << endl << "===> List of all bikes" << endl << endl;
				}
				cout << bikes[i]->imprime() << endl;
			}
		}

		if (!imprimiu)
		{
			cout << endl << "There are no bikes in the network, registered by supplying companies";
		}
		cout << endl << endl;
		system("pause");
		return MENU_mngr_bikes;
	// List all available bikes
	case 2:
		for (unsigned int i = 0; i < postos.size(); i++)
		{
			bikes = postos[i]->getDisponiveis();
			bikes_dispo.insert(bikes_dispo.end(), bikes.begin(), bikes.end());
		}

		if (bikes_dispo.size() == 0)
			cout << endl << " There are no bikes available.";
		else
		{
			cout << endl << "===> List of available bikes." << endl << endl;
			for (unsigned int i = 0; i < bikes_dispo.size(); i++)
			{
				cout << bikes_dispo[i]->imprime() << endl;
			}
		}
		cout << endl << endl;
		system("pause");
		return MENU_mngr_bikes;
	// List all broken bikes
	case 3:
		for (unsigned int i = 0; i < postos.size(); i++)
		{
			bikes = postos[i]->getAvariadas();
			bikes_avariadas.insert(bikes_avariadas.end(), bikes.begin(), bikes.end());
		}

		if (bikes_avariadas.size() == 0)
			cout << endl << " There are no broken bikes.";
		else
		{
			cout << endl << "===> List of broken bikes." << endl << endl;
			for (unsigned int i = 0; i < bikes_avariadas.size(); i++)
			{
				cout << bikes_avariadas[i]->imprime() << endl;
			}
		}
		cout << endl << endl;
		system("pause");
		return MENU_mngr_bikes;
	// List currently rented bikes
	case 4:
		clear_screen();
		print_menu_header();
		
		if (rented_bikes.size() == 0)
			cout << endl << " There are no bikes rented by occasional users." << endl << endl;
		else
		{
			cout << endl << "===> Bikes currently rented by occasional users :" << endl << endl;
			for (unsigned int i = 0; i < rented_bikes.size(); i++)
			{
				cout << rented_bikes[i]->imprime() << endl;
			}
		}

		if (rented_bikes_freq.size() == 0)
			cout << endl << " There are no bikes rented by registered users." << endl << endl;
		else
		{
			cout << endl << "===> Bikes currently rented by registered users :" << endl << endl;
			for (unsigned int i = 0; i < rented_bikes_freq.size(); i++)
			{
				cout << rented_bikes_freq[i]->imprime() << endl;
			}
		}

		cout << endl;
		system("pause");
		return MENU_mngr_bikes;
	// Repair all bikes
	case 5:
		for (unsigned int i = 0; i < postos.size(); i++)
			postos[i]->arranja_bicicletas();

		cout << endl << " All bikes were repaired." << endl << endl;
		system("pause");
		return MENU_mngr_bikes;
	// Create a new bike
	case 6:
		create_add_bike();
		cout << endl << endl;
		system("pause");
		return MENU_mngr_bikes;
	// Remove a bike
	case 7:
		cout << endl << " Please insert bike ID : ";
		id = readInt();

		nome = is_busy(id, true);

		if (nome.size() != 0)
		{
			cout << endl << endl;
			system("pause");
			return MENU_mngr_bikes;
		}

		apagou = false;
		for (unsigned int i = 0; i < empresas.size(); i++)
		{
			bikes = empresas[i].getBicicletas();
			for (unsigned int j = 0; j < bikes.size(); j++)
			{
				if (bikes[j]->getID() == id)
				{
					apagou = true;
					empresas[i].remove_bicis(id);
				}
			}
		}

		if (!apagou)
		{
			cout << endl << " There is no bike with that id, registered by a supplying company." << endl << endl;
			system("pause");
			return MENU_mngr_bikes;
		}

		for (unsigned int i = 0; i < utilizadores.size(); i++)
		{
			utilizadores[i]->remove_bici(id);
		}

		for (unsigned int i = 0; i < postos.size(); i++)
		{
			postos[i]->removebicicleta(id);
		}

		cout << endl << " Bike successfully removed" << endl << endl;
		system("pause");
		return MENU_mngr_bikes;
	}

	return MENU_manager;
}

/**
\brief Management menu for rental logs.
Allows the system manager to view information about the Bike-sharing network in a easy way. Some of the lists are:

"Time a user has rented a bike"
"Money to charge a user"
"Number of users served by a company"
"Ongoing rentals"
"Most frequent service user"
*/
int Rede::menu_mngr_logs()
{
	print_menu_header();

	cout << endl << endl << "===> Please select an option:" << endl;
	cout << " 1 - Show the time a user has rented a bike" << endl;
	cout << " 2 - Show money to charge a user" << endl;
	cout << " 3 - Show number of users served by a company" << endl;
	cout << " 4 - Show ongoing rentals" << endl;
	cout << " 5 - Show most frequent service user" << endl;
	cout << " 0 - Return to the previous menu" << endl;

	int option, soma, max;
	get_option(option, 0, 5);
	string name;
	Registo *reg_ptr;
	vector<Registo *> regs;
	vector<Utilizador*> users;
	vector<Bicicleta*> bici;

	switch (option)
	{
	// Show the time a user has rented a bike
	case 1:
		cout << " Enter the name of the user : ";
		getline(cin, name);

		for (unsigned int i = 0; i < utilizadores.size(); i++)
		{
			if (utilizadores[i]->getNome() == name)
			{
				soma = utilizadores[i]->tempo_aluguer();
				if (soma == 0)
				{
					cout << " This user has never rented a bike" << endl << endl;
					system("pause");
					return MENU_mngr_logs;
				}

				cout << " This user has rented a bike for " << soma << " day(s)" << endl << endl;
				system("pause");
				return MENU_mngr_logs;
			}
		}


		cout << " There is no user with that name" << endl << endl;
		system("pause");
		return MENU_mngr_logs;
	// Show money to charge a user
	case 2:
		cout << " Enter the name of the user : ";
		getline(cin, name);

		for (unsigned int i = 0; i < utilizadores.size(); i++)
		{
			if (utilizadores[i]->getNome() == name)
			{
				cout << " The service cost for all registered users is 40 euros" << endl << endl;
				system("pause");
				return MENU_mngr_logs;
			}
		}

		cout << " There is no user with that name" << endl << endl;
		system("pause");
		return MENU_mngr_logs;
	// Show number of users served by a company
	case 3:
		cout << " Enter the name of the company : ";
		getline(cin, name);

		for (unsigned int i = 0; i < empresas.size(); i++)
		{
			if (empresas[i].getNome() == name)
			{
				soma = empresas[i].num_users();
				cout << endl << " This company has served " << soma << " user(s)" << endl << endl;
				system("pause");
				return MENU_mngr_logs;
			}
		}

		cout << " There is no company with that name" << endl << endl;
		system("pause");
		return MENU_mngr_logs;
	//Show ongoing rentals
	case 4:
		clear_screen();
		print_menu_header();
		cout << endl;
		if (curr_rentals.size() == 0)
			cout << " There are no current rentals from occasional users." << endl << endl;
		else
		{
			cout << "===> Rentals from occasional users : " << endl << endl;
			for (unsigned int i = 0; i < curr_rentals.size(); i++)
			{
				curr_rentals[i]->print_reg();
				cout << endl;
			}
		}
		
		for (unsigned int i = 0; i < utilizadores.size(); i++)
		{
			reg_ptr = utilizadores[i]->ultimoReg();
			if ((reg_ptr != NULL) && (reg_ptr->ID_posto_chegada == 0))
			{
				regs.push_back(reg_ptr);
			}
		}

		if (regs.size() == 0)
			cout << " There are no current rentals from registered users." << endl << endl;
		else
		{
			cout << "===> Rentals from registered users : " << endl << endl;
			for (unsigned int i = 0; i < regs.size(); i++)
			{
				regs[i]->print_reg();
				cout << endl;
			}
		}

		cout << endl;
		system("pause");
		return MENU_mngr_logs;
	// Show most frequent service user
	case 5:
		if (utilizadores.size() == 0)
			cout << " There are no registered users. This log is impossible to calculate." << endl << endl;
		else
		{
			max = 0;
			for (unsigned int i = 0; i < utilizadores.size(); i++)
			{
				soma = utilizadores[i]->num_aluguer();
				if (soma >= max)
				{
					name = utilizadores[i]->getNome();
					max = soma;
				}
			}

			cout << " The most frequent service user is " << name << endl << endl;
		}

		system("pause");
		return MENU_mngr_logs;
	}

	return MENU_manager;
}

/**
\brief Management menu for service posts
Allows the system manager to perform CRUD operations on PostoServico objects, as well as repair one or more bikes in one or all of those objects,
and listing of the bikes in a service post
*/
int Rede::menu_mngr_spots()
{
	print_menu_header();

	cout << endl << endl << "===> Please select an option:" << endl;
	cout << " 1 - Show all service posts" << endl;
	cout << " 2 - Add a new service post" << endl;
	cout << " 3 - Edit a service post" << endl;
	cout << " 4 - Delete a service post" << endl;
	cout << " 5 - Repair a specific bike" << endl;
	cout << " 6 - Repair all bikes in a service post" << endl;
	cout << " 7 - List all bikes for a service post" << endl;
	cout << " 0 - Return to the previous menu" << endl;

	int option, id, lotacao, index, id_bici;
	get_option(option, 0, 7);
	PostoServico posto, *posto_ptr;
	vector<Bicicleta *> bicis, bicis2;
	bool result;


	switch (option)
	{
	// Show all service posts
	case 1:
		if (postos.size() == 0)
		{
			cout << endl << " There are no service posts." << endl << endl;
			system("pause");
			return MENU_mngr_spots;
		}

		cout << endl << "===> List of service posts : " << endl << endl;
		for (unsigned int i = 0; i < postos.size(); i++)
		{
			cout << " -> " << postos[i]->getID() << " : " << postos[i]->getOcupacao() << "/" << postos[i]->getLotacao() << " bike slots taken" << endl;
		}
		cout << endl;
		system("pause");
		return MENU_mngr_spots;
	// Create new service post
	case 2:
		cout << endl << " Enter new post ID : ";
		id = readInt();

		for (unsigned int i = 0; i < postos.size(); i++)
		{
			if (postos[i]->getID() == id)
			{
				cout << endl << " There already is a post with that ID." << endl << endl;
				system("pause");
				return MENU_mngr_spots;
			}
		}

		cout << endl << " Enter new post capacity : ";
		lotacao = readInt();

		posto = PostoServico(id, 0, lotacao);
		posto_ptr = new PostoServico;
		*posto_ptr = posto;
		postos.push_back(posto_ptr);
		cout << endl << " Service post added" << endl << endl;
		system("pause");
		return MENU_mngr_spots;
	// Edit a service post
	case 3:
		cout << endl << " Enter post ID : ";
		id = readInt();
		index = -1;

		for (unsigned int i = 0; i < postos.size(); i++)
		{
			if (postos[i]->getID() == id)
			{
				index = i;
				break;
			}
		}

		if (index == -1)
		{
			cout << endl << " There is no post with that id." << endl << endl;
			system("pause");
			return MENU_mngr_spots;
		}

		cout << " Post occupation : " << postos[index]->getOcupacao() << "/" << postos[index]->getLotacao() << " bike slots taken" << endl << endl;
		cout << " Insert new post id : ";
		id = readInt();

		for (unsigned int i = 0; i < postos.size(); i++)
		{
			if ((postos[i]->getID() == id) && (i != index))
			{
				cout << endl << " There already is a post with that ID." << endl << endl;
				system("pause");
				return MENU_mngr_spots;
			}
		}

		cout << endl << " Insert new post capacity : ";
		lotacao = readInt();

		if (lotacao < postos[index]->getOcupacao())
		{
			cout << endl << endl << " New capacity can't be less than current occupation. No changes were made." << endl << endl;
			system("pause");
			return MENU_mngr_spots;
		}

		postos[index]->setID(id);
		postos[index]->setLotacao(lotacao);

		cout << endl << endl << " Service post successfully edited" << endl << endl;
		system("pause");
		return MENU_mngr_spots;
	// Delete a service post
	case 4:
		cout << endl << " Enter post ID : ";
		id = readInt();
		index = -1;

		for (unsigned int i = 0; i < postos.size(); i++)
		{
			if (postos[i]->getID() == id)
			{
				index = i;
				break;
			}
		}

		if (index == -1)
		{
			cout << endl << " There is no post with that id." << endl << endl;
			system("pause");
			return MENU_mngr_spots;
		}

		bicis = postos[index]->getDisponiveis();
		bicis2 = postos[index]->getAvariadas();
		bicis.insert(bicis.end(), bicis2.begin(), bicis2.end());

		for (unsigned int i = 0; i < bicis.size(); i++)
		{
			for (unsigned int i = 0; i < utilizadores.size(); i++)
				utilizadores[i]->remove_bici(id);

			for (unsigned int j = 0; j < empresas.size(); j++)
				empresas[j].remove_bicis(bicis[i]->getID());
		}

		postos.erase(postos.begin() + index);

		cout << endl << " Service post deleted" << endl << endl;
		system("pause");
		return MENU_mngr_spots;
	// Repair a specific bike
	case 5:
		cout << endl << " Enter post ID : ";
		id = readInt();
		index = -1;

		for (unsigned int i = 0; i < postos.size(); i++)
		{
			if (postos[i]->getID() == id)
			{
				index = i;
				break;
			}
		}

		if (index == -1)
		{
			cout << endl << " There is no post with that id." << endl << endl;
			system("pause");
			return MENU_mngr_spots;
		}

		cout << endl << " Enter bike ID : ";
		id_bici = readInt();

		result = postos[index]->arranja_bicicleta(id_bici);
		
		if (!result)
			cout << endl << " There is no bike with that ID in this post." << endl << endl;
		else
			cout << endl << " Bike repaired." << endl << endl;

		system("pause");
		return MENU_mngr_spots;
	// Repair all bikes in a service post
	case 6:
		cout << endl << " Enter post ID : ";
		id = readInt();

		for (unsigned int i = 0; i < postos.size(); i++)
		{
			if (postos[i]->getID() == id)
			{
				postos[i]->arranja_bicicletas();
				cout << endl << endl << " All bikes were repaired in post " << id << endl << endl;
				system("pause");
				return MENU_mngr_spots;
			}
		}

		cout << endl << " There is no post with that id." << endl << endl;
		system("pause");
		return MENU_mngr_spots;
	// List all bikes in a post
	case 7:
		cout << endl << " Enter post ID : ";
		id = readInt();
		index = -1;

		for (unsigned int i = 0; i < postos.size(); i++)
		{
			if (postos[i]->getID() == id)
			{
				index = i;
				break;
			}
		}

		if (index == -1)
		{
			cout << endl << " There is no post with that id." << endl << endl;
			system("pause");
			return MENU_mngr_spots;
		}

		bicis = postos[index]->getDisponiveis();
		bicis2 = postos[index]->getAvariadas();

		if ((bicis.size() == 0) && (bicis2.size() == 0))
		{
			cout << endl << " This post has no bikes." << endl << endl;
			system("pause");
			return MENU_mngr_spots;
		}

		clear_screen();
		print_menu_header();

		if (bicis.size() == 0)
			cout << endl << " There are no available bikes in this post";
		else
		{
			cout << endl << "===> List of available bikes in this post" << endl << endl;
			for (unsigned int i = 0; i < bicis.size(); i++)
				cout << " -> " << bicis[i]->imprime() << endl;
		}

		if (bicis2.size() == 0)
			cout << endl << " There are no broken bikes in this post";
		else
		{
			cout << endl << "===> List of broken bikes in this post" << endl << endl;
			for (unsigned int i = 0; i < bicis2.size(); i++)
				cout << " -> " << bicis2[i]->imprime() << endl;
		}

		cout << endl << endl;
		system("pause");
		return MENU_mngr_spots;
	}



	return MENU_manager;
}
//////////////////////////////////////////////////////////////////////////////// CHECKED ^^
/**
\brief Management menu for users
Allows the system manager to perform CRUD operations on Utilizador objects
*/
int Rede::menu_mngr_users()
{
	print_menu_header();

	cout << endl << endl << "===> Please select an option:" << endl;
	cout << " 1 - List all users" << endl;
	cout << " 2 - Create a new user" << endl;
	cout << " 3 - Edit existing user" << endl;
	cout << " 4 - Delete user" << endl;
	//cout << " 5 - List old users (inactive for over " << USER_MONTHS_LIMIT << " months)" << endl;
	//cout << " 6 - Update old users list" << endl;
	cout << " 0 - Return to previous menu" << endl;

	int option, index, idade, numero;
	get_option(option, 0, 6);
	string nome, pass, morada;
	Registo *reg_ptr;
	vector<Bicicleta *> bikes;

	hashUtilizador::iterator it;

	switch (option)
	{
	// List all registered users
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
	// Create new registered user
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
	// Edit a registered user
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

		cout << endl << " Current user address : " << utilizadores[index]->getMorada();
		cout << endl << " New user address : ";
		getline(cin, morada);
		utilizadores[index]->setMorada(morada);

		cout << " Current user contact : " << utilizadores[index]->getContacto();
		cout << endl << " New user contact : ";
		while (true)
		{
			numero = readInt();
			if ((numero <= 0) || (numero > 999999999))
			{
				cout << endl << "ERROR : Invalid contact. Try again." << endl << " New user contact : ";
				continue;
			}
			break;
		}
		utilizadores[index]->setContacto(numero);

		cout << endl << " User successfully edited." << endl << endl;
		system("pause");
		return MENU_mngr_users;
	// Delete a registered user
	case 4:
		cout << endl << " Enter name of user to delete : ";
		getline(cin, nome);

		for (index = 0; index < utilizadores.size(); index++)
		{
			if (utilizadores[index]->getNome() == nome)
				break;
		}

		if (index == utilizadores.size())
		{
			cout << endl << " There is no registered user with that name." << endl << endl;
			system("pause");
			return MENU_mngr_users;
		}

		reg_ptr = utilizadores[index]->ultimoReg();

		if (reg_ptr == NULL)
		{
			utilizadores.erase(utilizadores.begin() + index);
			cout << endl << " User deleted successfully." << endl << endl;
			system("pause");
			return MENU_mngr_users;
		}
		else if (reg_ptr->ID_posto_chegada != 0)
		{
			for (unsigned int i = 0; i < postos.size(); i++)
				postos[i]->removeutilizador(utilizadores[index]->getNome());
			for (unsigned int i = 0; i < rented_bikes_freq.size(); i++)
				rented_bikes_freq[i]->remove_util(utilizadores[index]->getNome());
			utilizadores.erase(utilizadores.begin() + index);

			cout << endl << " User deleted successfully." << endl << endl;
			system("pause");
			return MENU_mngr_users;
		}
		else
		{
			cout << endl << " This user is currently renting a bike." << endl <<
				" Which post should the bike go to?" << endl << endl;
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
				return MENU_mngr_users;
			}

			for (unsigned int i = 0; i < rented_bikes_freq.size(); i++)
			{
				if (rented_bikes_freq[i]->getID() == reg_ptr->ID_Bicicleta)
				{
					postos[option]->adicionabicicleta(rented_bikes_freq[i]);
					rented_bikes_freq.erase(rented_bikes_freq.begin() + i);

				}
			}
			for (unsigned int i = 0; i < postos.size(); i++)
				postos[i]->removeutilizador(utilizadores[index]->getNome());
			for (unsigned int i = 0; i < rented_bikes_freq.size(); i++)
				rented_bikes_freq[i]->remove_util(utilizadores[index]->getNome());
			it = util_antigos.find(*utilizadores[index]);
			if (it != util_antigos.end())
				util_antigos.erase(it);
			utilizadores.erase(utilizadores.begin() + index);

			cout << endl << " User deleted successfully." << endl << endl;
			system("pause");
			return MENU_mngr_users;
		}
		break;
	}

	return MENU_manager;
}