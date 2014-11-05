#include <string>
#include <iostream>

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

void clear_screen() { system("cls"); }

