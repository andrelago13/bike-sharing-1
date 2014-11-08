#include <iostream>
#include "Rede.h"

// TEST INCLUDES ------------- REMOVE
#include "Tools.h"
#include "Bicicleta.h"
#include "Registo.h"
#include <fstream>

using namespace std;

int main()
{
	Rede network;

	network.menu_system();

	return 0;

	/*
	Bicicleta bic(1, "eletrica", "adulto", 3, false, 100);

	cout << bic.imprime() << endl;

	int i = bic.getID();
	string p = bic.getTipo();
	string m = bic.getTamanho();
	int a = bic.getVelocidades();
	string u = bic.getAvariada();
	int e = bic.getPreco();
	cout << i << endl << p << endl << m << endl << a << endl;
	cout << u << endl << e << endl;

	cout << bic.tipo_valido() << endl << endl;

	//////////////////////////////////////
	//////////Sets -> erros (void)////////
	//////////////////////////////////////

	Bicicleta bici;

	bici.setID(2);
	bici.setTamanho("crianca");
	bici.setVeloc(2);
	bici.setTipo("corrida");
	cout << "Preco por defeito: " << bici.getPreco() << endl;
	bici.setPrecoDia(1,"adulto");
	
	cout << bici.getPreco() << endl;
	
	system("pause");

	return 0;*/
}