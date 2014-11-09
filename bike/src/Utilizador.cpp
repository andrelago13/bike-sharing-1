#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "Registo.h"
#include "Utilizador.h"
#include "Tools.h"

using namespace std;

/*!
\brief Set name of a user
\param nome - new name for the user
*/
void Utilizador::setNome(string nome) //funçao que coloca o nome do utilizador igual a nome
{
	this->nome = nome;
}

/*!
\brief Set idade of a user
\param idade - new idade for the user
*/
void Utilizador::setIdade(int idade) //funçao que coloca a idade do utilizador igual a idade
{
	this->idade = idade;
}

/*!
\brief Get the name of a user
\return name of current Utilizador object
*/
string Utilizador::getNome() const {return nome;} //funçao que retorna o nome do utilizador

/*!
\brief Get the age of a user
\return user's age
*/
int Utilizador::getIdade() const {return idade;} //funçao que retorna a idade do utilizador

/*!
\brief Get all the user rental records
\return vector with pointers to all user complete and incomplete rental records (Registo)
*/
vector<Registo *> Utilizador::getRegs() const {return registos;} //funçao que retorna o vetor de registos dos utilizadores

/*!
\brief Set the vector of Registo pointers of a user
\param regs - new Utilizador rental record
*/
void Utilizador::setRegs(vector<Registo *> regs) //funçao que coloca o vetor de registos dos utilizadores igual a regs
{
	registos = regs;
}

/*!
\brief Get most recent rental record from user
\return Pointer to last Registo of vector registos, or NULL if vector is empty
*/
Registo* Utilizador::ultimoReg() const //funçao que retorna o ultimo registo dos utilizadores(do vetor registos)
{
	if (registos.size() == 0)
		return NULL;

	int pos = registos.size() - 1;

	return registos[pos];
}

/*!
\brief Compare user to string
Compares a user to a string representing it's name
\param name - name to check if it is the user's name
\return true if user's name is equal to param name, false otherwise
*/
bool Utilizador::operator==(string name) //funçao que redefine a expressão de comparação "==" para comparar nomes
{
	if (nome == name)
		return true;
	return false;
}

/*!
\brief Compare two users
Compares current user's name to another user's
\return true if users have same name, false otherwise
*/
bool Utilizador::operator==(Utilizador user) //funçao que redefine a expressão de comparação "==" para comparar utilizadores(os seus nomes)
{
	if (nome == user.nome)
		return true;
	return false;
}

/*!
\brief Assignment operator overload for Utilizador
Copies one user to another one, exactly the same way and using the same pointers
\param user - user to serve as "model"
*/
void Utilizador::operator=(Utilizador user) //funçao que redefine a expressão de igualdade "="
{
	nome = user.nome;
	idade = user.idade;
	password = user.password;

	vector<Registo*> regs2 = user.getRegs();

	for (unsigned int i = 0; i < regs2.size(); i++)
	{
		Registo *ptr;
		ptr = new(Registo);
		*ptr = *regs2[i];
		registos.push_back(ptr);
	}
}

/*!
\brief Overload of << operator, to allow output of user
Outputs user's information, inline, but only name and age
\param o - stream to output to
\param user - Utilizador to output
\return stream to allow inline multiple << operators
*/
ostream& operator<<(ostream &o, Utilizador &user)
{
	o << user.nome << " - " << user.idade << " y/o";
	return o;
}

/*!
\brief Default constructor of Ut_ocasional
Initializes everything like Utilizador default constructor, except for tipo (now equal to 1)
*/
Ut_ocasional::Ut_ocasional() : Utilizador(), cartao("") { tipo = 1; }

/*!
\brief Complete constructor of Ut_ocasional
*/
Ut_ocasional::Ut_ocasional(string name, int age, string pass, string novo_cartao) : Utilizador(name, age, pass), cartao(novo_cartao)
{
	tipo = 1;
}

/*!
\brief Get service cost for Utilizador
This is a virtual function that diferentiates registered from occasional users, by being redefined by the Ut_ocasional class
\return service cost for the Utilizador
*/
int Utilizador::getCusto()
{
	return 40;
}

/*!
\brief Get service cost for Ut_ocasional
Redefinition of the same funtion on Utilizador class
\return service cost for the Ut_ocasional user
*/
int Ut_ocasional::getCusto()
{
	return 2;
}

/*!
\brief Sum of all user rental time
This functions calculates how long the user has been in posession of any Bicicleta, by adding the duration of all his rentals (in days)
\return User's rental time in days
*/
int Utilizador::tempo_aluguer()
{
	int soma = 0;

	if ((registos.size() == 0) || ((registos.size() == 1) && (registos[registos.size() - 1]->ID_posto_chegada == 0)))
		return 0;

	for (unsigned int j = 0; j < registos.size(); j++)
	{
		if (registos[j]->ID_posto_chegada != 0)
			soma += dif_dias(registos[j]->levantamento, registos[j]->entrega) + 1; //dif_dias --> calcula a diferença entre o dia de entrega e do de levantamento
	}
	
	return soma;
}

/*!
\brief Number of user's complete rentals
This function returns the ammount of complete rentals for this user. If checks if the last rental was complete to determine the number of rentals
\return Number of complete rentals by the user
*/
int Utilizador::num_aluguer()
{
	if (registos.size() == 0)
		return 0;
	else if (registos[registos.size() - 1]->ID_posto_chegada == 0)
		return registos.size() - 1;

	return registos.size();
}

/*!
\brief Remove a Bicicleta from all Registo object pointers
This function is used when a Bicicleta is deleted from the system. It erases from the vector all Registo objects relative to
rentals of the Bicicleta with the specified ID
\param id - ID of the Bicicleta to remove
*/
void Utilizador::remove_bici(int id) //função que remove uma bicicleta com um determinado id
{
	for (unsigned int i = 0; i < registos.size(); i++)
	{
		if (registos[i]->ID_Bicicleta == id)
		{
			registos.erase(registos.begin() + i);
			i--;
		}
	}
}

/*!
\brief Get string that represents user
This function is used in Rede::storeInfo(), because it converts the Utilizador object to a multiple line string containing all of it's information
except the rental logs
\return string representing user info
*/
string Utilizador::get_str() const
{
	stringstream ss;
	ss << nome << endl << password << endl << idade << endl << tipo << endl;
	return ss.str();
}

/*!
\brief Make a user from a string that represents it
This function is used in Rede::loadInfo(), because it makes a Utilizador object from a multiple line string that contains all it's information
except for the rental logs
*/
void Utilizador::make_str(string user)
{
	stringstream ss(user);
	string temp;

	getline(ss, temp);
	nome = temp;
	getline(ss, temp);
	password = temp;
	getline(ss, temp);
	idade = str_to_int(temp);
	getline(ss, temp);
	tipo = str_to_int(temp);
}

/*!
\brief Get string that represents user
This function is used in Rede::storeInfo(), because it converts the Ut_ocasional object to a multiple line string containing all of it's information
except the rental logs
\return string representing user info
*/
string Ut_ocasional::get_str() const
{
	string user = Utilizador::get_str();
	stringstream ss(user, ios_base::app | ios_base::out);
	ss << cartao << endl;
	string x = ss.str();
	return ss.str();
}

/*!
\brief Make a user from a string that represents it (in this case, a Ut_ocasional user)
\param user - string with a user
This function is used in Rede::loadInfo(), because it makes a Ut_ocasional object from a multiple line string that contains all it's information
except for the rental logs
*/
void Ut_ocasional::make_str(string user)
{
	stringstream ss(user);
	string temp;

	getline(ss, temp);
	nome = temp;
	getline(ss, temp);
	password = temp;
	getline(ss, temp);
	idade = str_to_int(temp);
	getline(ss, temp);
	tipo = str_to_int(temp);
	getline(ss, temp);
	cartao = temp;
}