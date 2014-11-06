/*
* Empresa.h
*
*  Created on: 02/11/2014
*      Author: leonardo
*/

#ifndef EMPRESA_H_
#define EMPRESA_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Empresa
{
private:
	string nome;
	vector<Bicicleta*> bicicletas;
public:
	Empresa();
	Empresa(string nome);
	string getNome() const;
	vector<Bicicleta *> getBicicletas() const;
	void adicionaBicicleta(Bicicleta *bic);
	void show_specs();
	void setBicicletas(const vector<Bicicleta*> bicicletas);
};

#endif /* EMPRESA_H_ */


//set bicicletas com um vetor de apontadores OK