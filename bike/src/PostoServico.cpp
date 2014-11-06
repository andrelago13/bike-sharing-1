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

PostoServico::PostoServico(int ID, int ocupacao, int lotacao)
{
	this->ID = ID;
	this->lotacao = lotacao;
	this->ocupacao = ocupacao;
}

int PostoServico::getID() const
{
	return ID;
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

void PostoServico::setPreencheOcup(int lug)
{
	ocupacao = (PostoServico::getDisponiveis()).size() + (PostoServico::getAvariadas()).size() - lug;
}

void PostoServico::setLibertaOcup(int lug)
{
	ocupacao = (PostoServico::getDisponiveis()).size() + (PostoServico::getAvariadas()).size() + lug;
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
	this->disponiveis = disponiveis;
}

void PostoServico::setAvariadas(vector<Bicicleta*> avariadas)
{
	this->avariadas = avariadas;
}

void PostoServico::setUtilizacao(vector<Registo*> utilizacao)
{
	this->utilizacao = utilizacao;
}

void PostoServico::adicionabicicleta(Bicicleta *bi1)

{
	if (bi1->getAvariada())
	{
		avariadas.push_back(bi1);
		setPreencheOcup(1);
	}
	else
		disponiveis.push_back(bi1);
		setPreencheOcup(1);

}

void PostoServico::adicionaDisponivel(Bicicleta *bi1)
{
	disponiveis.push_back(bi1);
}

void PostoServico::adicionaAvariada(Bicicleta *bi1)
{
	avariadas.push_back(bi1);
}

void PostoServico::adicionaUtilizacao(Registo *reg1)
{
	utilizacao.push_back(reg1);
}

bool PostoServico::aluga(Bicicleta *bi1)		// O utilizador aluga uma das bicicletas disponiveis no posto de serviço
{																	
	vector<Bicicleta*> dispo = PostoServico::getDisponiveis();
	int ocupacao = PostoServico::getOcupacao();

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
				setLibertaOcup(1);
				return true;
			}
			it++;
		}
	}
}

bool PostoServico::devolve(Bicicleta *bi1)		// O utilizador devolve a bicicleta alugada ao posto de serviço
{
	int ocupacao = PostoServico::getOcupacao();

	if (bi1->getAvariada())
	{
		avariadas.push_back(bi1);
		setPreencheOcup(1);
		return false;
	}
	else
	{
		disponiveis.push_back(bi1);
		setPreencheOcup(1);
	}
	return true;
}

bool PostoServico::removebicicleta(unsigned int id_bike)	//remove bicicleta do vetor utilizacao(vetor que contem os registos do posto de serviço)
{
	vector<Registo*> utils = PostoServico::getUtlizacao();
	vector<Registo*>::iterator it = utils.begin();

	if (utils.size() == 0)
	{
		cout << "No registers available" << endl;
		return false;
	}

		while (it != utils.end())
		{
			if ((*it)->ID_Bicicleta == id_bike)
			{
				utils.erase(it);
				it--;
				return true;
			}
			it++;
		}
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