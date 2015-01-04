#include <iostream>
#include <vector>
#include <string>
#include "Empresa.h"
#include "Tools.h"

using namespace std;

Empresa::Empresa()
{
}

/**
* \brief Creates a company
* \param nome - Name given to the new company
* Creates a company with the the the name passed as argument
*/

Empresa::Empresa(string nome)
{
	this->nome = nome;
}

/**
* \brief Gets the name of a company
* \returns a string with the company's name
* Let us get the name of a company on a string
*/

string Empresa::getNome() const
{
	return nome;
}

/**
* \brief Gets the company's bikes
* \returns a vector with all the company's bikes
* Let us get a vector of type Bicicleta with all bikes of the company
*/

vector<Bicicleta *> Empresa::getBicicletas() const
{
	return bicicletas;
}

/**
* \brief Adds a bike object to the company
* \param *bic - New bike to be added
* Add a bike to the the company's bikes vector
*/

void Empresa::adicionaBicicleta(Bicicleta *bic)
{
	bicicletas.push_back(bic);
}

/**
* \brief Shows the company's specifications
* Shows all the company's information, the name and all the bikes
*/
void Empresa::show_specs()		
{
	string empresa = Empresa::getNome();
	vector<Bicicleta*> bikes = Empresa::getBicicletas();

	vector<Bicicleta *>::iterator it = bikes.begin();

	cout << "---> Empresa: " << empresa << endl << endl;

	while (it != bikes.end())
	{
		if (bikes.size() == 0)
			cout << "This company has no bikes!!!" << endl;
		else
		{
			(*it)->imprime();
			cout << endl;
		}
		it++;
	}
}

/**
* \brief Sets a new group of bikes on the company
* \param bicicletas - New pack of bicicletas implemented
* Sets a new pack of bicicletas to the company's bikes vector
*/
void Empresa::setBicicletas(vector<Bicicleta*> bicicletas)
{
	this->bicicletas = bicicletas;
}

/**
* \brief Removes a bike(s) of the company
* \param id - identifies the bike(s) to be removed
* Deletes bike(s) from the company's bikes vector through an id
*/
void Empresa::remove_bicis(unsigned int id)			
{
	vector<Bicicleta *> bikes = getBicicletas();

	if (bikes.size() == 0)
		return;

	vector<Bicicleta *>::iterator it = bikes.begin();

	while (it != bikes.end())
	{
		if (id == (*it)->getID())
		{
			bikes.erase(it);
			break;
		}
		it++;
	}

	setBicicletas(bikes);
	return;
}

/**
* \brief Gets the number of users
* \returns the number of users
* Let us get the number of user without repeting users
*/

int Empresa::num_users() const		
{
	vector<Registo *> regs;
	vector<string> nomes;

	for (unsigned int i = 0; i < bicicletas.size(); i++)
	{
		regs = bicicletas[i]->getRegsBicis();
		for (unsigned int j = 0; j < regs.size(); j++)
		{
			bool existe = false;
			for (unsigned int k = 0; k < nomes.size(); k++)
			if (nomes[k] == regs[j]->nome_utilizador)
				existe = true;
			if (existe == false)
				nomes.push_back(regs[j]->nome_utilizador);
		}
	}

	return nomes.size();
}

/**
* \brief Sets a company's name
* \param novo_nome - New name to be implemented
* Sets a new name to the company
*/
void Empresa::setNome(string novo_nome)
{
	nome = novo_nome;
}

bool operator<(const Empresa emp1, const Empresa &emp2)
{
	if (emp1.bicicletas.size() < emp2.bicicletas.size())
		return true;
	else if (emp1.bicicletas.size() > emp2.bicicletas.size())
		return false;
	else
	{
		if (emp1.numUtilsBicis() < emp2.numUtilsBicis())
			return true;
	}

	return false;
}

bool operator==(const Empresa emp1, const Empresa &emp2)
{
	return (emp1.nome == emp2.nome);
}

int Empresa::numUtilsBicis() const
{
	int soma = 0;

	for (int i = 0; i < bicicletas.size(); i++)
	{
		soma += bicicletas[i]->getNumUtils();
	}
	return soma;
}