
#ifndef DATA_H_
#define DATA_H_

#include <string>
#include <iostream>

using namespace std;

class Data
{
public:
	unsigned int ano;
	unsigned int mes;
	unsigned int dia;

	Data();
	Data(unsigned int ano, unsigned int mes, unsigned int dia);
	string getDataStr();
	friend bool operator<(Data data1, Data data2);
	friend bool operator==(Data data1, Data data2);

};

#endif /* DATA_H_ */
