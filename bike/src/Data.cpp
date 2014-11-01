#include "Data.h"
#include "string"
#include <iostream>

using namespace std;

Data::Data() : dia(0), mes(0), ano(0) {}

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
