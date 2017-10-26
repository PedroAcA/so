//Modulo principal que simula e gernecia as partes do pseudo-so
#include "../include/arquivos.hpp"
#include "../include/Processos/processo.hpp"
#include "../include/modulo_filas.hpp"
#include <stdio.h>
#include <stdlib.h>


/**
A interface que propicia o gerenciamento das filas de prioridade é a biblioteca deque, que ja fornece
uma lista do tipo parametrizada e com as operações de inserção, retirada e exclusão da lista.
http://www.cplusplus.com/reference/deque/deque/
**/

int main(int argc, char* argv[]){
	arquivos leitor_arquivos;
	leitor_arquivos.le_arquivos(argc,argv);
	filas escalonador;
	escalonador.insereFilas(leitor_arquivos);
	escalonador.algoritmoEscalonamento(leitor_arquivos);
	escalonador.destroiFilas();
	return 0;
}