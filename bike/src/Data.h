
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
	string getDataStr() const;
	friend int dif_dias(Data d1, Data d2);
	friend bool operator<(const Data data1, const Data data2);
	friend bool operator==(const Data data1, const Data data2);
	friend ostream& operator<<(ostream &o, const Data &data);
};

#endif /* DATA_H_ */
