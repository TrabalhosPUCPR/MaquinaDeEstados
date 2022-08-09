#include <iostream>
#include <fstream>
#include <stdbool.h>
#include <string.h>
using namespace std;

enum class states
{
	sn1 = -1,
	s0 = 0,
	s1 = 1,
	s2 = 2
};

states &operator++(states &s)
{
	if (s == states::s2 || s == states::sn1)
		return s = states::s2; // returns s2 when on last and first state
	return s = static_cast<states>(static_cast<int>(s) + 1);
}

states &operator--(states &s)
{
	return s = states::s0; // returns s0 whenever -- (A) is received
}

bool contains(char array[], char value)
{
	for (int i = 0; i < (sizeof(*array) / sizeof(int)); i++)
	{
		if (array[i] == value)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	int choice = 1;
	cout << "Select an option: " << endl;
	cout << "1) input1.txt " << endl;
	cout << "2) input2.txt " << endl;
	cout << "3) input3.txt " << endl;
	cout << "4) custom " << endl;
	cin >> choice;

	ifstream input;
	if (choice == 4)
	{
		cout << "Create a .txt file and put it next to main.cpp" << endl;
		cout << "Do not leave any empty spaces on the first line " << endl;
		cout << "Type the name of the file with the extension:" << endl;
		string file;
		cin >> file;
		input.open(file);
	}
	else
	{
		input.open("input" + to_string(choice) + ".txt");
	}
	if (!input)
	{
		cout << "Could not reach file!" << endl;
	}
	else
	{
		int n_inputs;

		// reads first line with the amount of inputs to be read
		input >> n_inputs;

		// skips \n at the end of the line
		input.ignore(1);

		char lang[2] = {'a', 'b'};
		char alph[3] = {'a', 'b', 'c'};

		while (n_inputs > 0)
		{
			// cout << "n_inputs: " + to_string(n_inputs) << endl;
			bool valid = true;
			char c;
			string line;

			states current_state = states::sn1;

			while (input >> noskipws >> c && c != '\n')
			{
				line += c;
				// checks if the input is in the language
				// if the line already doesnt valid, wont send it to the machine
				if (valid /*&& contains(lang, c)*/) // switch case can detect if its not a or b
				{
					// the machine initial state is Sn1, when it receives B, goes to s2
					// whenever it receives A input, reset its state to s0
					// whenever it receives B input, it goes to the next state
					// a line is only valid if theres 2 B's after an A
					// so the only condition of failure is if the machine receives A and its state
					// is on s0 and s1 or if the final state is not s2
					switch (c)
					{
					case 'a':
						if (current_state == states::s0 || current_state == states::s1)
							valid = false;
						--current_state;
						break;
					case 'b':
						++current_state;
						break;
					default:
						valid = false;
						break;
					}
				}
				else
				{
					valid = false;
				}
			}
			if (!valid || !(current_state == states::s2))
			{
				cout << line;
				cout << " : ";
				// cout << "not valid" << endl;
				cout << "nao pertence" << endl;
			}
			else
			{
				cout << line;
				cout << " : ";
				// cout << "valid" << endl;
				cout << "ok" << endl;
			}
			n_inputs--;
		}
	}
	return 0;
}