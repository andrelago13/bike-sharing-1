#include <iostream>
#include <vector>
#include <string>
#include "PostoServico.h"
#include "Bicicleta.h"


using namespace std;
#define veloc_max = 6;

Bicicleta::Bicicleta(unsigned int id, string tipo_bici, int mudancas) : id_num(id), tipo(tipo_bici), velocidades(mudancas)
{
}

int Bicicleta::getID()
{
	return id_num;
}

int Bicicleta::getVelocidades()
{
	return velocidades;
}

string Bicicleta::getTipo()
{
	return tipo;
}

string Bicicleta::getEmpresa()
{
	return empresa;
}

bool Bicicleta::getAvariada()
{
	return avariada;
}

bool Bicicleta::velocidades_valido(int veloc)
{
	if (veloc == velocidades)
		return true;
	return false;
}

bool Bicicleta::tipo_valido()
{
	if (tipo == "eletrica" || tipo == "com cesto" || tipo == "sem cesto" || tipo == "passeio" || tipo == "corrida" || tipo == "montanha")
		return true;
	return false;
}

void Bicicleta::setPreco(int preco)
{
	this->preco = preco;
}

string Bicicleta::imprime() {
	stringstream ss;
	ss << id_num << ", " << tipo << ", " << velocidades;
	return ss.str();
}

void Bicicleta::setID()
{
	int idnew = bicicletas.size() - 1;
	id_num = idnew++;
}

void Bicicleta::setTipo(string tipo)
{
	this->tipo = tipo;
}

void Bicicleta::setBicis(vector<Registo *> bicis)
{
	bicicletas = bicis;
}

vector<Registo *> Bicicleta::getBicis() const { return bicicletas; }