#include "PostoServico.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

PostoServico::PostoServico()		// Cria um posto de serviço por defeito
{
}

PostoServico::PostoServico(int iD, int ocupacao, int lotacao)		// Cria um posto de serviço que aceita parâmetros id, ocupação e lotação
{
	this->iD = iD;
	this->lotacao = lotacao;
	this->ocupacao = ocupacao;
}

int PostoServico::getID() const		// função retorna o id do posto de serviço
{
	return iD;
}

int PostoServico::getLotacao() const		// função retorna a lotação do posto de serviço
{
	return lotacao;
}

int PostoServico::getOcupacao() const		// função retorna a ocupação do posto de serviço
{
	return ocupacao;
}

int PostoServico::getEspacoLivre() const		// função retorna o espaço livre do posto de serviço
{
	return (PostoServico::getLotacao() - PostoServico::getOcupacao());
}

vector<Bicicleta*> PostoServico::getDisponiveis()			// função retorna as bicicletas disponiveis do posto de serviço
{
	return disponiveis;
}

vector<Bicicleta*> PostoServico::getAvariadas()			// função retorna as bicicletas avariadas do posto de serviço
{
	return avariadas;
}

vector<Registo*> PostoServico::getUtlizacao()		// função retorna um vetor com os registos de todas as bicicletas
{
	return utilizacao;
}

void PostoServico::setID(int id)		// função modifica o id de um posto de serviço
{
	iD = id;
}

void PostoServico::setLotacao(int lot)			// funçao modifica a lotação de um posto de serviço
{
	lotacao = lot;
}

void PostoServico::setDisponiveis(vector<Bicicleta*> disponiveis)		// função modifica as bicicletas disponiveis pelo vetor de bicicletas passado como parametro na função atualizando a ocupação do posto
{
		this ->disponiveis = disponiveis;
		ocupacao = disponiveis.size() + avariadas.size();		
}

void PostoServico::setAvariadas(vector<Bicicleta*> avariadas)		// função modifica as bicicletas avariadas pelo vetor de bicicletas passado como parametro na função atualizando a ocupação do posto
{
		this->avariadas = avariadas;			
		ocupacao = disponiveis.size() + avariadas.size();
}

void PostoServico::setUtilizacao(vector<Registo*> utilizacao)		// função modifica o vetor de registos pelo que é passado como parametro da função
{
	this->utilizacao = utilizacao;
}

void PostoServico::adicionabicicleta(Bicicleta *bi1)		// função adiciona uma nova bicicleta ao posto de serviço. Se estiver avariada é guardada nas avariadas caso contrario fica nas disponiveis sendo que em ambos os casos a ocupação do posto é atualizada

{
	if (bi1->getAvariada())
		avariadas.push_back(bi1);
	else
		disponiveis.push_back(bi1);

	ocupacao++;
}

void PostoServico::adicionaDisponivel(Bicicleta *bi1)		// função adiciona uma nova bicicleta ás disponiveis atualizando a ocupação do posto
{
	disponiveis.push_back(bi1);
	ocupacao++;
}

void PostoServico::adicionaAvariada(Bicicleta *bi1)			// função adiciona uma nova bicicleta ás avariadas atualizando a ocupação do posto
{
	avariadas.push_back(bi1);
	ocupacao++;
}

void PostoServico::adicionaUtilizacao(Registo *reg1)		// função adiciona um novo registo ao vetor de registos
{
	utilizacao.push_back(reg1);
}

bool PostoServico::aluga(Bicicleta *bi1)			// O utilizador aluga uma das bicicletas disponiveis no posto de serviço
{																	
	vector<Bicicleta*> dispo = PostoServico::getDisponiveis();

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

bool PostoServico::devolve(Bicicleta *bi1)				// o utilizador devolve a bicicleta alugada ao posto de serviço
{
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

bool PostoServico::removebicicleta(unsigned int id_bike)	// remove bicicleta do vetor utilizacao
{
	vector<Registo*> utils = PostoServico::getUtlizacao();		
	vector<Bicicleta*> dispon = PostoServico::getDisponiveis();		
	vector<Bicicleta*> avariad = PostoServico::getAvariadas();		

	for (unsigned int i = 0; i < utils.size(); i++)			// apaga do registo a bicicleta segundo o id dado
	{
		if (utils[i]->ID_Bicicleta == id_bike)
		{
			utils.erase(utils.begin() + i);
		}
	}
	setUtilizacao(utils);

	for (unsigned int i = 0; i < dispon.size(); i++)			// apaga das disponiveis a bicicleta segundo um id dado
	{
		if (dispon[i]->getID() == id_bike)
		{
			dispon.erase(dispon.begin() + i);
			setDisponiveis(dispon);
			ocupacao--;
			return true;
		}
	}

	for (unsigned int i = 0; i < avariad.size(); i++)			// se não encontrar nas disponiveis, procura nas avariadas e apaga
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
		return false;


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

void PostoServico::arranja_bicicletas()				// arranja as bicicletas avariadas e coloca as nas disponiveis apagando as mesmas das avariadas
{
	for (unsigned int i = 0; i < avariadas.size(); i++)
	{
		disponiveis.push_back(avariadas[i]);
		avariadas.erase(avariadas.begin());
	}
}

bool PostoServico::arranja_bicicleta(int id_bike)		// arranja uma bicicleta em especifico (segundo um id) e coloca a nas disponiveis apagando a mesma das avariadas
{
	for (unsigned int i = 0; i < avariadas.size(); i++)
	{
		if (avariadas[i]->getID == id_bike)
		{
			disponiveis.push_back(avariadas[i]);
			avariadas.erase(avariadas.begin() + i);
			return true;
		}
	}

	return false;
}
