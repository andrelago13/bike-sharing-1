#include <iostream>
#include "Registo.h"

using namespace std;

void Registo::print_reg() const //funçao que permite saber o estado do aluguer da bicicleta e se esta ficou ou nao avariada durante o mesmo
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

void Registo::print_sem_user() const //funçao que permite saber o estado do aluguer da bicicleta e se esta ficou ou nao avariada durante o mesmo tudo isto relativo a um utilizador ocasional(ou seja sem ter de identificar o utilizador)
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

Registo::Registo() //construtor por defeito de um registo em que todos os parâmetros estao inicializados com os valores "basicos iniciais" --> 0 nos id e string vazia no nome do utilizador
{
	ID_Bicicleta = 0;
	ID_posto_origem = 0;
	ID_posto_chegada = 0;
	nome_utilizador = "";
}

bool operator==(const Registo reg1, const Registo reg2)
{
	if ((reg1.ID_Bicicleta == reg2.ID_Bicicleta) && (reg1.ID_posto_origem == reg2.ID_posto_origem) && (reg1.ID_posto_chegada == reg2.ID_posto_chegada) && (reg1.nome_utilizador == reg2.nome_utilizador) && (reg1.levantamento.getDataStr() == reg2.levantamento.getDataStr()) && (reg1.entrega.getDataStr() == reg2.entrega.getDataStr()) && (reg1.ficou_avariada == reg2.ficou_avariada))
		return true;
	return false;
}