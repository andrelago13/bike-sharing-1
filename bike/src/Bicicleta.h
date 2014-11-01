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
	unsigned int ID;
	string tipo;
	int velocidades;
public:
	string empresa;
	vector<Registo*> bicicletas;
	bool avariada;
	unsigned int preco;

	Bicicleta();
	Bicicleta(unsigned int id, bool tipo, int velocidades);
	int getID();
	int getVelocidades();
	bool getTipo();
	vector <Bicicleta> historico_utilizacao;
	string getEmpresa();
	bool setPreco(int velocidades, string tipo);
	bool velocidades_valido(int veloc);
	bool tipo_valido();
};

class

#endif /* BICICLETA_H_ */
