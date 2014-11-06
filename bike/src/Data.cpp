#include "Data.h"
#include <string>
#include <iostream>
#include <sstream>

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

	int var1 = 365 * d1.ano + d1.ano / 4 - d1.ano / 100 + d1.ano / 400 + (153 * d1.mes - 457) / 5 + d1.dia - 306;
	int var2 = 365 * d2.ano + d2.ano / 4 - d2.ano / 100 + d2.ano / 400 + (153 * d2.mes - 457) / 5 + d2.dia - 306;

	return var2 - var1;
	

}