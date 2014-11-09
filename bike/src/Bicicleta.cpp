#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "PostoServico.h"
#include "Bicicleta.h"
#include "Tools.h"


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

int Bicicleta::getID() //função retorna o id caracteristico da bicicleta
{
	return id_num;
}

int Bicicleta::getVelocidades() //função retorna as velocidades da bicicleta
{
	return velocidades;
}

string Bicicleta::getTipo() //função retorna o tipo da bicicleta(que pode ser eletrica, com ou sem cesto, passeio, montanha ou de corrida)
{
	return tipo;
}

string Bicicleta::getTamanho() //função retorna o tamanho da bicicleta(adulto ou criança)
{
	return tamanho;
}

string Bicicleta::getEmpresa() //função retorna a empresa onde a bicicleta esta registada
{
	return empresa;
}

bool Bicicleta::getAvariada() //função retorna se a bicicleta está avariada
{
	return avariada;
}

void Bicicleta::setAvariada() //função põe avariada como verdadeiro 
{
	avariada = true;
}

int Bicicleta::getPreco() //função retorna o preço da bicicleta
{
	return preco;
}

void Bicicleta::adicionaRegisto(Registo *reg1) //função adiciona um registo ao vetor de registos das bicicletas
{
	regs.push_back(reg1);
}

bool Bicicleta::velocidades_valido(int veloc) //funçao retorna verdadeiro se as velocidades foram válidas ou falso se nao o foram
{
	if (veloc == velocidades)
		return true;
	return false;
}

string Bicicleta::tipo_valido() //função retorna se o tipo é válido ou não 
{
	if (tipo == "eletrica" || tipo == "com cesto" || tipo == "sem cesto" || tipo == "passeio" || tipo == "corrida" || tipo == "montanha")
		return "ESSE TIPO E VALIDO";
	return "ESSE TIPO NAO E VALIDO";
}

void Bicicleta::setPrecoDia(int velocidade, string tamanho) //função coloca o preço das bicicletas por dia a um certo valor mediante tamanho e velocidades
{
	if ((velocidade > veloc_max) || (velocidade == 0))
	{
		cout << "Velocidade invalida! " << endl << "Preco(anterior->por defeito): "; //velocidades invalidades
		return;
	}
	
	//cout do tamanho
	if (tamanho == "adulto")
	{
		switch (velocidade) //as várias opções para as velocidades
		{
		case 1:
			if (tipo == "eletrica" || tipo == "montanha") //preços mediantes os tipos das bicicletas
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

string Bicicleta::imprime() //função que imprime os dados de uma determinada bicicleta
{
	stringstream ss;
	ss << "ID- " << id_num << ", " << tipo << ", " << tamanho << ", " << velocidades << " velocidade(s), " << avariada << ", " << preco << " euros ";
	return ss.str();
}

void Bicicleta::setID(int id) //função que coloca o id a um certo valor(sem devolver nada)
{
	/*int ID= bicicletas.size() - 1;
	id_num = ID++;*/
	this->id_num = id;
}

void Bicicleta::setTipo(string tipo) //função que coloca bicicleta com um tipo específico(sem devolver nada)
{
	this->tipo = tipo;
}

void Bicicleta::setRegsBicis(vector<Registo *> bicis) //função que coloca um vetor de registos de uma bicicleta, ou varias, no vetor original existente na classe(sem devolver nada)
{
	regs = bicis;
}

vector<Registo *> Bicicleta::getRegsBicis() const { return regs; } //vetor que devolve o vetor de registos das bicicletas existente na classe

void Bicicleta::setTamanho(string tamanho) //função que coloca o tamanho a um certo valor(sem devolver nada)
{
	this->tamanho = tamanho;
}

void Bicicleta::setVeloc(int velocidades) //função que coloca as velocidades a um certo valor(sem devolver nada)
{
	this->velocidades = velocidades;
}

bool Bicicleta::remove_util(string nome) //função que remove um utilizador do vetor de registos das bicicletas
{
	vector<Registo *> result = getRegsBicis(); //vetor resultado para o qual se carrega o vetor de registos das bicicletas

	if (result.size() == 0) //se vetor estiver vazio o utilizador ja foi "removido"
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

	setRegsBicis(result); //colocar o vetor resultado como o vetor de registos, agora sem o utilizador
	return true;
}

string Bicicleta::get_str() const
{
	stringstream ss;
	ss << id_num << endl << tipo << endl << tamanho << endl << velocidades << endl
		<< preco << endl << empresa << endl;
	if (avariada)
		ss << "1" << endl;
	else
		ss << "0" << endl;

	return ss.str();
}

void Bicicleta::make_str(string bike)
{
	stringstream ss(bike);
	string temp;

	getline(ss, temp);
	id_num = str_to_int(temp);
	getline(ss, temp);
	tipo = temp;
	getline(ss, temp);
	tamanho = temp;
	getline(ss, temp);
	velocidades = str_to_int(temp);
	getline(ss, temp);
	preco = str_to_int(temp);
	getline(ss, temp);
	empresa = temp;
	getline(ss, temp);
	if (temp == "1")
		avariada = true;
	else
		avariada = false;
}

Registo* Bicicleta::ultimo_reg() const
{
	return regs[regs.size() - 1];
}