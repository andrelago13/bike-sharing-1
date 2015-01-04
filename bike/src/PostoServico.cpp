#include "PostoServico.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

PostoServico::PostoServico()		
{
}

/**
* \brief Creates a service spot
* \param iD - Name given to the new the service spot
* \param ocupacao - ocupation of the new service spot
* \param lotacao - include free space and ocupation of the service spot
* Creates a service spot with a new id,  new ocupacao and  new lotacao
*/
PostoServico::PostoServico(int iD, int ocupacao, int lotacao)		// Cria um posto de serviço que aceita parâmetros id, ocupação e lotação
{
	this->iD = iD;
	this->lotacao = lotacao;
	this->ocupacao = ocupacao;
}

/**
* \brief Gets the service spot's id
* \returns the id of the service spot
* Let us get the id of the service spot
*/
int PostoServico::getID() const		// função retorna o id do posto de serviço
{
	return iD;
}

/**
* \brief Gets the service spot's lotacao
* \returns the lotacao of the service spot
* Let us get the lotacao of the service spot
*/
int PostoServico::getLotacao() const		
{
	return lotacao;
}

/**
* \brief Gets the service spot's ocupacao
* \returns the ocupacao of the service spot
* Let us get the ocupacao of the service spot
*/
int PostoServico::getOcupacao() const		
{
	return ocupacao;
}

/**
* \brief Gets the service spot's free space
* \returns the free space of the service spot
* Let us get the free space of the service spot
*/
int PostoServico::getEspacoLivre() const		
{
	return (PostoServico::getLotacao() - PostoServico::getOcupacao());
}

/**
* \brief Gets the service spot's disponiveis bikes
* \returns the disponiveis bikes of the service spot
* Let us get a vector of type Bicicleta with disponiveis bikes of the service spot
*/
vector<Bicicleta*> PostoServico::getDisponiveis()			
{
	return disponiveis;
}

/**
* \brief Gets the service spot's avariadas bikes
* \returns the avariadas bikes of the service spot
* Let us get a vector of type Bicicleta with avariadas bikes of the service spot
*/
vector<Bicicleta*> PostoServico::getAvariadas()			
{
	return avariadas;
}

/**
* \brief Gets the regists of all bikes of service spot
* \returns the the regists of all bikes of the service spot
* Let us get a vector of type Registo with all bikes of the service spot
*/
vector<Registo*> PostoServico::getUtlizacao()		
{
	return utilizacao;
}

/**
* \brief Sets a new service spot's id
* \param id - New id to be implemented
* Sets a new id to the service spot
*/
void PostoServico::setID(int id)		
{
	iD = id;
}

/**
* \brief Sets a new service spot's lotacao
* \param id - New lotacao to be implemented
* Sets a new lotacao to the service spot
*/
void PostoServico::setLotacao(int lot)		 
{
	lotacao = lot;
}

/**
* \brief Sets a new group of disponiveis bikes on the company
* \param disponiveis - New pack of disponiveis bikes to be implemented
* Sets a new pack of disponiveis bikes to the service spot's vector disponiveis
*/
void PostoServico::setDisponiveis(vector<Bicicleta*> disponiveis)		// função modifica as bicicletas disponiveis pelo vetor de bicicletas passado como parametro na função atualizando a ocupação do posto
{
		this ->disponiveis = disponiveis;
		ocupacao = disponiveis.size() + avariadas.size();		
}

/**
* \brief Sets a new group of avariadas bikes on the company
* \param disponiveis - New pack of avariadas bikes to be implemented
* Sets a new pack of avariadas bikes to the service spot's vector avariadas
*/
void PostoServico::setAvariadas(vector<Bicicleta*> avariadas)		
{
		this->avariadas = avariadas;			
		ocupacao = disponiveis.size() + avariadas.size();
}

/**
* \brief Sets a new group of regists to the service spot
* \param disponiveis - New pack of regists to be implemented
* Sets a new pack of regists to the service spot's vector utilizacao
*/
void PostoServico::setUtilizacao(vector<Registo*> utilizacao)		
{
	this->utilizacao = utilizacao;
}

/**
* \brief Adds a bike object to the service spot
* \param *bi1 - New bike to be added
* Adds a bike to the service spot. If it is broken, is implemented on avariadas otherwise it goes to disponiveis
*/
void PostoServico::adicionabicicleta(Bicicleta *bi1)		

{
	if (bi1->getAvariada())
		avariadas.push_back(bi1);
	else
		disponiveis.push_back(bi1);

	ocupacao++;
}

/**
* \brief Adds a bike object to the service spot
* \param *bi1 - New bike to be added
* Adds a bike to the service spot's vector disponiveis and increments ocupacao
*/
void PostoServico::adicionaDisponivel(Bicicleta *bi1)		
{
	disponiveis.push_back(bi1);
	ocupacao++;
}

/**
* \brief Adds a bike object to the service spot
* \param *bi1 - New bike to be added
* Add a bike to the service spot's vector avariadas and increments ocupacao
*/
void PostoServico::adicionaAvariada(Bicicleta *bi1)			
{
	avariadas.push_back(bi1);
	ocupacao++;
}

/**
* \brief Adds a new regist object to the service spot
* \param *reg1 - New regist to be added
* Add a bike to the service spot's vector avariadas and increments ocupacao
*/
void PostoServico::adicionaUtilizacao(Registo *reg1)		
{
	utilizacao.push_back(reg1);
}

/**
* \brief The user rents a bike
* \param *bi1 - bike object to be rentes
* \return true if successfull, false if does not exist
* The user rentes a bike from disponiveis through a parameter and then the ocupacao is decremented
*/
bool PostoServico::aluga(Bicicleta *bi1)		
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

/**
* \brief The user returns a bike
* \param *bi1 - bike object to be return
* \return true if successfull, false if the user returns the bike broken
* The user returns a bike and if it is broken, it goes to avariadas otherwise goes to disponiveis.On both cases the ocupacao is incremented
*/
bool PostoServico::devolve(Bicicleta *bi1)				
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

/**
* \brief The service spot removes a bike
* \param id_bike - identifies the bike to be removed
* \return true if successfull, false if the bike does not exist on disponiveis and avariadas
* The servide spot removes a bike through an id_bike. To do so, the service spot erases the regist of that bike from utilizacao and removes the bike from disponiveis or avariadas
* depending on which section they are. The ocupacao is decremented
*/
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

/**
* \brief The service spot removes a user
* \param user - the user to be deleted
* \return true if successfull, false if the bike does not exist on disponiveis and avariadas
* The servide spot removes the User through an user. To do so, the service spot erases the regist of that user from utilizacao and from disponiveis or avariadas
*/
bool PostoServico::removeutilizador(string user)		 
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

/**
* \brief The service spot fix the broken bikes
* The servide spot fix the broken bikes and put then back to disponiveis
*/
void PostoServico::arranja_bicicletas()			
{
	for (unsigned int i = 0; i < avariadas.size(); i++)
	{
		disponiveis.push_back(avariadas[i]);
		avariadas[i]->setAvariada(false);
		avariadas.erase(avariadas.begin());
	}
}

/**
* \brief The service spot fix an especific broken bike
* \param id_bike - identifies the bike to be fixed
* \return true if successfull, false if the bike does not exist on avariadas
* The servide spot fix a bike through an id_bike. Then it removes from avariadas and put him on disponiveis
*/
bool PostoServico::arranja_bicicleta(int id_bike)	
{
	for (unsigned int i = 0; i < avariadas.size(); i++)
	{
		if (avariadas[i]->getID() == id_bike)
		{

			disponiveis.push_back(avariadas[i]);
			avariadas[i]->setAvariada(false);
			avariadas.erase(avariadas.begin() + i);
			return true;
		}
	}

	return false;
}

/**
* \brief Sends a posto Bike to maintenance
* \param id_bike - id of the bike to send to maintenance
* \returns true if the bike existed, false otherwise
* Sends one of the posto bike's to maintenance, making it available (if 
* it was broken, and adding it a new Registo to tell the system the 
* bike was sent to maintenance
*/
bool PostoServico::manda_manutencao(int id_bike)
{
	for (unsigned int i = 0; i < avariadas.size(); i++)
	{
		if (avariadas[i]->getID() == id_bike)
		{
			Registo *reg;
			reg = new Registo;
			reg->ID_posto_origem = -1;
			reg->ID_Bicicleta = id_bike;
			avariadas[i]->adicionaRegisto(reg);

			disponiveis.push_back(avariadas[i]);
			avariadas[i]->setAvariada(false);

			avariadas.erase(avariadas.begin() + i);
			return true;
		}
	}

	for (unsigned int j = 0; j < disponiveis.size(); j++)
	{
		if (disponiveis[j]->getID() == id_bike)
		{
			Registo *reg;
			reg = new Registo;
			reg->ID_posto_origem = -1;
			disponiveis[j]->adicionaRegisto(reg);
			disponiveis[j]->setAvariada(false);
			return true;
		}
	}

	return false;

}

/**
* \brief Gets the service spot's bikes
* \returns a vector with all the service spot's bikes
* Let us get a vector of type Bicicleta with all bikes of the service spot
*/
vector<Bicicleta*> PostoServico::getBicicletas()
{
	vector<Bicicleta *> bicis = disponiveis;
	bicis.insert(bicis.end(), avariadas.begin(), avariadas.end());
	return bicis;
}

