/*
 * Utilizador.h
 *
 *  Created on: 31/10/2014
 *      Author: edgar
 */
#ifndef UTILIZADOR_H_
#define UTILIZADOR_H_

#include <iostream>
#include <vector>
#include <string>

#include "Registo.h"

using namespace std;

class Utilizador
{
	string nome;
	unsigned int idade;
	vector <Registo*> registos;
public:
	Utilizador();
	Utilizador(string name, int age) : nome(name), idade(age) {}
	void setNome(string nome);
	void setIdade(int idade);
	string getNome() const;
	int getIdade() const;
	vector <Registo *> getRegs() const;
	void setRegs(vector <Registo *> regs);
	Registo ultimoReg() const;
};
 //FREQUENTES E OCASIONAIS


#endif /* UTILIZADOR_H_ */
