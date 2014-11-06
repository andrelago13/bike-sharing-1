#include <iostream>
#include <vector>
#include <string>
#include"Empresa.h"

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
		if (id == (*it)->getID)
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