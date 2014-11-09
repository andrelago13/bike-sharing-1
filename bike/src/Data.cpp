#include "Data.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Tools.h"
#include <iomanip> 

using namespace std;

/*!
\brief Default constructor of Data class
It initializes the object as being date 0000/00/00
*/
Data::Data() : ano(0), mes(0), dia(0) {}

/*!
\brief Complete Data constructor
\param ano - New object's year
\param mes - New object's month
\param dia - New object's day
*/
Data::Data(unsigned int ano, unsigned int mes, unsigned int dia) : ano(ano), mes(mes), dia(dia) {}/


/*!
\brief Operator < to compare Data objects
Compares two Data objects to determine if one is "before" the other
\param data1 - First Data object
\param data2 - Second Data object
\return true if data1 is prior to data2, and false otherwise
*/
bool operator<(const Data data1, const Data data2)
{
	if (data1.ano < data2.ano)//data é menor se ano for menor
		return true;
	else if (data1.ano > data2.ano)
		return false;
	else
	{
		if(data1.mes < data2.mes) //posteriormente, data é menor se mes for menor
			return true;
		else if (data1.mes > data2.mes)
			return false;
		else
		{
			if (data1.dia < data2.dia)//e por fim, data é menor se dia for menor
				return true;
			else
				return false;
		}
	}

	return false;
}

/*!
\brief Operator == to determine equality of two Data objects
\param data1 - First Data object
\param data2 - Second Data object
\return true if data1 is equal to data2, and false otherwise
*/
bool operator==(const Data data1, const Data data2)
{
	if (data1.getDataStr() == data2.getDataStr())
		return true;

	return false;
}

/*!
\brief Convert Data object to string
This funtion converts the Data object into a string in format YYYY/MM/DD
\return current Data object in string format
*/
string Data::getDataStr() const
{
	stringstream ss;

	ss << setfill('0') << setw(4) << ano << "/" << setfill('0') << setw(2) << mes << "/" << setfill('0') << setw(2) << dia;

	return ss.str();
}

/*!
\brief Allows operator << to use a Data object
Converts the object to a string using getDataStr() and "sends" it to the ostream o
\return ostream reference to allow multiple, inline, << operators
*/
ostream& operator<<(ostream &o, const Data &data)
{
	o << data.getDataStr();
	return o;
}

/*!
\brief Calculates the difference between two dates in days
\param d1 - First Data object
\param d2 - Second Data object
\return day difference between two dates, given that d1 is "older"
Calculates the difference between the two dates, considering the number of days in a month and other factors
*/
int dif_dias(Data d1, Data d2)
{
	static int month_days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int dias = 0;

	if (d1.ano == d2.ano)
	{
		if (d1.mes == d2.mes)
			dias = d2.dia - d1.dia;
		else
		{
			for (int i = d1.mes; i < d2.mes - 1; i++)
				dias += month_days[i];
			dias += month_days[d1.mes - 1] - d1.dia + d2.dia;
		}
	}
	else
	{
		for (int i = 0; i < d2.mes - 1; i++)
			dias += month_days[i];
		for (int i = d1.mes; i < 12; i++)
			dias += month_days[i];
		if (d2.ano - d1.ano >= 0)
			dias += (d2.ano - d1.ano - 1) * 365 +
			month_days[d1.mes - 1] - d1.dia + d2.dia;
	}

	return dias;
}

/*!
\brief Constructor of Date from a string
\param date - string with a date in format YYYY/MM/DD
Constructs a date object from a string in the specified format, useful for construction of objects on loadInfo function of Rede class
*/
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