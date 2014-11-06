#ifndef EMPRESA_H_
#define EMPRESA_H_

#include <iostream>
#include <vector>
#include <string>
#include "Bicicleta.h"
#include "Registo.h"

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
	void remove_bicis(unsigned int id)
};

#endif /* EMPRESA_H_ */


//set bicicletas com um vetor de apontadores OK