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
	int num_users() const;
	vector<Bicicleta *> getBicicletas() const;
	void adicionaBicicleta(Bicicleta *bic);
	void setBicicletas(const vector<Bicicleta*> bicicletas);
	void remove_bicis(unsigned int id);
	void show_specs();
	void setNome(string novo_nome);
};

#endif /* EMPRESA_H_ */
