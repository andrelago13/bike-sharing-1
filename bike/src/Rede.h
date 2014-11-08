#ifndef REDE_H_
#define REDE_H_

#include<vector>
#include "PostoServico.h"
#include "Utilizador.h"
#include "Empresa.h"
#include "Bicicleta.h"

using namespace std;

#define MENU_exit -1
#define MENU_start 0
#define MENU_regUsr 1
#define MENU_ocUsr 2
#define MENU_manager 3
#define MENU_mngr_supplyers 4
#define MENU_mngr_spots 5
#define MENU_mngr_bikes 6
#define MENU_mngr_users 7
#define MENU_mngr_logs 8

class Rede
{
	vector <Empresa> empresas;
	vector<PostoServico*> postos;
	vector<Utilizador*> utilizadores;
	vector<Ut_ocasional*> ocasionais;
	vector<Registo*> curr_rentals;
	vector<Bicicleta*> rented_bikes;
	vector<Bicicleta*> rented_bikes_freq;
	string sys_password;

public:
	Rede() : sys_password("") {}
	~Rede();
	void loadInfo(); // Load all Rede info from text files
	void storeInfo(); // Store all Rede info into text files

	// Rede functions
	int addUser(Utilizador user);
	int createUser(string nome);
	bool existeUtilizador(string nome);
	int tipoUser(string nome);
	void addPosto(PostoServico *posto) { postos.push_back(posto); }
	string is_busy(int id_bici, bool print) const;
	int create_add_bike();
	vector<Registo *> get_regs() const;

	// Menu system base functions
	int menu_system();
	void print_menu_header();
	void menu_exit_prog();

	// Rede menus
	int menu_start();
	int menu_regUsr();
	int menu_ocUsr();
	int menu_manager();
	int menu_regUsr_logged(Utilizador *user);
	int menu_mngr_supplyers();
	int menu_mngr_spots();
	int menu_mngr_bikes();
	int menu_mngr_users();
	int menu_mngr_logs();

};


#endif /* REDE_H_ */
