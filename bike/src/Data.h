
#ifndef DATA_H_
#define DATA_H_

#include <string>
#include <iostream>

using namespace std;

/*! \class Data
\brief Data - auxiliary class to keep track of time

This is a simple class we built to simplify the order of time in the rental events of Rede.
Though, it was made in a way that it can be used in other, unrelated projects, because it has a simple, public, interface and
has methods that allow easy convertion between Data and other formats
*/
class Data
{
public:
	unsigned int ano;
	unsigned int mes;
	unsigned int dia;

	Data();
	Data(unsigned int ano, unsigned int mes, unsigned int dia);
	Data(string date);
	string getDataStr() const;
	friend int dif_dias(Data d1, Data d2);
	friend int dif_meses(Data d1, Data d2);
	friend bool operator<(const Data data1, const Data data2);
	friend bool operator==(const Data data1, const Data data2);
	friend ostream& operator<<(ostream &o, const Data &data);
};

#endif /* DATA_H_ */
