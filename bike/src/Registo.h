
#ifndef REGISTO_H_
#define REGISTO_H_

#include <iostream>
#include <vector>
#include <string>

#include "Data.h"

using namespace std;

/*! \class Registo
\brief Registo - Auxiliary program class

This class allows the program objects to keep track of their history in the Bike-Sharing network. A Registo objects stores the important information of
a bike rental. It keeps track of the ID of the rented bike, the ID's of the source and destination service posts (PostoServico), the name of the renting user
(Utilizador), the date (Data) of rental and return of the bike and determines if the bike got broken or not during the rental
*/
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
	string get_str() const;
	void make_from_str(string reg);
};



#endif /* REGISTO_H_ */
