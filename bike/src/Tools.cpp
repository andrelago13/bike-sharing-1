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
		throw error;
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
	for (unsigned int i = 0; i < v.size(); i++)
	if (v[i] == x)
		return i;   // encontrou
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
				password.resize(password.size() - 1);
			cout << "\b \b";
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
				int x = letter;
				x = x - '0';
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