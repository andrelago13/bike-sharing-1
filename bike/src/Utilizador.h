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
	string password;
	unsigned int idade;
	vector <Registo*> registos;
public:
	Utilizador() : nome(""), password(""), idade(0) {}
	Utilizador(string name, int age) : nome(name), idade(age), password("") {}
	Utilizador(string name, int age, string pass) : nome(name), idade(age), password(pass) {}
	void setNome(string nome);
	void setIdade(int idade);
	string getNome() const;
	int getIdade() const;
	vector <Registo *> getRegs() const;
	void setRegs(vector <Registo *> regs);
	Registo ultimoReg() const;
	string getPassword() const { return password; }
	void setPassword(string pass) { password = pass; }
	bool operator==(string name);
	bool operator==(Utilizador user);
	void operator=(Utilizador user);

};
 //FREQUENTES E OCASIONAIS


#endif /* UTILIZADOR_H_ */
