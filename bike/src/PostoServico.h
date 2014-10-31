/*
 * PostoServico.h
 *
 *  Created on: 31/10/2014
 *      Author: edgar
 */
#include <iostream>
#include<vector>
#include <string>

#include "Registo.h"
#include "Bicicleta.h"
using namespace std;

#ifndef POSTOSERVICO_H_
#define POSTOSERVICO_H_

class PostoServico
{
public:
	int lotacao;
	int ocupacao;
	int ID;
	vector<* Bicicleta> disponiveis;
	vector<* Bicicleta> avariadas;
	vector<* Registo> utilizacao;

};



#endif /* POSTOSERVICO_H_ */
