#include <iostream>
#include "Registo.h"
#include <string>
#include <sstream>
#include "Tools.h"

using namespace std;

/**
* \brief The status of the rental
* Show the status of the rental for a specified user and the bike he has rented
*/
void Registo::print_reg() const //funçao que permite saber o estado do aluguer da bicicleta e se esta ficou ou nao avariada durante o mesmo
{
	cout << "User : " << nome_utilizador << endl;
	cout << "Bike : " << ID_Bicicleta << endl;
	cout << "Picked up at post " << ID_posto_origem << " em " << levantamento << endl;
	if (ID_posto_chegada == 0)
	{
		cout << "This rental is still ongoing." << endl;
		return;
	}
	cout << "Delivered at post " << ID_posto_chegada << " em " << entrega << endl;
	if (ficou_avariada)
		cout << "The bike got broken during this rental." << endl;
	else
		cout << "The bike did not get damaged during this rental." << endl;
}

/**
* \brief The status of the rental
* Show the status of the rental for an ocasional user and the bike he has rented
*/
void Registo::print_sem_user() const //funçao que permite saber o estado do aluguer da bicicleta e se esta ficou ou nao avariada durante o mesmo tudo isto relativo a um utilizador ocasional(ou seja sem ter de identificar o utilizador)
{
	cout << "Bike : " << ID_Bicicleta << endl;
	cout << "Picked up at post " << ID_posto_origem << " em " << levantamento << endl;
	if (ID_posto_chegada == 0)
	{
		cout << "This rental is still ongoing." << endl;
		return;
	}
	cout << "Delivered at post " << ID_posto_chegada << " em " << entrega << endl;
	if (ficou_avariada)
		cout << "The bike got broken during this rental." << endl;
	else
		cout << "The bike did not get damaged during this rental." << endl;
}

/*!
\brief Default constructor of Registration
It initializes the registration as being 0, 0, 0, ""
*/
Registo::Registo() //construtor por defeito de um registo em que todos os parâmetros estao inicializados com os valores "basicos iniciais" --> 0 nos id e string vazia no nome do utilizador
{
	ID_Bicicleta = 0;
	ID_posto_origem = 0;
	ID_posto_chegada = 0;
	nome_utilizador = "";
}

/*!
\brief Assignment operator overload for Registo
Compares two registrations and see if they are the same (parameters are the same) or not
\param reg1 - first registration
\param reg2 - the second registration
\returns true if the registrations are the same and false if they don't
*/
bool operator==(const Registo reg1, const Registo reg2)
{
	if ((reg1.ID_Bicicleta == reg2.ID_Bicicleta) && (reg1.ID_posto_origem == reg2.ID_posto_origem) && (reg1.ID_posto_chegada == reg2.ID_posto_chegada) && (reg1.nome_utilizador == reg2.nome_utilizador) && (reg1.levantamento.getDataStr() == reg2.levantamento.getDataStr()) && (reg1.entrega.getDataStr() == reg2.entrega.getDataStr()) && (reg1.ficou_avariada == reg2.ficou_avariada))
		return true;
	return false;
}

/*!
\brief Get string that represents the rental record
This function is used in Rede::storeInfo(), because it converts the rental record object to a multiple line string containing all of it's information
except the rental logs
\return string representing rental record info
*/
string Registo::get_str() const
{
	stringstream ss;
	ss << ID_Bicicleta << endl << ID_posto_origem << endl << ID_posto_chegada << endl
		<< nome_utilizador << endl << levantamento.getDataStr() << endl << entrega.getDataStr() << endl;
	if (ficou_avariada)
		ss << "0" << endl;
	else
		ss << "1" << endl;

	string s = ss.str();
	return s;
}

/*!
\brief Get rental record that represents the bike
\param reg - string with a rental record
This function is used in Rede::loadInfo(), because it makes a rental record object from a multiple line string that contains all it's information
*/
void Registo::make_from_str(string reg)
{
	stringstream ss(reg);
	string temp;

	getline(ss, temp);
	ID_Bicicleta = str_to_int(temp);
	getline(ss, temp);
	ID_posto_origem = str_to_int(temp);
	getline(ss, temp);
	ID_posto_chegada = str_to_int(temp);
	getline(ss, temp);
	nome_utilizador = temp;
	getline(ss, temp);
	levantamento = Data(temp);
	getline(ss, temp);
	entrega = Data(temp);
	getline(ss, temp);
	if (temp == "0")
		ficou_avariada = false;
	else
		ficou_avariada = true;
}