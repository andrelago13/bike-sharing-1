
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
	int ID_posto_origem;
	int ID_posto_chegada;
	string nome_utilizador;
	Data levantamento;
	Data entrega;
	bool ficou_avariada;

	void print_reg() const;
	void print_sem_user() const;
	Registo();
	friend bool operator==(const Registo reg1, const Registo reg2);
};



#endif /* REGISTO_H_ */
