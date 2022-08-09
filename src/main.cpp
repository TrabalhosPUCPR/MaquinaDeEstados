// Leonardo Matthew Knight

/*
ENUNCIADO

Para  obter  os  pontos  relativos  a  este  trabalho,  você  deverá  criar  um  programa,  utilizando  a
linguagem  Python, C, ou C++.  Este  programa,  quando  executado,  irá  determinar  se  uma  string de
entrada  faz  parte  da  linguagem  𝐿    definida  por  𝐿 = {𝑥 | 𝑥 ∈ {𝑎,𝑏}∗ 𝑒 𝑐𝑎𝑑𝑎 𝑎 𝑒𝑚 𝑥 é
𝑠𝑒𝑔𝑢𝑖𝑑𝑜 𝑝𝑜𝑟 𝑝𝑒𝑙𝑜 𝑚𝑒𝑛𝑜𝑠 𝑑𝑜𝑖𝑠 𝑏} segundo o alfabeto  Σ={𝑎,𝑏,𝑐}.

O  programa  que  você  desenvolverá  irá  receber  como  entrada um arquivo de texto  (.txt)
contendo várias strings. A primeira linha do arquivo indica quantas strings estão no arquivo de texto de
entrada. As linhas subsequentes contém uma string por linha.  A seguir está um exemplo das linhas que
podem existir em um arquivo de testes para o programa que você irá desenvolver:

3
abbaba
abababb
bbabbaaab


Neste  exemplo  temos  3  strings  de  entrada.  O  número  de  strings em  cada  arquivo  será
representado  por  um  número  inteiro  positivo.  A  resposta  do  seu  programa  deverá  conter  uma, e
somente uma linha de saída para cada string. Estas linhas conterão a string de entrada e o resultado
da validação conforme o formato indicado a seguir:

abbaba: não pertence.


A  saída  poderá  ser  enviada  para  um  arquivo  de  textos,  ou  para  o  terminal  padrão  e  será
composta de uma linha de saída por string de entrada. No caso do exemplo, teremos 3 linhas de saída.

Para que seu programa possa ser testado você deve criar, no mínimo, três arquivos de entrada
contendo um número diferente de strings diferentes. Os arquivos de entrada criados para os seus testes
devem estar disponíveis tanto no ambiente repl.it quanto no ambiente Github. Observe que o professor
irá  testar  seu  programa  com  os  arquivos  de  testes  que  você  criar  e  com,  no  mínimo  um  arquivo  de
testes criado pelo próprio professor.
 */

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

states &operator++(states &s) // when B is received
{
	if (s == states::s2 || s == states::sn1)
		return s = states::s2; // returns s2 when on last or first state
	return s = static_cast<states>(static_cast<int>(s) + 1); // else, returns the next state
}

states &operator--(states &s) // when A is received
{
	return s = states::s0; // returns s0 by default
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
	// cout << "Select an option: " << endl;
	cout << "Selecione uma opcao: " << endl;
	cout << "1) input1.txt " << endl;
	cout << "2) input2.txt " << endl;
	cout << "3) input3.txt " << endl;
	cout << "4) custom " << endl;
	cout << "R: ";
	cin >> choice;

	ifstream input;
	ofstream output;

	if (choice == 4)
	{
		/*
		cout << "Create a .txt file and put it inside the 'inputs' folder" << endl;
		cout << "Do not leave any empty spaces on the first line" << endl;
		cout << "Type the name of the file with the extension:" << endl;
		*/
		cout << "Crie um arquivo .txt e coloque-o dentro da pasta 'inputs" << endl;
		cout << "Nao deixe espaco vazio na primeira linha" << endl;
		cout << "Digite o nome do arquivo com a extensao:" << endl;
		cout << "R: ";
		string file;
		cin >> file;
		input.open("inputs-output/" + file);
	}
	else
	{
		input.open("inputs-output/input" + to_string(choice) + ".txt");
	}

	if (!input)
	{
		// cout << "Could not find file or selected option doesn't exist!" << endl;
		cout << "Arquivo nao encontrado ou opcao selecionada nao existe!" << endl;
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

		output.open("inputs-output/output.txt");

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
				if (valid /*&& contains(lang, c)*/) // switch case can detect if its not A or B
				{
					// The machine initial state is Sn1, when it receives B, goes to s2
					// Whenever it receives A input, reset its state to s0
					// Whenever it receives B input, it goes to the next state
					// A line is only valid if theres 2 B's after an A
					// So the only condition of failure is if the machine receives A and its state
					// is s0 or s1 and if the final state is not s2
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
			output << line + " : ";
			cout << line + " : ";
			if (valid && current_state == states::s2)
			{
				// cout << "valid" << endl;
				// output << "valid";
				cout << "pertence" << endl;
				output << "pertence" << endl;
			}
			else
			{
				// cout << "not valid" << endl;
				// output << "not valid";
				cout << "nao pertence" << endl;
				output << "nao pertence" << endl;
			}
			n_inputs--;
		}
		output.close();
	}
	return 0;
}
