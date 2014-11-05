#ifndef REDE_H_
#define REDE_H_

#include<vector>

using namespace std;
#include "PostoServico.h"
#include "Utilizador.h"
#include "Empresa.h"

#define MENU_exit -1
#define MENU_start 0
#define MENU_regUsr 1
#define MENU_ocUsr 2
#define MENU_manager 3

class Rede
{
	vector <Empresa> Empresas;
	vector<PostoServico*> PostoServico;
	vector<Utilizador*> Utilizadores;
public:
	Rede() {}
	void loadInfo(); // Load all Rede info from text files
	int menu_system();
	void print_menu_header();
	void menu_exit_prog();

	int menu_start();
	int menu_regUsr();
	int menu_ocUsr();
	int menu_manager();

};


#endif /* REDE_H_ */
