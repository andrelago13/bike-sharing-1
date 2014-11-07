#include <iostream>
#include <vector>
#include <string>

#include "Registo.h"
#include "Utilizador.h"

using namespace std;

void Utilizador::setNome(string nome) //fun�ao que coloca o nome do utilizador igual a nome
{
	this->nome = nome;
}

void Utilizador::setIdade(int idade) //fun�ao que coloca a idade do utilizador igual a idade
{
	this->idade = idade;
}

string Utilizador::getNome() const {return nome;} //fun�ao que retorna o nome do utilizador

int Utilizador::getIdade() const {return idade;} //fun�ao que retorna a idade do utilizador

vector<Registo *> Utilizador::getRegs() const {return registos;} //fun�ao que retorna o vetor de registos dos utilizadores

void Utilizador::setRegs(vector<Registo *> regs) //fun�ao que coloca o vetor de registos dos utilizadores igual a regs
{
	registos = regs;
}

Registo* Utilizador::ultimoReg() const //fun�ao que retorna o ultimo registo dos utilizadores(do vetor registos)
{
	if (registos.size() == 0)
		return NULL;

	int pos = registos.size() - 1;

	return registos[pos];
}

bool Utilizador::operator==(string name) //fun�ao que redefine a express�o de compara��o "==" para comparar nomes
{
	if (nome == name)
		return true;
	return false;
}

bool Utilizador::operator==(Utilizador user) //fun�ao que redefine a express�o de compara��o "==" para comparar utilizadores(os seus nomes)
{
	if (nome == user.nome)
		return true;
	return false;
}

void Utilizador::operator=(Utilizador user) //fun�ao que redefine a express�o de igualdade "="
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

ostream& operator<<(ostream &o, Utilizador &user) //fun�ao que redefine a express�o "<<" para que mostre nome de utilizador seguido de "-" e idade
{
	o << user.nome << " - " << user.idade << " y/o";
	return o;
}

Ut_ocasional::Ut_ocasional() : Utilizador(), cartao("") {} //construtor por defeito para utilizador ocasional

Ut_ocasional::Ut_ocasional(string name, int age, string pass, string novo_cartao) : Utilizador(name, age, pass), cartao(novo_cartao) {} //construtor de utilizador ocasional com todos os parametros caracter�sticos de utilizador adicionando o cart�o (de cr�dito)

int Utilizador::getCusto() //fun��o que retorna o custo do dia de utiliza��o das bicicletas -> utilizador normal/freq
{
	return 40;
}

int Ut_ocasional::getCusto() //fun��o que retorna o custo do dia de utiliza��o das bicicletas -> utilizador ocasional
{
	return 2;
}

int Utilizador::tempo_aluguer() //fun��o que determina o tempo de aluguer (em dias) da bicicleta em quest�o
{
	int soma = 0;

	if ((registos.size() == 0) || ((registos.size() == 1) && (registos[registos.size() - 1]->ID_posto_chegada == 0)))
		return 0;

	for (unsigned int j = 0; j < registos.size(); j++)
	{
		if (registos[j]->ID_posto_chegada != 0)
			soma += dif_dias(registos[j]->levantamento, registos[j]->entrega) + 1; //dif_dias --> calcula a diferen�a entre o dia de entrega e do de levantamento
	}
	
	return soma;
}

int Utilizador::num_aluguer() //fun��o que retorna o n� de alugueres existentes at� � data
{
	if (registos.size() == 0)
		return 0;
	else if (registos[registos.size() - 1]->ID_posto_chegada == 0)
		return registos.size() - 1;

	return registos.size();
}