//Classe para maniuplar os arquivos de entrada do programa (processes.txt files.txt)
//Classe vai ler cada linha dos arquivos e armazenar as informcoes contidas nele
//(processos, definidos na classe processo.hpp e informcoes do disco) em estru-
//turas de vetor

//Versao incial so le o arquivo processes.txt
//Versao atual ja le o arquivo files.txt
#ifndef LEITORENTRADAS_H//include de guarda
#define LEITORENTRADAS_H
#include <vector>//para usar std::vector (estrutura que permite trabalahr como vetor, pilha ou lista)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//para usar funcoes como strlen
#include "Processos/Processo.hpp"//para poder criar uma lista de processos
#include "Sistema_Arquivos/SistemaArquivos.hpp"
class LeitorEntradas{
//Inicio da definicao das variaveis da classe
public://a lista de processos e informacoes do disco deverao ser publicas
//para que outros modulos do SO possam acessar esssa informacao 
	std::vector<Processo> lista_processos;
	SistemaArquivos informacao_disco;
//Fim da definicao das variaveis da classe

//Inicio da definicao dos metodos da classe
private:
	/**
	*	Método que verifica se os 4 ultimos caracteres das strings passadas 
	*(argv) como parametro de entrada formam a extensao .txt
	*	
	*	@param char**: argumentos passados via terminal e inseridos em argv[] 
	**/
	bool arquivo_contem_extensao_txt(char**);//char** argv eh o argv da main
	/**
	*	Método que le o arquivo de processos (em formato texto) e adiciona
	*os dados dos processos na lista_processos de acordo com o formato padrao
	*de arquivo de processos presente na especeficicacao do trabalho  
	*	@param FILE*: ponteiro para um arquivo do tipo 'processes' ja aberto  
	**/
	void extrai_informacoes_processos(FILE*);//ponteiro para arquivos de processo
	/**
	*	Método que le o arquivo de configuracao do disco (em formato texto) 
	*e adiciona os dados lidos na classe de sistema_arquivos de acordo 
	com o formato padrao de arquivo do tipo 'files' presente
	*na especeficicacao do trabalho  
	*	@param FILE*: ponteiro para um arquivo do tipo 'files' ja aberto  
	**/
	void extrai_informacoes_disco(FILE* );
	/**
	*	Método que obtem a proxima palavra (token). Uma palavra foi definida
	*como uma sequencia de caracteres entre ','(virgula) ou ' '(espaco)
	**/
	char* proximo_token();
	/**
	*	Método armazena caracter a caracter de um arquivo numa string (char*)
	*ate encontrar qualquer um dos 3 caracteres de parada: EOF(fim do arquivo), 
	*'\n'(fim de linha) ou '\r'(parte do fim da linha presente em sistemas
	*Windows)
	*	@param FILE*:  arquivo (em formato texto) ja aberto
	**/
	char* le_proxima_linha(FILE*);
public:
	LeitorEntradas();//construtor padrao (default)
	//Na versao incial, le_arquivos so le processes.txt (TODO:implementar
	//leitura de files.txt)
	//(DONE:implementar leitura de files.txt)
	/**
	* Método para verificar se os arquivos passados por linha de comando
	*estao de acordo com o esperado: comando da linha de comando possui 3
	*strings (nome_programa,arquivo_processos e arquivos_disco). Metodo
	*confere se os arquivos sao no formato .txt, mas nao confere se a ordem
	*esta correta. Logo, ele espera comandos na ordem 
	*(nome_programa,arquivo_processos e arquivos_disco)
	*
	*	@param int: argc recebido pela funcao princiapl (int main)
	*	@param char**: argv recebido pela funcao princiapl (int main)
	**/
	void le_arquivos(int,char**);//argumentos argc e argv da main
	/**
	*	Metodo percorre a lista de processos e, para cada elemento da lista,
	*imprime o conteudo relativo aquele processo
	**/
	void imprime_informacoes_processos();
	/**
	*	Metodo limpa a lista (std::vector) de processos, deixando-a com 
	*size=0
	**/
	void libera_lista_processos();

	std::vector<Processo> get_lista_processos();

	SistemaArquivos get_disco();
//Fim da definicao dos metodos da classe	
};
#endif