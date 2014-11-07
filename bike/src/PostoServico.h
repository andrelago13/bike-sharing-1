#ifndef POSTOSERVICO_H_
#define POSTOSERVICO_H_

#include <iostream>
#include <vector>
#include <string>
#include "Registo.h"
#include "Bicicleta.h"

using namespace std;

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
	PostoServico();
	PostoServico(int iD, int ocupacao, int lotacao);
	int getID() const;
	int getLotacao() const;
	int getOcupacao() const;
	int getEspacoLivre() const;
	vector<Bicicleta*> getDisponiveis();
	vector<Bicicleta*> getAvariadas();
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
	bool aluga(Bicicleta *bi1);			
	bool devolve(Bicicleta *bi1);	
	bool removebicicleta(unsigned int id_bike);
	bool removeutilizador(string user);
	void arranja_bicicletas();
	bool arranja_bicicleta(int id_bike);

};

#endif /* POSTOSERVICO_H_ */

