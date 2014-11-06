#include "Data.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Tools.h"

using namespace std;

Data::Data() : ano(0), mes(0), dia(0) {}

Data::Data(unsigned int ano, unsigned int mes, unsigned int dia) : ano(ano), mes(mes), dia(dia) {}



bool operator<(const Data data1, const Data data2)
{
	if (data1.ano < data2.ano)
		return true;
	else if (data1.ano > data2.ano)
		return false;
	else
	{
		if(data1.mes < data2.mes)
			return true;
		else if (data1.mes > data2.mes)
			return false;
		else
		{
			if (data1.dia < data2.dia)
				return true;
			else
				return false;
		}
	}

	return false;
}

bool operator==(const Data data1, const Data data2)
{
	if (data1.getDataStr() == data2.getDataStr())
		return true;

	return false;
}

string Data::getDataStr() const
{
	stringstream ss;

	ss << ano << "/" << mes << "/" << dia;

	return ss.str();
}

ostream& operator<<(ostream &o, const Data &data)
{
	o << data.getDataStr();
	return o;
}

int dif_dias(Data d1, Data d2)
{
	if (d2 < d1)
		return -1;
	if (d1 == d2)
		return 0;

	int var1 = 0;
	int var2 = 0;

	if ((d1.ano % 4) == 0)
	{
		var1 += 366 * d1.ano;
		if (d1.mes == 2)
			var1 += 29;
	}
	else
	{
		if (d1.mes == 2)
			var1 += 28;
		var1 += 365 * d1.ano;
	}

	switch (d1.mes)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		var1 += 31 * d1.mes;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		var1 += 30 * d1.mes;
		break;
	}


	if ((d2.ano % 4) == 0)
	{
		var2 += 366 * d2.ano;
		if (d2.mes == 2)
			var2 += 29;
	}
	else
	{
		if (d2.mes == 2)
			var2 += 28;
		var2 += 365 * d2.ano;
	}

	switch (d2.mes)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		var2 += 31 * d2.mes;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		var2 += 30 * d2.mes;
		break;
	}

	return var2 - var1;
}

Data::Data(string date)
{
	string ano_str;
	ano_str += date[0];
	ano_str += date[1];
	ano_str += date[2];
	ano_str += date[3];
	int ano_int = str_to_int(ano_str);
	string mes_str;
	mes_str += date[5];
	mes_str += date[6];
	int mes_int = str_to_int(mes_str);
	string dia_str;
	dia_str += date[8];
	dia_str += date[9];
	int dia_int = str_to_int(dia_str);
	this->ano = ano_int;
	this->mes = mes_int;
	this->dia = dia_int;
}