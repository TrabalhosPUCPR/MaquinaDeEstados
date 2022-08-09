#include <iostream>
#include <fstream>
#include <stdbool.h>
using namespace std;

// para ficar mais facil de visualizar
enum estado {
	sn1 = -1,
	s0 = 0,
	s1 = 1,
	s2 = 2
};
// muito legal isso aqui
estado operator++(estado e){
	if(e == s2) return s2; // se ja tiver no s2 retorna s2
	return static_cast<estado>(e + 1); 
}
estado operator--(estado e){
	return s0; // sempre q tem o A(--) ele volta pra s0
}

bool contains(char array[], char value) {
  	for (int i = 0; i < sizeof(array) / sizeof(int); i++) {
    	if (array[i] == value) {
      		return true;
    	}
 	}
  	return false;
}

class Maquina{
	private:
		estado estado_atual = sn1;
		char linguagem[2] = {'a', 'b'};
		char alfabeto[3] = {'a', 'b', 'c'};
	public:
		Maquina();

		// coisas que acontecem nessa maquina de estado finito:
		// toda vez que ele recebe um A, ele volta pro estado 0.
		// toda vez que ele recebe um B, ele incrementa 1, com o valor maximo claro, sendo 2.
		// seguindo isso mesmo se ele tiver no estado inicial (s-1 ou sn1) ele vai pro s0.
		// toda vez que a maquina ta no estado s0, deve-se garantir que ela consiga chegar no s2, se nao, a entrada nao pertence
		// pra isso acontece, toda vez que ele ta no s0, ele ta na expectativa de dois B
		// retorna falso quando o valor nao pertence e verdadeiro quando pertence
		bool receberEntrada(char entr){
			// verifica se a entrada pertence o array linguagem
			if (contains(this->linguagem, entr)) {
				switch(entr){
					case 'a':
						estado_atual--;
					break;
					case 'b':
					break;
				}

				return true;
			}else{
				cout << "naonao";
			}
			return false;
		}
		void receberEntrada(){ estado_atual = sn1;}
};

int main() {
	//maquina.receberEntrada('a');
	ifstream input;
	input.open("src/input.txt");
	if(!input){ // caso nao consiga chegar no arquivo
		cout << "Could not reach file!" << endl;
	}else{
		int n_entradas;

		// ler o int que diz a quantidade de entradas que o .txt tem
		input >> n_entradas;

		// pula o null e o \n que tem no fim de toda linha
		input.ignore(2);

		// cria o objeto da maquina
		Maquina maquina;

		// comeca o loop para ler todas as linhas
		while(n_entradas > 0){
			//cout << "n_entradas: " + to_string(n_entradas) << endl;
			char c;
			while(input >> noskipws >> c && !isblank(c)){
				// le o character e manda para a maquina
				maquina.receberEntrada(c);
			}
			n_entradas--;
			input.ignore(); // pra pular o \n q vem depois do vazio do fim da linha pra alguma razao
		}
	}
	return 0;
}


