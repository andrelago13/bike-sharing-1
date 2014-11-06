#include <iostream>
#include <vector>
#include <string>
#include "Empresa.h"
#include "Tools.h"

using namespace std;

Empresa::Empresa()
{
}

Empresa::Empresa(string nome)
{
	this->nome = nome;
}

string Empresa::getNome() const
{
	return nome;
}

vector<Bicicleta *> Empresa::getBicicletas() const
{
	return bicicletas;
}

void Empresa::adicionaBicicleta(Bicicleta *bic)
{
	bicicletas.push_back(bic);
}

void Empresa::show_specs()		//Imprime as especificações da empresa, ou seja, mostra o seu nome e de seguida todas as bicicletas da mesma
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

void Empresa::setBicicletas(vector<Bicicleta*> bicicletas)
{
	this->bicicletas = bicicletas;
}

void Empresa::remove_bicis(unsigned int id)			// remove uma bicicleta da empresa de acordo com o id
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
			it--;
			break;
		}
		it++;
	}

	setBicicletas(bikes);
	return;
}

int Empresa::num_users() const		// devolve o numero de utilizadores registados na empresa sem estarem repetidos
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