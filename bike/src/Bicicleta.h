#ifndef BICICLETA_H_
#define BICICLETA_H_


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "Registo.h"
//#include "PostoServico.h"

using namespace std;

class Bicicleta
{
	unsigned int id_num;
	string tipo; // tipos: eletrica, com ou sem cesto, passeio, montanha, corrida
	string tamanho;
	int velocidades;
	bool avariada;
	unsigned int preco;
	vector<Registo*> regs;
	string empresa;
public:

	Bicicleta();
	Bicicleta(unsigned int id, string tipo_bici, string size, int mudancas, bool avariad, unsigned int preco1);
	int getID(); 
	int getVelocidades();
	string getTipo();
	string getTamanho();
	string getEmpresa(); 
	bool getAvariada(); 
	void setAvariada();
	int getPreco();
	void setPrecoDia(int velocidade, string tamanho); 
	bool velocidades_valido(int veloc); 
	string tipo_valido(); 
	string imprime(); 
	void setID(int id); 
	void setTipo(string tipo); 
	void setRegsBicis(vector<Registo *> bicis); 
	vector<Registo *> getRegsBicis() const; 
	void adicionaRegisto(Registo *reg1);
	void setTamanho(string tamanho);
	void setVeloc(int velocidades);
	bool remove_util(string nome);

};

#endif /* BICICLETA_H_ */
