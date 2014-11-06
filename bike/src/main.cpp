#include <iostream>
#include "Rede.h"

// TEST INCLUDES ------------- REMOVE
#include "Tools.h"
#include "Bicicleta.h"

using namespace std;

int main()
{
	Rede network;

	Utilizador usr("Andre", 19, "123456");
	network.addUser(usr);

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

	cout << bic.tipo_valido() << endl;

	//////////////////////////////////////
	//////////Sets -> erros (void)////////
	//////////////////////////////////////

	Bicicleta bici;

	cout << bici.setPrecoDia(0, "adulto") << endl;
	cout << bici.getPreco() << endl;*/
	
	
	system("pause");

	return 0;
}