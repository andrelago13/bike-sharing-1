#include <iostream>
#include "Registo.h"

using namespace std;

void Registo::print_reg() const
{
	cout << "Utilizador : " << nome_utilizador << endl;
	cout << "Bicicleta : " << ID_Bicicleta << endl;
	cout << "Levantada no posto " << ID_posto_origem << " em " << levantamento << endl;
	cout << "Entregue no posto " << ID_posto_chegada << " em " << entrega << endl;
	if (ficou_avariada)
		cout << "A bicicleta ficou avariada neste aluguer." << endl;
	else
		cout << "A bicicleta não sofreu avarias neste aluguer." << endl;
}

void Registo::print_sem_user() const
{
	cout << "Bicicleta : " << ID_Bicicleta << endl;
	cout << "Levantada no posto " << ID_posto_origem << " em " << levantamento << endl;
	cout << "Entregue no posto " << ID_posto_chegada << " em " << entrega << endl;
	if (ficou_avariada)
		cout << "A bicicleta ficou avariada neste aluguer." << endl;
	else
		cout << "A bicicleta não sofreu avarias neste aluguer." << endl;
}