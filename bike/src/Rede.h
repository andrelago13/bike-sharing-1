#ifndef REDE_H_
#define REDE_H_

#include<vector>

using namespace std;
#include "PostoServico.h"
#include "Utilizador.h"
#include "Empresa.h"


class Rede
{
	vector <Empresa> Empresas;
	vector<PostoServico*> PostoServico;
	vector<Utilizador*> Utilizadores;
public:
	Rede() {}
	void loadInfo(); // Load all Rede info from text files
	int menu_system();
	void clear_screen() { system("cls"); }
	int menu_start();

};


#endif /* REDE_H_ */
