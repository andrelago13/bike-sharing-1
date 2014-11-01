#include <iostream>
#include <vector>
#include <string>

#include "Bicicleta.h"
#include "PostoServico.h"

using namespace std;

Bicicleta::Bicicleta(unsigned int id, bool tipo, int velocidades): ID(id),tipo(tipo),velocidades(velocidades){}

int Bicicleta::getID()
{
	return id_num;
}

int Bicicleta::getVelocidades()
{
	return velocidades;
}

bool Bicicleta::getTipo()
{
	//return tipo;												AQUI TENS DE RETORNAR UM BOOL E NÃO UMA STRING!
	return false
}

string Bicicleta::getEmpresa()
{
	return empresa;
}

bool Bicicleta::velocidades_valido(int veloc)
{
	if(veloc == velocidades)
		return true;
	return false;
}

bool Bicicleta::tipo_valido()
{
	//if(tipo)		--------------------------------------------------------^^SAME HERE
	//	return true;
	return false;

}
bool Bicicleta::setPreco(int velocidades, string tipo)
{

}
