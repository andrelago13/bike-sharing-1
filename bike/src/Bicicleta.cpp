#include <iostream>
#include <vector>
#include <string>
#include "PostoServico.h"
#include "Bicicleta.h"


using namespace std;
#define veloc_max 5

Bicicleta::Bicicleta()
{
	id_num = 0;
	tipo = "sem cesto";
	tamanho = "adulto";
	velocidades = 1;
	avariada = false;
	preco = 40;
}

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

bool Bicicleta::getAvariada()
{
	return avariada;
}

void Bicicleta::setAvariada()
{
	avariada = true;
}

int Bicicleta::getPreco()
{
	return preco;
}

void Bicicleta::adicionaRegisto(Registo *reg1)
{
	regs.push_back(reg1);
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

void Bicicleta::setPrecoDia(int velocidade, string tamanho) //verificar velocidades das bicicletas -> corrida 1 velocidade x
{
	if ((velocidade > veloc_max) || (velocidade == 0))
	{
		cout << "Velocidade invalida! " << endl << "Preco(anterior->por defeito): "; //velocidades invalidades
		return;
	}
	
	//cout do tamanho
	if (tamanho == "adulto")
	{
		switch (velocidade)
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
			cout << "Preco ajustado! " << endl << "Preco:" ;
			return;
		case 2:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 125;
			if (tipo == "corrida")
				preco = 190;
			if (tipo == "com cesto")
				preco = 90;
			if (tipo == "sem cesto")
				preco = 80;
			cout << "Preco ajustado! " << endl << "Preco:";
			return;
		case 3:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 170;
			if (tipo == "corrida")
				preco = 230;
			if (tipo == "com cesto")
				preco = 130;
			if (tipo == "sem cesto")
				preco = 120;
			cout << "Preco ajustado! " << endl << "Preco:";
			return;
		case 4:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 210;
			if (tipo == "corrida")
				preco = 270;
			if (tipo == "com cesto")
				preco = 170;
			if (tipo == "sem cesto")
				preco = 160;
			cout << "Preco ajustado! " << endl << "Preco:";
			return;
		case 5:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 250;
			if (tipo == "corrida")
				preco = 310;
			if (tipo == "com cesto")
				preco = 210;
			if (tipo == "sem cesto")
				preco = 200;
			cout << "Preco ajustado! " << endl << "Preco:";
			return;
		}
	}
	else if (tamanho == "crianca")
	{
		switch (velocidade)
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
			cout << "Preco ajustado! " << endl << "Preco:";
			return;
		case 2:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 80;
			if (tipo == "corrida")
				preco = 120;
			if (tipo == "com cesto")
				preco = 50;
			if (tipo == "sem cesto")
				preco = 40;
			cout << "Preco ajustado! " << endl << "Preco:";
			return;
		case 3:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 110;
			if (tipo == "corrida")
				preco = 150;
			if (tipo == "com cesto")
				preco = 80;
			if (tipo == "sem cesto")
				preco = 70;
			cout << "Preco ajustado! " << endl << "Preco:";
			return;
		case 4:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 140;
			if (tipo == "corrida")
				preco = 180;
			if (tipo == "com cesto")
				preco = 110;
			if (tipo == "sem cesto")
				preco = 100;
			cout << "Preco ajustado! " << endl << "Preco:";
			return;
		case 5:
			if (tipo == "eletrica" || tipo == "montanha")
				preco = 170;
			if (tipo == "corrida")
				preco = 210;
			if (tipo == "com cesto")
				preco = 150;
			if (tipo == "sem cesto")
				preco = 140;
			cout << "Preco ajustado! " << endl << "Preco:";
			return;
		}
		cout << "Parametros nao validos! " << endl;
		return;
	}
}

string Bicicleta::imprime()
{
	stringstream ss;
	ss << "ID- " << id_num << ", " << tipo << ", " << tamanho << ", " << velocidades << " velocidades, " << avariada << ", " << preco << " € ";
	return ss.str();
}

void Bicicleta::setID(int id)
{
	/*int ID= bicicletas.size() - 1;
	id_num = ID++;*/
	this->id_num = id;
}

void Bicicleta::setTipo(string tipo)
{
	this->tipo = tipo;
}

void Bicicleta::setRegsBicis(vector<Registo *> bicis)
{
	regs = bicis;
}

vector<Registo *> Bicicleta::getRegsBicis() const { return regs; }

void Bicicleta::setTamanho(string tamanho)
{
	this->tamanho = tamanho;
}

void Bicicleta::setVeloc(int velocidades)
{
	this->velocidades = velocidades;
}

bool Bicicleta::remove_util(string nome)
{
	vector<Registo *> result = getRegsBicis();

	if (result.size() == 0)
		return true;
	
	vector<Registo *>::const_iterator it = result.begin(); 
	
	while (it!= result.end())
	{
		if (nome == (*it)->nome_utilizador)
		{
			result.erase(it);
			it--;
		}		
		it++;
	}

	setRegsBicis(result);
	return true;
}