#include "Data.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Tools.h"
#include <iomanip> 

using namespace std;

Data::Data() : ano(0), mes(0), dia(0) {} //construtor por defeito da classe data inicializada como dia "0"

Data::Data(unsigned int ano, unsigned int mes, unsigned int dia) : ano(ano), mes(mes), dia(dia) {}//construtor da classe data inicializando ano como ano, mes como mes e dia como dia



bool operator<(const Data data1, const Data data2) //função que redefine o operador "<" para que se possa comparar se uma data é menor que a outra(mais fácil para obter essa situação posteriormente)
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

bool operator==(const Data data1, const Data data2)//função que redefine o operador "==" que permite comparar se duas datas são iguais 
{
	if (data1.getDataStr() == data2.getDataStr())
		return true;

	return false;
}

string Data::getDataStr() const //função que retorna/imprime a data
{
	stringstream ss;

	ss << setfill('0') << setw(4) << ano << "/" << setfill('0') << setw(2) << mes << "/" << setfill('0') << setw(2) << dia;

	return ss.str();
}

ostream& operator<<(ostream &o, const Data &data) //função que permite cout de uma data 
{
	o << data.getDataStr();
	return o;
}

int dif_dias(Data d1, Data d2) //função que calcula a diferença de dias entre duas datas
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

Data::Data(string date) //construtor de data que constrói a data através de uma string
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