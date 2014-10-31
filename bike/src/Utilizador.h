/*
 * Utilizador.h
 *
 *  Created on: 31/10/2014
 *      Author: edgar
 */
#ifndef UTILIZADOR_H_
#define UTILIZADOR_H_

#include <iostream>
#include <vector>
#include <string>

#include "Registo.h"

using namespace std;

class Utilizador
{
public:
	string nome;
	unsigned int idade;
	vector <* Registo> users;
};
 //FREQUENTES E OCASIONAIS


#endif /* UTILIZADOR_H_ */
