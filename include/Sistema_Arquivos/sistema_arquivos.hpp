//Classe para armazenar as configuracoes inciais do disco descritas em 
//um arquivo txt e manipular esses dados, criando um gerenciador
// de arquivos para a simulacao do so
#ifndef SISTEMA_ARQUIVOS_H //include de guarda para evitar redefinicao da classe caso ela seja incluida em mais de um cpp
#define SISTEMA_ARQUIVOS_H
#include <iostream>//para usar o std::cout e facilitar a impressao das informcoes na tela
#include <vector>//para usar std::vector (estrutura que permite trabalahr como vetor, pilha ou lista)
#include <stdlib.h>
#include <stdio.h>
#include "operacao_arquivo.hpp"//para poder criar a lista_operacoes_arquivo
#include "arquivo_gravado.hpp"//para poder criar a lista_arquivos_gravados
#include "../Processos/processo.hpp"//para ter acesso aos pids e prioridades dos processos
class sistema_arquivos{
//Obs.:processos de tempo real tem prioridade 0
//Inicio da definicao das variaveis do processo
	private:
		//Inicio da definicao da estrutura contida no arquivo files.txt
		int total_blocos_disco;
		int n;//n eh a variavel para indicar quantidade de segmentos ocupados
		
		//lista_arquivos_gravados contem as informacoes da linha 3 ate n+2
		//do arquivo files.txt (informacoes sobre arquivos e numeros de blocos
		//gravados no disco
		std::vector<arquivo_gravado> lista_arquivos_gravados;
	
		//lista_operacoes_arquivo contem as infomacoes da linha n+3 ate o
		//final de files.txt (informacoes sobre operacoes de create/delete
		//que os processos podem requisitar para um arquivo)
		std::vector <operacao_arquivo> lista_operacoes_arquivo;
//Fim da definicao da estrutura contida no arquivo files.txt

//ocupacao_memoria vai conter uma lista informando o nome do arquivo 
//gravado naquele bloco (caso exista) ou o caractere '0' (caso nao exista)
//tamanho de ocupacao_memoria eh o numero total de blocos
		std::vector<char> ocupacao_memoria;

//Inicio da definicao dos metodos da classe
	public:
		sistema_arquivos();//construtor sem argumentos de entrada permite nao precisar passar todos os argumentos da classe de uma vez
		//Inicio da declaracao dos setters
		void set_total_blocos_disco(int);
		void set_n(int); 
		//Fim da declaracao dos setters

		/**Metodo que adiciona um elemento a lista_arquivos_gravados. 
			As informacoes a serem adicionadas estao no paramentro de entrada
			@param char* linha lida de files.txt contendo  as informacoes de
				arquivo salvo na memoria (informacoes da linha 3 ate n+2) 
		*/
		void adiciona_arquivo_gravado(char*);

		/**Metodo que adiciona um elemento a lista_operacoes_arquivo. 
			As informacoes a serem adicionadas estao no paramentro de entrada
			@param char* linha lida de files.txt contendo  as informacoes de
				operacao que um processo requisitou fazer em um aruqivo
				(informacoes da linha n+2 ate final do arquivo) 
		*/
		void adiciona_operacao_arquivo(char*);

		//escreve na estrutura que simula o disco (ocupacao_memoria)
		void escreve_no_disco(int,int,char);

		void executa_operacoes_sobre_arquivo(std::vector<processo>);

		void tenta_criar_arquivo(std::vector<processo>);

		int busca_espacos_adjacentes();
		/**
		*	Metodo para imprimir os valores atuais das variaveis:
		* total_blocos_disco, n e para percorrrer as listas de arquivos
		*gravadas e operacoes com arquivos (imprimindo o conteudo de
		*cada um dos elementos da lista)  
		**/
		void imprime_informacoes_disco();
		//Inicio da declaracao dos getters
		int get_total_blocos_disco();
		int get_n();
		//Fim da declaracao dos getters

//Fim da definicao dos metodos da classe
};

#endif