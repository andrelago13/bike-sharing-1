#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "PostoServico.h"
#include "Bicicleta.h"
#include "Tools.h"


using namespace std;
#define veloc_max 5

/*!
\brief Default constructor of Bike
It initializes the bike as being bike 0,"sem cesto", "adulto", 1, false, 40
*/
Bicicleta::Bicicleta()
{
	id_num = 0;
	tipo = "sem cesto";
	tamanho = "adulto";
	velocidades = 1;
	avariada = false;
	preco = 40;
}

/**
* \brief Creates a bike
* \param id - Name given to the new the bike
* \param tipo_bici - the type of the bike
* \param size - what size is the bike for
* \param mudanças - the number of shifts of the bike
* \param avariad - if the bike is broken or not
* \param preco1 - the price of the bike
* Creates bike with a new id,  new tipo_bici, new size, new mudancas, new avariad and new preco1
*/
Bicicleta::Bicicleta(unsigned int id, string tipo_bici, string size, int mudancas, bool avariad, unsigned int preco1) : id_num(id), tipo(tipo_bici), tamanho(size), velocidades(mudancas), avariada(avariad), preco(preco1)
{
}

/**
* \brief gets the bike's id
* \returns the id of the bike
* Let us get the id of the bike
*/
int Bicicleta::getID() //função retorna o id caracteristico da bicicleta
{
	return id_num;
}

/**
* \brief gets the bike's shifts
* \returns the shifts of the bike
* Let us get the shifts of the bike
*/
int Bicicleta::getVelocidades() //função retorna as velocidades da bicicleta
{
	return velocidades;
}

/**
* \brief gets the bike's type
* \returns the type of the bike
* Let us get the type of the bike
*/
string Bicicleta::getTipo() //função retorna o tipo da bicicleta(que pode ser eletrica, com ou sem cesto, passeio, montanha ou de corrida)
{
	return tipo;
}

/**
* \brief gets the bike's size
* \returns the size of the bike
* Let us get the size of the bike
*/
string Bicicleta::getTamanho() //função retorna o tamanho da bicicleta(adulto ou criança)
{
	return tamanho;
}

/**
* \brief gets the bike's company
* \returns the company of the bike
* Let us get the company of the bike
*/
string Bicicleta::getEmpresa() //função retorna a empresa onde a bicicleta esta registada
{
	return empresa;
}

/**
* \brief gets the bike's state of damage
* \returns the damage of the bike
* Let us get the damage of the bike
*/
bool Bicicleta::getAvariada() //função retorna se a bicicleta está avariada
{
	return avariada;
}

/**
* \brief Sets the bike as avariada (damaged)
* Sets the bike as damaged (avariada)
*/
void Bicicleta::setAvariada() //função põe avariada como verdadeiro 
{
	avariada = true;
}

/**
* \brief Gets the bike's price
* \returns the price of the bike
* Let us get the price of the bike
*/
int Bicicleta::getPreco() //função retorna o preço da bicicleta
{
	return preco;
}

/**
* \brief add a rental record to the vector of regists
* \param *reg1 - the rental record we want to put on the vector of regists (rental records)
* Add a rental record to the vector we have of rental records
*/
void Bicicleta::adicionaRegisto(Registo *reg1) //função adiciona um registo ao vetor de registos das bicicletas
{
	regs.push_back(reg1);
}

/**
* \brief Shifts are valid
* \param veloc - shift to compare with
* \return true if shift is valid, false if it isn't
* We check if the shift we want to give to the bike is valid or not
*/
bool Bicicleta::velocidades_valido(int veloc) //funçao retorna verdadeiro se as velocidades foram válidas ou falso se nao o foram
{
	if (veloc == velocidades)
		return true;
	return false;
}

/**
* \brief Type is valid
* \return a string saying if the type is valid or not
* We learn if the type we want to give to the bike is valid or not
*/
string Bicicleta::tipo_valido() //função retorna se o tipo é válido ou não 
{
	if (tipo == "eletrica" || tipo == "com cesto" || tipo == "sem cesto" || tipo == "passeio" || tipo == "corrida" || tipo == "montanha")
		return "ESSE TIPO E VALIDO";
	return "ESSE TIPO NAO E VALIDO";
}

/**
* \brief Sets a the price of the bike per day
* \param velocidade - the shifts the bike has
* \param tamanho - the size of the bike
* Sets the price of the bike, with that specs, for a day 
*/
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

/**
* \brief Print a bike
* \returns a string with the specs of the bike
* Prints a bike with the specs we previously had given to it
*/
string Bicicleta::imprime() //função que imprime os dados de uma determinada bicicleta
{
	stringstream ss;
	ss << "ID- " << id_num << ", " << tipo << ", " << tamanho << ", " << velocidades << " velocidade(s), " << avariada << ", " << preco << " euros ";
	return ss.str();
}

/**
* \brief Sets the id to the bike
* \param id - the id we want to give to the bike
* Sets the id we want to give to the bike
*/
void Bicicleta::setID(int id) //função que coloca o id a um certo valor(sem devolver nada)
{
	/*int ID= bicicletas.size() - 1;
	id_num = ID++;*/
	this->id_num = id;
}

/**
* \brief Sets the bike's type
* \param tipo - the type we want to give to the bike
* Sets the type we want to give to the bike
*/
void Bicicleta::setTipo(string tipo) //função que coloca bicicleta com um tipo específico(sem devolver nada)
{
	this->tipo = tipo;
}

/**
* \brief Sets the rental record
* \param bicis - the rental record we want to load to the vector
* Sets the rental record we want to the vector of rental records
*/
void Bicicleta::setRegsBicis(vector<Registo *> bicis) //função que coloca um vetor de registos de uma bicicleta, ou varias, no vetor original existente na classe(sem devolver nada)
{
	regs = bicis;
}

/**
* \brief Gets the rental record
* \returns a vector with the rental records of the vector 
* Gets the rental record of the vector of rental records
*/
vector<Registo *> Bicicleta::getRegsBicis() const { return regs; } //vetor que devolve o vetor de registos das bicicletas existente na classe

/**
* \brief Sets a new size to the bike
* \param tamanho - New size to be implemented
* Sets a new size to the bike
*/
void Bicicleta::setTamanho(string tamanho) //função que coloca o tamanho a um certo valor(sem devolver nada)
{
	this->tamanho = tamanho;
}

/**
* \brief Sets a new shift to the bike
* \param velocidades - New shift to be implemented
* Sets a new shift to the bike
*/
void Bicicleta::setVeloc(int velocidades) //função que coloca as velocidades a um certo valor(sem devolver nada)
{
	this->velocidades = velocidades;
}

/**
* \brief Removes the user with the name nome
* \param nome - Name of the user we want to delete
* \returns true if the name is removed sucessfully and false if it doesn't
* Removes the user with the name nome of the vector of registrations
*/
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

/*!
\brief Get string that represents the bike
This function is used in Rede::storeInfo(), because it converts the bike object to a multiple line string containing all of it's information
except the rental logs
\return string representing bike info
*/
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

/*!
\brief Make a bike from a string that represents it
\param bike - string with a bike
This function is used in Rede::loadInfo(), because it makes a bike object from a multiple line string that contains all it's information
except for the rental logs
*/
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

/**
* \brief Show the last of the rental records
* \returns a pointer to a rental record with the last of the rental records
* Show the last of the rental records
*/
Registo* Bicicleta::ultimo_reg() const
{
	Registo *ptr;
	if (regs.size() == 0)
		return NULL;
	ptr = regs[regs.size() - 1];
	return ptr;
}

int Bicicleta::getUtilizacaoTempoUso() const
{
	int tempo_uso = 0;

	if (regs.size() == 0)
		return tempo_uso;

	else
	{
		if (!avariada)
		{
			for (unsigned int i = regs.size() - 1; i >= 0; i--)
			{
				if (regs[i]->ficou_avariada)
					break;

				tempo_uso += dif_dias(regs[i]->entrega, regs[i]->levantamento) + 1;
			}
			return tempo_uso;
		}
		else
		{
			tempo_uso += dif_dias(regs[regs.size()-1]->entrega, regs[regs.size()-1]->levantamento) + 1;
			for (int i = regs.size() - 2; i >= 0; i--)
			{
				if (regs[i]->ficou_avariada)
					break;

				tempo_uso += dif_dias(regs[i]->entrega, regs[i]->levantamento) + 1;
			}
			return tempo_uso;
		}
	}
}

bool operator <(const Bicicleta bi1, const Bicicleta bi2)
{
	return (bi1.getUtilizacaoTempoUso() < bi2.getUtilizacaoTempoUso());
}