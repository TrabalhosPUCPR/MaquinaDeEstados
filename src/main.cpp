#include <iostream>
#include <fstream>
#include <stdbool.h>
using namespace std;

// para ficar mais facil de visualizar
enum class estados {
	sn1 = -1,
	s0 = 0,
	s1 = 1,
	s2 = 2
};

estados& operator++(estados& e){
	if(e == estados::s2) return e = estados::s2; // se ja tiver no s2 retorna s2
	return e = static_cast<estados>(static_cast<int>(e) + 1);
}

estados& operator--(estados& e){
	return e = estados::s0; // sempre q tem o A(--) ele volta pra s0
}

bool contains(char array[], char value) {
  	for (int i = 0; i < (sizeof(array) / sizeof(int)); i++) {
    	if (array[i] == value) {
      		return true;
    	}
 	}
  	return false;
}

int main() {
	ifstream input;
	input.open("src/input.txt");
	if(!input){ // caso nao consiga chegar no arquivo
		cout << "Could not reach file!" << endl;
	}else{
		int n_entradas;

		// ler o int que diz a quantidade de entradas que o .txt tem
		input >> n_entradas;

		// pula o \n que tem no fim de toda linha
		input.ignore(1);

		// cria a linguagem e o alfabeto
		char linguagem[2] = {'a', 'b'};
		char alfabeto[3] = {'a', 'b', 'c'};

		// comeca o loop para ler todas as linhas
		while(n_entradas > 0){
			//cout << "n_entradas: " + to_string(n_entradas) << endl;
			bool pertence = true;
			char c;
			string linha;

			estados estado_atual = estados::sn1;

			while(input >> noskipws >> c && c != '\n'){
				linha += c;
				// verifica se a entrada pertence o array linguagem
				if (contains(linguagem, c)) {
					switch(c){
						case 'a':
							if(estado_atual == estados::s0 || estado_atual == estados::s1) pertence = false;
							--estado_atual;
						break;
						case 'b':
							++estado_atual;
						break;
					}
				}else{
					pertence = false;
				}
			}
			if(!pertence || !(estado_atual == estados::s2)){
				cout << linha;
				cout << " : ";
				cout << "nao pertence" << endl;
			}else{
				/*
				cout << linha;
				cout << " : ";
				cout << "ok" << endl;
				*/
			}
			n_entradas--;
		}
	}
	return 0;
}


