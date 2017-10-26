//Modulo principal que simula e gernecia as partes do pseudo-so
#include "../include/arquivos.hpp"
#include "../include/Processos/processo.hpp"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
	int i;
	arquivos leitor_arquivos;
	leitor_arquivos.le_arquivos(argc,argv);
//Laco for abaixo eh uma das maneiras de se acessar a lista de processos
//Outras formas de acesso a lista (std::vector) podem ser encontradas na 
//secao "Element access " de http://www.cplusplus.com/reference/vector/vector/
//(acessado em 26/10/2017 as 11:50)
	for (i = 0; i < (int) leitor_arquivos.lista_processos.size(); i++){
		//Metodo imprime_infomacoes_processo() espera como argumento de entrada
		//o PID, que eh simplesmente o (indice atual da lista de processsos +1)
		leitor_arquivos.lista_processos[i].imprime_infomacoes_processo(i+1);	
	}
	return 0;
}