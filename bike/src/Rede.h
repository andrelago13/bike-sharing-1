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
#define MENU_regUsr_logged 4

class Rede
{
	vector <Empresa> empresas;
	vector<PostoServico*> postos;
	vector<Utilizador*> utilizadores;
public:
	Rede() {}
	~Rede();
	void loadInfo(); // Load all Rede info from text files

	// Rede functions
	int addUser(Utilizador user);
	int createUser(string nome);

	// Menu system base functions
	int menu_system();
	void print_menu_header();
	void menu_exit_prog();

	// Rede menus
	int menu_start();
	int menu_regUsr();
	int menu_ocUsr();
	int menu_manager();
	int menu_regUsr_logged();

};


#endif /* REDE_H_ */
