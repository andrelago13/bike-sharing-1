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
	bool avariada;
	unsigned int preco;
	vector<Registo*> bicicletas;
public:
	string empresa;
	vector <Bicicleta> historico_utilizacao;

	Bicicleta();
	Bicicleta(unsigned int id, string tipo_bici, string size, int mudancas, bool avariad, unsigned int preco1);
	int getID(); //
	int getVelocidades();//
	string getTipo();//
	string getTamanho();
	string getEmpresa(); //
	string getAvariada(); //
	int getPreco();
	bool setPrecoDia(int velocidade, string tamanho); //
	bool velocidades_valido(int veloc); //
	string tipo_valido(); //
	string imprime(); //
	void setID(int ID); // .....
	void setTipo(string tipo); //...
	void setBicis(vector<Registo *> bicis); //
	vector<Registo *> getBicis() const; //
	void setTamanho(string tamanho);//.....
	void setVeloc(int velocidades);// .....

};

#endif /* BICICLETA_H_ */
