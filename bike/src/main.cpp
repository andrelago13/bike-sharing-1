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

	Bicicleta bici(1, "eletrica", "adulto", 3, false, 100);
	Bicicleta *ptr = new Bicicleta();
	*ptr = bici;

	PostoServico posto(123, 2, 10);
	posto.adicionabicicleta(ptr);

	PostoServico *ptr2 = new PostoServico;
	*ptr2 = posto;

	network.addPosto(ptr2);


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