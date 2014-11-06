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
protected:
	string nome;
	string password;
	unsigned int idade;
	vector <Registo*> registos;
	int tipo; // 0 se frequente, 1 se ocasional
public:
	Utilizador() : nome(""), password(""), idade(0), tipo(0) {}
	Utilizador(string name, int age) : nome(name), idade(age), password(""), tipo(0) {}
	Utilizador(string name, int age, string pass) : nome(name), idade(age), password(pass), tipo(0) {}
	void setNome(string nome);
	void setIdade(int idade);
	string getNome() const;
	int getIdade() const;
	vector <Registo *> getRegs() const;
	void setRegs(vector <Registo *> regs);
	Registo* ultimoReg() const;
	string getPassword() const { return password; }
	void setPassword(string pass) { password = pass; }
	bool operator==(string name);
	bool operator==(Utilizador user);
	void operator=(Utilizador user);
	int getTipo() { return tipo; }
	virtual int getCusto();
	void adicionaRegisto(Registo *reg) { registos.push_back(reg); }
	int tempo_aluguer();

	friend ostream& operator<<(ostream &o, Utilizador &user);

};

class Ut_ocasional : public Utilizador
{
	string cartao;

public:
	Ut_ocasional();
	Ut_ocasional(string name, int age, string pass, string novo_cartao);
	string get_cartao() { return cartao; }
	void set_cartao(string novo) { cartao = novo; }
	int getCusto();
};


#endif /* UTILIZADOR_H_ */
