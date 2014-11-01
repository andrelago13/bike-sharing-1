#include <iostream>
#include <vector>
#include <string>

#include "Registo.h"
#include "Utilizador.h"

using namespace std;

void Utilizador::setNome(string nome)
{
	this->nome = nome;
}

void Utilizador::setIdade(int idade)
{
	this->idade = idade;
}

string Utilizador::getNome() const {return nome;}

int Utilizador::getIdade() const {return idade;}

vector<Registo *> Utilizador::getRegs() const {return registos;}

void Utilizador::setRegs(vector<Registo *> regs)
{
	registos = regs;
}

Registo Utilizador::ultimoReg() const
{
	int pos = registos.size() - 1;

	return *registos[pos];
}
