//Classe para maniuplar os arquivos de entrada do programa (processes.txt files.txt)
//Classe vai ler cada linha dos arquivos e armazenar as informcoes contidas nele
//(processos, definidos na classe processo.hpp e informcoes do disco) em estru-
//turas de vetor

//Versao incial so le o arquivo processes.txt
#ifndef ARQUIVOS_H//include de guarda
#define ARQUIVOS_H
#include <vector>//para usar std::vector (estrutura que permite trabalahr como vetor, pilha ou lista)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//para usar funcoes como strlen
#include "Processos/processo.hpp"//para poder criar uma lista de processos
class arquivos{
//Inicio da definicao das variaveis da classe
public://klista de processos e informacoes do disco deverao ser publicas
//para que outros modulos do SO possam acessar esssa informacao 
	std::vector<processo> lista_processos;

//Fim da definicao das variaveis da classe

//Inicio da definicao dos metodos da classe
private:
	bool arquivo_contem_extensao_txt(char**);//char** argv eh o argv da main
	void extrai_informacoes_processos(FILE*);//ponteiro para arquivos de processo
	char* proximo_token();
	char* le_proxima_linha(FILE*);
public:
	arquivos();//construtor default
	//Na versao incial, le_arquivos so le processes.txt (TODO:implementar
	//leitura de files.txt)
	void le_arquivos(int,char**);//argumentos argc e argv da main
	void imprime_informacoes_processos();
	void libera_lista_processos();
//Fim da definicao dos metodos da classe	
};
#endif