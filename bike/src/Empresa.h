#ifndef EMPRESA_H_
#define EMPRESA_H_

#include <iostream>
#include <vector>
#include <string>
#include "Bicicleta.h"
#include "Registo.h"

using namespace std;

/*! \class Empresa
\brief Empresa - Auxiliary program class

This class functions as a bridge that connects PostoServico to Rede and is very important in many ways
*/
class Empresa
{
private:
	string nome;
	string morada;
	vector<Bicicleta*> bicicletas;
public:
	// Basic Functions
	Empresa();
	Empresa(string nome, string addr);
	string getNome() const;
	vector<Bicicleta *> getBicicletas() const;
	void adicionaBicicleta(Bicicleta *bic);
	void setBicicletas(const vector<Bicicleta*> bicicletas);
	void setNome(string novo_nome);
	void remove_bicis(unsigned int id);
	void show_specs();
	void setMorada(string addr) { morada = addr; }
	string getMorada() const { return morada; }
	int num_users() const;
	int numUtilsBicis() const;
	bool operator<(const Empresa &emp2) const;
	bool operator==(const Empresa &emp2) const;
};

#endif /* EMPRESA_H_ */
