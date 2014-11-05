#include <iostream>
#include <vector>
#include <string>
#include "PostoServico.h"
#include "Bicicleta.h"


using namespace std;
#define veloc_max 5

Bicicleta::Bicicleta(unsigned int id, string tipo_bici, string size, int mudancas, bool avariad, unsigned int preco1) : id_num(id), tipo(tipo_bici), tamanho(size), velocidades(mudancas), avariada(avariad), preco(preco1)
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

string Bicicleta::getTamanho()
{
	return tamanho;
}

string Bicicleta::getEmpresa()
{
	return empresa;
}

string Bicicleta::getAvariada()
{
	if (avariada)
		return "AVARIADA";
	else return "NAO AVARIADA";
}

int Bicicleta::getPreco()
{
	return preco;
}
bool Bicicleta::velocidades_valido(int veloc)
{
	if (veloc == velocidades)
		return true;
	return false;
}

string Bicicleta::tipo_valido()
{
	if (tipo == "eletrica" || tipo == "com cesto" || tipo == "sem cesto" || tipo == "passeio" || tipo == "corrida" || tipo == "montanha")
		return "ESSE TIPO E VALIDO";
	return "ESSE TIPO NAO E VALIDO";
}

bool Bicicleta::setPrecoDia(int velocidade, string tamanho) //verificar velocidades das bicicletas -> corrida 1 velocidade x
{
	if ((velocidades > veloc_max) || (velocidades == 0))
		return false; //velocidades invalidades

	//cout do tamanho
	if (tamanho == "adulto")
	{
		switch (velocidades)
		{
		case 1:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 90;
			if (tipo == "corrida")
				preco = 150;
			if (tipo == "com cesto")
				preco = 50;
			if (tipo == "sem cesto")
				preco = 40;
			return true;
		case 2:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 125;
			if (tipo == "corrida")
				preco = 190;
			if (tipo == "com cesto")
				preco = 90;
			if (tipo == "sem cesto")
				preco = 80;
			return true;
		case 3:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 170;
			if (tipo == "corrida")
				preco = 230;
			if (tipo == "com cesto")
				preco = 130;
			if (tipo == "sem cesto")
				preco = 120;
			return true;
		case 4:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 210;
			if (tipo == "corrida")
				preco = 270;
			if (tipo == "com cesto")
				preco = 170;
			if (tipo == "sem cesto")
				preco = 160;
			return true;
		case 5:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 250;
			if (tipo == "corrida")
				preco = 310;
			if (tipo == "com cesto")
				preco = 210;
			if (tipo == "sem cesto")
				preco = 200;
			return true;
		}
	}
	else if (tamanho == "crianca")
	{
		switch (velocidades)
		{
		case 1:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 50;
			if (tipo == "corrida")
				preco = 90;
			if (tipo == "com cesto")
				preco = 20;
			if (tipo == "sem cesto")
				preco = 10;
			return true;
		case 2:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 80;
			if (tipo == "corrida")
				preco = 120;
			if (tipo == "com cesto")
				preco = 50;
			if (tipo == "sem cesto")
				preco = 40;
			return true;
		case 3:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 110;
			if (tipo == "corrida")
				preco = 150;
			if (tipo == "com cesto")
				preco = 80;
			if (tipo == "sem cesto")
				preco = 70;
			return true;
		case 4:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 140;
			if (tipo == "corrida")
				preco = 180;
			if (tipo == "com cesto")
				preco = 110;
			if (tipo == "sem cesto")
				preco = 100;
			return true;
		case 5:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 170;
			if (tipo == "corrida")
				preco = 210;
			if (tipo == "com cesto")
				preco = 150;
			if (tipo == "sem cesto")
				preco = 140;
			return true;
		}
		return false;
	}
}

string Bicicleta::imprime()
{
	stringstream ss;
	ss << id_num << ", " << tipo << ", " << tamanho << ", " << velocidades << ", " << avariada << ", " << preco;
	return ss.str();
}

void Bicicleta::setID(int ID)
{
	/*int ID= bicicletas.size() - 1;
	id_num = ID++;*/
	this->id_num = ID;
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

void Bicicleta::setTamanho(string tamanho)
{
	this->tamanho = tamanho;
}

void Bicicleta::setVeloc(int velocidades)
{
	this->velocidades = velocidades;
}