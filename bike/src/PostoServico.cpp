#include "PostoServico.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

PostoServico::PostoServico()		// Cria um posto de servi�o por defeito
{
}

PostoServico::PostoServico(int iD, int ocupacao, int lotacao)		// Cria um posto de servi�o que aceita par�metros id, ocupa��o e lota��o
{
	this->iD = iD;
	this->lotacao = lotacao;
	this->ocupacao = ocupacao;
}

int PostoServico::getID() const		// fun��o retorna o id do posto de servi�o
{
	return iD;
}

int PostoServico::getLotacao() const		// fun��o retorna a lota��o do posto de servi�o
{
	return lotacao;
}

int PostoServico::getOcupacao() const		// fun��o retorna a ocupa��o do posto de servi�o
{
	return ocupacao;
}

int PostoServico::getEspacoLivre() const		// fun��o retorna o espa�o livre do posto de servi�o
{
	return (PostoServico::getLotacao() - PostoServico::getOcupacao());
}

vector<Bicicleta*> PostoServico::getDisponiveis()			// fun��o retorna as bicicletas disponiveis do posto de servi�o
{
	return disponiveis;
}

vector<Bicicleta*> PostoServico::getAvariadas()			// fun��o retorna as bicicletas avariadas do posto de servi�o
{
	return avariadas;
}

vector<Registo*> PostoServico::getUtlizacao()		// fun��o retorna um vetor com os registos de todas as bicicletas
{
	return utilizacao;
}

void PostoServico::setDisponiveis(vector<Bicicleta*> disponiveis)		// fun��o modifica as bicicletas disponiveis com o vetor de bicicletas passado na fun��o atualizando a ocupa��o do posto de servi�o
{
		this ->disponiveis = disponiveis;
		ocupacao = disponiveis.size() + avariadas.size();		
}

void PostoServico::setAvariadas(vector<Bicicleta*> avariadas)		// fun��o modifica as bicicletas avariadas pelo vetor de bicicletas passado como na fun��o atualizando a ocupa��o do posto de servi�o
{
		this->avariadas = avariadas;			
		ocupacao = disponiveis.size() + avariadas.size();
}

void PostoServico::setUtilizacao(vector<Registo*> utilizacao)		// fun��o modifica o vetor de registos pelo que � passado como parametro da fun��o
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

bool PostoServico::aluga(Bicicleta *bi1)		// O utilizador aluga uma das bicicletas disponiveis no posto de servi�o
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
		// Percorre o vetor dispo e verifica se existe alguma bicicleta com as mesmas caracteristicas da bicicleta passada como parametro na fun��o
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

bool PostoServico::devolve(Bicicleta *bi1)		// O utilizador devolve a bicicleta alugada ao posto de servi�o
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

bool PostoServico::removebicicleta(unsigned int id_bike)	//remove bicicleta do vetor utilizacao(vetor que contem os registos do posto de servi�o)
{
	vector<Registo*> utils = PostoServico::getUtlizacao();		// apaga do registo a bicicleta segundo o id dado
	vector<Registo*>::iterator it = utils.begin();

	vector<Bicicleta*> dispon = PostoServico::getDisponiveis();		// apaga das disponiveis a bicicleta segundo um id dado
	vector<Bicicleta*>::iterator ot = dispon.begin();

	vector<Bicicleta*> avariad = PostoServico::getAvariadas();		// se n�o encontrar nas disponiveis, procura nas avariadas e apaga
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

bool PostoServico::removeutilizador(string user)		//remove utilizador do posto de servi�o 
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

bool PostoServico::arranja_bicicleta(int id_bike)
{
	for (unsigned int i = 0; i < avariadas.size(); i++)
	{
		if (avariadas[i]->getID() == id_bike)
		{
			disponiveis.push_back(avariadas[i]);
			avariadas.erase(avariadas.begin() + i);
			return true;
		}
	}

	return false;
}

void PostoServico::setID(int id)
{
	iD = id;
}

void PostoServico::setLotacao(int lot)
{
	lotacao = lot;
}