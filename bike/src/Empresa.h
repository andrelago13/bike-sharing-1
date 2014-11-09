#ifndef EMPRESA_H_
#define EMPRESA_H_

#include <iostream>
#include <vector>
#include <string>
#include "Bicicleta.h"
#include "Registo.h"

using namespace std;

/*! \class Rede
\brief Rede - Auxiliary program class

This class functions as a bridge that connects PostoServico to Rede and is very important in many ways
*/

class Empresa
{
private:
	string nome;
	vector<Bicicleta*> bicicletas;
public:
	// Basic Functions
	Empresa();
	Empresa(string nome);
	string getNome() const;
	vector<Bicicleta *> getBicicletas() const;
	void adicionaBicicleta(Bicicleta *bic);
	void setBicicletas(const vector<Bicicleta*> bicicletas);
	void setNome(string novo_nome);
	void remove_bicis(unsigned int id);
	void show_specs();
	int num_users() const;
};

#endif /* EMPRESA_H_ */
