#include <iostream>
#include "Registo.h"

using namespace std;

void Registo::print_reg() const
{
	cout << "User : " << nome_utilizador << endl;
	cout << "Bike : " << ID_Bicicleta << endl;
	cout << "Picked up at post " << ID_posto_origem << " em " << levantamento << endl;
	if (ID_posto_chegada == 0)
	{
		cout << "This rental is still ongoing." << endl;
		return;
	}
	cout << "Delivered at post " << ID_posto_chegada << " em " << entrega << endl;
	if (ficou_avariada)
		cout << "The bike got broken during this rental." << endl;
	else
		cout << "The bike did not get damaged during this rental." << endl;
}

void Registo::print_sem_user() const
{
	cout << "Bike : " << ID_Bicicleta << endl;
	cout << "Picked up at post " << ID_posto_origem << " em " << levantamento << endl;
	if (ID_posto_chegada == 0)
	{
		cout << "This rental is still ongoing." << endl;
		return;
	}
	cout << "Delivered at post " << ID_posto_chegada << " em " << entrega << endl;
	if (ficou_avariada)
		cout << "The bike got broken during this rental." << endl;
	else
		cout << "The bike did not get damaged during this rental." << endl;
}

Registo::Registo()
{
	ID_Bicicleta = 0;
	ID_posto_origem = 0;
	ID_posto_chegada = 0;
	nome_utilizador = "";
}