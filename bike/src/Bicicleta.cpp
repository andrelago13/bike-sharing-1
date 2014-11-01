/*#include <iostream>
#include <vector>
#include <string>

#include "Bicicleta.h"
#include "PostoServico.h"*/

#include <iostream>
#include <vector>
#include <string>
#include "PostoServico.h"
#include "Bicicleta.h"


using namespace std;

Bicicleta::Bicicleta(unsigned int id, string tipo_bici, int mudancas) : id_num(id), tipo(tipo_bici), velocidades(mudancas), avariada(false), preco(0)
{

}

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
	return false;
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
	return false;
}
