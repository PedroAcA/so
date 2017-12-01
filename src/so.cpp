//Modulo principal que simula e gernecia as partes do pseudo-so
#include "../include/LeitorEntradas.hpp"
#include "../include/Processos/Processo.hpp"
#include "../include/Filas.hpp"
#include "../include/Escalonador.hpp"
#include "../include/Memoria.hpp"
#include "../include/Sistema_Arquivos/SistemaArquivos.hpp"
#include "../include/Recursos.hpp"
#include <stdio.h>
#include <stdlib.h>


/**
A interface que propicia o gerenciamento das filas de prioridade é a biblioteca deque, que ja fornece
uma lista do tipo parametrizada e com as operações de inserção, retirada e exclusão da lista.
http://www.cplusplus.com/reference/deque/deque/
**/

int main(int argc, char* argv[]){
	LeitorEntradas leitor_entradas;
	Recursos recursos;
	std::deque<Processo> lista_processos;
	Filas filasDeProcessos;
	Memoria memoria;
	SistemaArquivos disco;
	Escalonador escalonador;

	
	/**
	//Laco for abaixo eh uma das maneiras de se acessar a lista de processos
	//Outras formas de acesso a lista (std::vector) podem ser encontradas na 
	//secao "Element access " de http://www.cplusplus.com/reference/vector/vector/
	//(acessado em 26/10/2017 as 11:50)
	int i;
	for (i = 0; i < (int) leitor_arquivos.lista_processos.size(); i++){
		//Metodo imprime_infomacoes_processo() espera como argumento de entrada
		//o PID, que eh simplesmente o (indice atual da lista de processsos +1)
		leitor_arquivos.lista_processos[i].imprime_infomacoes_processo(i+1);	
	}
	**/

	leitor_entradas.le_arquivos(argc,argv);

	lista_processos = leitor_entradas.get_lista_processos();
	disco = leitor_entradas.get_disco();
	//filasDeProcessos.insereProcessos(lista_processos);

	memoria.inicializa_memoria();
	recursos.inicializaRecursos();
	escalonador.inicializa(lista_processos, recursos, memoria);
	
	escalonador.rodaProcessos();
	
	//disco.executa_operacoes_sobre_arquivo(lista_processos);
	//disco.imprime_informacoes_disco();
	filasDeProcessos.destroiFilas();

	return 0;
}
