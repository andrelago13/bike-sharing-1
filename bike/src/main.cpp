#include <iostream>
#include "Rede.h"

using namespace std;

int main()
{
	Rede network;
	try
	{
		network.menu_system();
	}
	catch (string e)
	{
		cout << e << endl << endl;
		system("pause");
		return -1;
	}

	return 0;
}

/*! \file Rede.h
\brief Rede class header file
Declaration of the Rede class, as well as defined constants for the menu_system of the class
Also includes some useful
*/

/*! \file Rede.cpp
\brief Implementation of Rede class
Contains the definition of all member functions of Rede class, and their documentation
*/

/*! \file Empresa.h
\brief Empresa class header file
Contains the declaration of the Empresa class
*/

/*! \file Empresa.cpp
\brief Implementation of Empresa class
Contains the definition of all member functions of Empresa class
*/

/*! \file Bicicleta.h
\brief Bicicleta class header file
Contains the declaration of the Bicicleta class
*/

/*! \file Bicicleta.cpp
\brief Implementation of Bicicleta class
Contains the definition of all member functions of Bicicleta class, as well as the definition of constant veloc_max
*/

/*! \file Data.h
\brief Declaration of Data class
Contains the declaration of class Data
*/

/*! \file Data.cpp
\brief Implementation of Data class
Contains the definition of all member functions of Data class,
supporting convertion of Data to other formats
*/

/*! \file PostoServico.h
\brief Declaration of PostoServico class
Contains the declaration of class PostoServico
*/

/*! \file PostoServico.cpp
\brief Implementation of PostoServico class
Contains the definition of all PostoServico funtions
*/

/*! \file Registo.h
\brief Declaration of Registo class
Contains the declaration of the Registo class
*/

/*! \file Registo.cpp
\brief Implementation of Registo class
Contains the definition of all Registo member functions
Allows conversion between Registo and string, both ways
*/

/*! \file Tools.h
\brief	Declaration of auxiliary functions
*/

/*! \file Tools.cpp
\brief Implementation of functions in Tools.h
This file contains some useful, utilitary functions that we considered to be
possibly useful for our solution. It's functions can be used freely in possible, future projects
*/

/*! \file Utilizador.h
\brief Declaration of Utilizador and Ut_ocasional classes
*/

/*! \file Utilizador.cpp
\brief Implementation of Utilizador and Ut_ocasional classes
This classes are necessary for the project. Ut_ocasional is a derived class
of Utilizador that didn't necessarily need to be made, but we though it
could be useful for future utilizations
*/

/*! \mainpage Bike-Sharing network software simulation
*
* \section intro_sec Introduction
*
* This is the documentation for our Bike-Sharing network management and use software.

Our solution offers a simple menu interface that allows usage and maintenance of a Bike-Sharing network, made of
service posts, occupied by bycicles which are supplyed by certain companies. These bikes can be rented by occasional
and registered users, with different payment method and systems. The system management allows creation, addition, update and deletion
of all this features.
*
* \section notes_sec Notes
*
* Our solution is made for Windows only. Though it might work in Linux OS, for optimal performance Windows is recommended.
*
* 
*/