/*
* PostoServico.cpp
*
*  Created on: 05/11/2014
*      Author: leonardo
*/
#include "PostoServico.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

PostoServico::PostoServico()
{
}

PostoServico::PostoServico(int iD, int ocupacao, int lotacao)
{
	this->iD = iD;
	this->lotacao = lotacao;
	this->ocupacao = ocupacao;
}

int PostoServico::getID() const
{
	return iD;
}

int PostoServico::getLotacao() const
{
	return lotacao;
}

int PostoServico::getOcupacao() const
{
	return ocupacao;
}

int PostoServico::getEspacoLivre() const
{
	return (PostoServico::getLotacao() - PostoServico::getOcupacao());
}

vector<Bicicleta*> PostoServico::getDisponiveis()
{
	return disponiveis;
}

vector<Bicicleta*> PostoServico::getAvariadas()
{
	return avariadas;
}

vector<Registo*> PostoServico::getUtlizacao()
{
	return utilizacao;
}

void PostoServico::setDisponiveis(vector<Bicicleta*> disponiveis)
{
		this ->disponiveis = disponiveis;
		ocupacao = disponiveis.size() + avariadas.size();		
}

void PostoServico::setAvariadas(vector<Bicicleta*> avariadas)
{
		this->avariadas = avariadas;			
		ocupacao = disponiveis.size() + avariadas.size();
}

void PostoServico::setUtilizacao(vector<Registo*> utilizacao)
{
	this->utilizacao = utilizacao;
}

void PostoServico::adicionabicicleta(Bicicleta *bi1)

{
	if (bi1->getAvariada())
		avariadas.push_back(bi1);
	else
		disponiveis.push_back(bi1);

	ocupacao++;
}

void PostoServico::adicionaDisponivel(Bicicleta *bi1)
{
	disponiveis.push_back(bi1);
	ocupacao++;
}

void PostoServico::adicionaAvariada(Bicicleta *bi1)
{
	avariadas.push_back(bi1);
	ocupacao++;
}

void PostoServico::adicionaUtilizacao(Registo *reg1)
{
	utilizacao.push_back(reg1);
}

bool PostoServico::aluga(Bicicleta *bi1)		// O utilizador aluga uma das bicicletas disponiveis no posto de serviço
{																	
	vector<Bicicleta*> dispo = PostoServico::getDisponiveis();
	//int ocupacao = PostoServico::getOcupacao();

	if (dispo.size() == 0)
	{
		cout << "There are no bikes available!!!" << endl;
		return false;
	}
	else
	{
		vector<Bicicleta*>::iterator it = dispo.begin();
		// Percorre o vetor dispo e verifica se existe alguma bicicleta com as mesmas caracteristicas da bicicleta passada como parametro na função
		while (it != dispo.end())
		{
			if ((*it) == bi1)
			{
				dispo.erase(it);
				setDisponiveis(dispo);
				ocupacao--;
				return true;
			}
			it++;
		}
	}
}

bool PostoServico::devolve(Bicicleta *bi1)		// O utilizador devolve a bicicleta alugada ao posto de serviço
{
	//int ocupacao = PostoServico::getOcupacao();

	if (bi1->getAvariada())
	{
		avariadas.push_back(bi1);
		ocupacao++;
		return false;
	}
	else
	{
		disponiveis.push_back(bi1);
		ocupacao++;
	}
	return true;
}

bool PostoServico::removebicicleta(unsigned int id_bike)	//remove bicicleta do vetor utilizacao(vetor que contem os registos do posto de serviço)
{
	vector<Registo*> utils = PostoServico::getUtlizacao();		// apaga do registo a bicicleta segundo o id dado
	vector<Registo*>::iterator it = utils.begin();

	vector<Bicicleta*> dispon = PostoServico::getDisponiveis();		// apaga das disponiveis a bicicleta segundo um id dado
	vector<Bicicleta*>::iterator ot = dispon.begin();

	vector<Bicicleta*> avariad = PostoServico::getAvariadas();		// se não encontrar nas disponiveis, procura nas avariadas e apaga
	vector<Bicicleta*>::iterator ut = avariad.begin();

	for (unsigned int i = 0; i < utils.size(); i++)
	{
		if (utils[i]->ID_Bicicleta == id_bike)
		{
			utils.erase(utils.begin() + i);
		}
	}
	setUtilizacao(utils);

	for (unsigned int i = 0; i < dispon.size(); i++)
	{
		if (dispon[i]->getID() == id_bike)
		{
			dispon.erase(dispon.begin() + i);
			setDisponiveis(dispon);
			ocupacao--;
			return true;
		}
	}

	for (unsigned int i = 0; i < avariad.size(); i++)
	{
		if (avariad[i]->getID() == id_bike)
		{
			avariad.erase(avariad.begin() + i);
			setAvariadas(avariad);
			ocupacao--;
			return true;
		}
	}
	return false;
}

bool PostoServico::removeutilizador(string user)		//remove utilizador do posto de serviço 
{
	vector<Registo*>::iterator it = utilizacao.begin();

	if (utilizacao.size() == 0)
	{
		//cout << "No registers available" << endl;
		return false;
	}

	while (it != utilizacao.end())
	{
		if ((*it)->nome_utilizador == user)
		{
			utilizacao.erase(it);
			it--;
		}
		it++;
	}

	for (unsigned int i = 0; i < disponiveis.size(); i++)
		disponiveis[i]->remove_util(user);
	for (unsigned int i = 0; i < avariadas.size(); i++)
		avariadas[i]->remove_util(user);

	return true;
}

void PostoServico::arranja_bicicletas()
{
	for (unsigned int i = 0; i < avariadas.size(); i++)
	{
		disponiveis.push_back(avariadas[i]);
		avariadas.erase(avariadas.begin());
	}
}