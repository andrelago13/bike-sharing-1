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
	unsigned int id_num;
	string tipo; // tipos: eletrica, com ou sem cesto, passeio, montanha, corrida
	string tamanho;
	int velocidades;
	vector<Registo*> bicicletas;
public:
	string empresa;
	bool avariada;
	unsigned int preco;
	vector <Bicicleta> historico_utilizacao;

	Bicicleta();
	Bicicleta(unsigned int id, string tipo_bici, int mudancas);
	int getID(); //
	int getVelocidades();//
	string getTipo();//
	string getEmpresa(); //
	bool getAvariada(); //
	bool setPrecoDia(int preco); //
	bool velocidades_valido(int veloc); //
	bool tipo_valido(); //
	string imprime(); //
	void setID(); // .....
	void setTipo(string tipo); //
	void setBicis(vector<Registo *> bicis); //
	vector<Registo *> getBicis() const; //

};

#endif /* BICICLETA_H_ */
