/*
 * Registo.h
 *
 *  Created on: 31/10/2014
 *      Author: edgar
 */
#include <iostream>
#include <vector>
#include <string>

#ifndef REGISTO_H_
#define REGISTO_H_
using namespace std;

class Registo
{
public:
	int ID-Bicicleta;
	int ID-Posto;
	string nome_utilizador;
	Data levantamento;
	Data entrega;
	bool ficou_avariada;
};



#endif /* REGISTO_H_ */
