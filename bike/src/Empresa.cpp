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

void Empresa::setBicicletas(vector<Bicicleta*> bicicletas)
{
	this->bicicletas = bicicletas;
}

void Empresa::remove_bicis(unsigned int id)
{
	vector<Bicicleta *> result = getBicicletas();

	if (result.size() == 0)
		return;

	vector<Bicicleta *>::const_iterator it = result.begin();

	while (it != result.end())
	{
		if (id == (*it)->getID())
		{
			result.erase(it);
			//it--;
			break;
		}
		it++;
	}

	setBicicletas(result);
	return;
}

int Empresa::num_users() const
{
	vector<Registo *> regs;
	vector<string> nomes;

	for (unsigned int i = 0; i < bicicletas.size(); i++)
	{
		regs = bicicletas[i]->getRegsBicis();
		for (unsigned int j = 0; j < regs.size(); j++)
		{
			int result = sequentialSearch(nomes, regs[j]->nome_utilizador);
			if (result == -1)
				nomes.push_back(regs[j]->nome_utilizador);
		}
	}

	return nomes.size();
}