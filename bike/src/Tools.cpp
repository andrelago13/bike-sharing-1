#include "Tools.h"
#include <conio.h>
#include <iostream>
#include <sstream>

using namespace std;

int str_to_int(string &str)
{
	int result = atoi(str.c_str());
	if ((result == 0) && (str != "0"))
	{
		string error = "ERROR : Invalid input, must be a number";
		//throw error;
		return -1;
	}
	return result;
}

void get_option(int &option, int min_range, int max_range)
{
	string option_str;

	while (true)
	{
		cout << "Selection : ";
		getline(cin, option_str);
		option = 0;

		try
		{
			option = str_to_int(option_str);
		}
		catch (string error)
		{
			cout << error << endl;
			continue;
		}

		if ((option < min_range) || (option > max_range))
		{
			cout << "Invalid option, not in range." << endl;
			continue;
		}

		break;
	}
}

void clear_screen()
{
	system("cls");
}

template <class Comparable>
int sequentialSearch(const vector<Comparable> &v, Comparable x)
{
	for (unsigned int pos = 0; pos < v.size(); pos++)
	if (v[pos] == x)
		return pos;   // encontrou
	return -1;     // não encontrou
}

template <class Comparable>
void insertionSort(vector<Comparable> &v)
{
	for (unsigned int p = 1; p < v.size(); p++)
	{
		Comparable tmp = v[p];
		int j;
		for (j = p; j > 0 && tmp < v[j - 1]; j--)
			v[j] = v[j - 1];
		v[j] = tmp;
	}
}

string readPassword()
{
	string password;
	char letter = 0;

	while ((int)letter != 13)		// 13 corresponds to the ENTER ASCII Code
	{
		letter = _getch();

		if ((int)letter == 8)		// 8 corresponds to the BACKSPACE ASCII Code
		{
			if (password.length() > 0)
			{
				password.resize(password.size() - 1);
				cout << "\b \b";
			}
		}
		else
		{
			if ((toupper(letter) >= 'A' && toupper(letter) <= 'Z') || (letter >= '0' && letter <= '9'))
			{
				password += letter;
				cout << "*";
			}
		}
	}

	return password;
}

int readInt()
{
	string num_str;
	char letter = 0;

	while ((int)letter != 13)		// 13 corresponds to the ENTER ASCII Code
	{
		letter = _getch();

		if ((int)letter == 8)		// 8 corresponds to the BACKSPACE ASCII Code
		{
			if (num_str.length() > 0)
			{
				num_str.resize(num_str.size() - 1);
				cout << "\b \b";
			}
			
		}
		else
		{
			if (letter >= '0' && letter <= '9')
			{
				stringstream ss;
				int x = atoi(&letter);
				ss << x;

				num_str += ss.str();
				cout << letter;
			}
		}
	}

	if (num_str.size() > 0)
		return str_to_int(num_str);
	return 0;
}

void insert_no_repeat(vector<Registo *> &v1, vector<Registo *> &v2)
{
	for (unsigned int i = 0; i < v2.size(); i++)
	{
		bool exists = false;
		for (unsigned int j = 0; j < v1.size(); j++)
		{
			if (*v1[j] == *v2[i])
			{
				exists = true;
				break;
			}
		}

		if (!exists)
			v1.push_back(v2[i]);
	}
}

bool is_letter(char letra)
{
	if ((toupper(letra) > 'A') && (toupper(letra) < 'Z'))
		return true;
	return false;
}

bool is_number(char letra)
{
	if ((letra >= '0') && (letra <= '9'))
		return true;
	return false;
}

bool valid_date(string date)
{
	if (date.size() == 10)
	{
		if (is_number(date[0]) && is_number(date[1]) && is_number(date[2]) && is_number(date[3]) && (date[4] == '/'))
		{
			if (is_number(date[5]) && is_number(date[6]) && (date[7] == '/') && is_number(date[8]) && is_number(date[9]))
			{
				int ano = str_to_int(date.substr(0, 4));
				int mes = str_to_int(date.substr(5, 2));
				int dia = str_to_int(date.substr(8, 2));

				switch (mes)
				{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					if ((dia > 0) && (dia < 32))
						return true;
					break;
				case 4:
				case 6:
				case 9:
				case 11:
					if ((dia > 0) && (dia < 31))
						return true;
					break;
				case 2:
					if ((((ano % 4) == 0) && (dia > 0) && (dia < 30)) || (((ano % 4) != 0) && (dia > 0) && (dia < 29)))
						return true;
					break;
				default:
					return false;
				}
			}
		}
	}

	return false;
}