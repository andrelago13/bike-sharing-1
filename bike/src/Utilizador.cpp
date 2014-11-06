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

bool Utilizador::operator==(string name)
{
	if (nome == name)
		return true;
	return false;
}

bool Utilizador::operator==(Utilizador user)
{
	if (nome == user.nome)
		return true;
	return false;
}

void Utilizador::operator=(Utilizador user)
{
	nome = user.nome;
	idade = user.idade;
	password = user.password;

	vector<Registo*> regs2 = user.getRegs();

	for (unsigned int i = 0; i < regs2.size(); i++)
	{
		Registo *ptr;
		ptr = new(Registo);
		*ptr = *regs2[i];
		registos.push_back(ptr);
	}
}

ostream& operator<<(ostream &o, Utilizador &user)
{
	o << user.nome << " - " << user.idade << " y/o";
	return o;
}

Ut_ocasional::Ut_ocasional() : Utilizador(), cartao("") {}

Ut_ocasional::Ut_ocasional(string name, int age, string pass, string novo_cartao) : Utilizador(name, age, pass), cartao(novo_cartao) {}

int Utilizador::getCusto()
{
	return 40;
}

int Ut_ocasional::getCusto()
{
	if (idade < 18)
		return 1;

	return 2;
}
