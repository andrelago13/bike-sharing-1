/*
* Empresa.cpp
*
*  Created on: 02/11/2014
*      Author: leonardo
*/
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
			Bicicleta::imprime();
			cout << endl;
		}
		it++;
	}
}

vector<Bicicleta*> Empresa::setBicicletas(vector<Bicicleta*> bicicletas)
{
	this->bicicletas = bicicletas;
}