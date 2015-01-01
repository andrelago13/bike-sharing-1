#ifndef REDE_H_
#define REDE_H_

#include<vector>
#include "PostoServico.h"
#include "Utilizador.h"
#include "Empresa.h"
#include "Bicicleta.h"
#include <boost/tr1/unordered_set.hpp>

using namespace std;

// Constants for use in menu functions. This values are used for a menu to indicate which menu should be loaded next
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

#define USER_MONTHS_LIMIT 12

struct hUtilizador {

	int operator()(const Utilizador& v1) const{
		return v1.getPassword().size() * v1.getIdade();
	}

	bool operator()(const Utilizador& v1, const Utilizador& v2) const {
		return v1 == v2;
	}

};

typedef tr1::unordered_set<Utilizador, hUtilizador, hUtilizador> hashUtilizador;


/*! \class Rede
\brief Rede - main program class

This class stores and manages all important information of a bike-sharing network, and allows a simple user interface for occasional and registered
users and allows system management with a password authentication
*/
class Rede
{
	vector <Empresa> empresas;				// stores all Empresa objects
	vector<PostoServico*> postos;			// stores all PostoServico objects, and therefore, bikes assigned to posts
	vector<Utilizador*> utilizadores;		// stores all Utilizador objects
	vector<Ut_ocasional*> ocasionais;		// stores all Ut_ocasional objects
	vector<Registo*> curr_rentals;			// stores all Registo objects corresponding to ongoing rentals by occasional users
	vector<Bicicleta*> rented_bikes;		// stores all Bicicleta objects corresponding to bikes currently rented by occasional users
	priority_queue <Bicicleta *> bikes_tempo_uso;		// stores all Bicicleta objects ordered by "use time"
	/* The last 3 vectors are associated with each other. Index i of all vectors corresponds to the same
	ongoing rental by an occasional user*/
	vector<Bicicleta*> rented_bikes_freq;	// stores all Bicicleta objects corresponding to bikes currently rented by occasional users
	string sys_password;					// Rede management function's password

	// Part 2 of the project

	hashUtilizador util_antigos;

public:
	/*!
	\brief Rede default constructor
	Initializes password as an empty string
	*/
	Rede() : sys_password("") {}
	~Rede();

	// Rede functions
	void loadInfo();
	void storeInfo();
	int addUser(Utilizador user);
	int createUser(string nome);
	/*!
	\brief Add a PostoServico to postos vector
	*/
	void addPosto(PostoServico *posto) { postos.push_back(posto); }
	int create_add_bike();
	void reset();
	void assign_regs(vector<Registo *> &regs);
	void update_old_users(Data data_atual);

	// Auxiliary functions
	bool existeUtilizador(string nome);
	int tipoUser(string nome);
	string is_busy(int id_bici, bool print) const;
	vector<Registo *> get_regs() const;
	void adicionaBikesTempUso(Bicicleta *bi1);
	bool remove_Bikes_Tempo(unsigned int id_bike);

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
