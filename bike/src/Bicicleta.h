/*
 * Bicicleta.h
 *
 *  Created on: 31/10/2014
 *      Author: edgar
 */

#ifndef BICICLETA_H_
#define BICICLETA_H_


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "Registo.h"
#include "PostoServico.h"

using namespace std;

class Bicicleta
{
public:
	string empresa;
	unsigned int ID;
	vector<* Registo> bicicletas;
	int avariada;
	bool tipo;
	int velocidades;

};



#endif /* BICICLETA_H_ */
