/*
 * Registo.h
 *
 *  Created on: 31/10/2014
 *      Author: edgar
 */
#ifndef REGISTO_H_
#define REGISTO_H_

#include <iostream>
#include <vector>
#include <string>

#include "Data.h"

using namespace std;

class Registo
{
public:
	int ID_Bicicleta;
	int ID_Posto;
	string nome_utilizador;
	Data levantamento;
	Data entrega;
	bool ficou_avariada;
};



#endif /* REGISTO_H_ */
