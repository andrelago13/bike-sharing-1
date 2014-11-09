#ifndef POSTOSERVICO_H_
#define POSTOSERVICO_H_

#include <iostream>
#include <vector>
#include <string>
#include "Registo.h"
#include "Bicicleta.h"

using namespace std;

/*! \class PostoServico
\brief Rede - Auxiliary program class

This class let us manage everything about bikes. Here we can rent or return a bike, fix broken bikes and remove bikes or users. Therefore is class that
help us have a clear vision of what bike-sharing really is
*/
class PostoServico
{
private:
	int lotacao;
	int ocupacao;
	int iD;
	vector<Bicicleta*> disponiveis;
	vector<Bicicleta*> avariadas;
	vector<Registo*> utilizacao;
public:
	// Creates a Service Spot
	PostoServico();
	PostoServico(int iD, int ocupacao, int lotacao);
	
	// Basic Functions
	int getID() const;
	int getLotacao() const;
	int getOcupacao() const;
	int getEspacoLivre() const;
	vector<Bicicleta*> getDisponiveis();
	vector<Bicicleta*> getAvariadas();
	vector<Bicicleta*> getBicicletas();
	vector<Registo*> getUtlizacao();
	void adicionabicicleta(Bicicleta *bi1);
	void adicionaDisponivel(Bicicleta *bi1);
	void adicionaAvariada(Bicicleta *bi1);
	void adicionaUtilizacao(Registo *reg1);
	void setDisponiveis(vector<Bicicleta*> disponiveis);
	void setAvariadas(vector<Bicicleta*> avariadas);
	void setUtilizacao(vector<Registo*> utilizacao);
	void setID(int id);
	void setLotacao(int lot);

	// Rent or Return a bike
	bool aluga(Bicicleta *bi1);			
	bool devolve(Bicicleta *bi1);

	// Remove bikes or users
	bool removebicicleta(unsigned int id_bike);
	bool removeutilizador(string user);

	// Fix Bikes
	void arranja_bicicletas();
	bool arranja_bicicleta(int id_bike);


};

#endif /* POSTOSERVICO_H_ */

