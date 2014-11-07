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

Registo* Utilizador::ultimoReg() const
{
	if (registos.size() == 0)
		return NULL;

	int pos = registos.size() - 1;

	return registos[pos];
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
	return 2;
}

int Utilizador::tempo_aluguer()
{
	int soma = 0;

	if ((registos.size() == 0) || ((registos.size() == 1) && (registos[registos.size() - 1]->ID_posto_chegada == 0)))
		return 0;

	for (unsigned int j = 0; j < registos.size(); j++)
	{
		if (registos[j]->ID_posto_chegada != 0)
			soma += dif_dias(registos[j]->levantamento, registos[j]->entrega) + 1;
	}
	
	return soma;
}

int Utilizador::num_aluguer()
{
	if (registos.size() == 0)
		return 0;
	else if (registos[registos.size() - 1]->ID_posto_chegada == 0)
		return registos.size() - 1;

	return registos.size();
}