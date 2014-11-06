/*
* PostoServico.h
*
*  Created on: 02/11/2014
*      Author: leonardo
*/

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
	int ID;
	vector<Bicicleta*> disponiveis;
	vector<Bicicleta*> avariadas;
	vector<Registo*> utilizacao;
public:
	PostoServico();
	PostoServico(int ID, int ocupacao, int lotacao);
	int getID() const;
	int getLotacao() const;
	int getOcupacao() const;
	vector<Bicicleta*> getDisponiveis();
	vector<Bicicleta*> getAvariadas();
	vector<Registo*> getUtlizacao();
	void adicionaDisponivel(Bicicleta *bi1);
	void adicionaAvariada(Bicicleta *bi1);
	void adicionaUtilizacao(Registo *reg1);
	void setDisponiveis(vector<Bicicleta*> disponiveis);
	void setAvariadas(vector<Bicicleta*> avariadas);
	void setUtilizacao(vector<Registo*> utilizacao);
	//  void show_posto_specs() const;
	bool aluga(Bicicleta *bi1);			// Falta adicionar o registo ao vet de utilizacao
	bool devolve(Bicicleta *bi1);		// Falta adicionar o registo ao vet de utilizacao
	void setLibertaOcup(int lug);
	void setPreencheOcup(int lug);
	bool removebicicleta(Bicicleta *bi1);
};

#endif /* POSTOSERVICO_H_ */

//remover uma bicicleta no posto de serviço e o seu registo
