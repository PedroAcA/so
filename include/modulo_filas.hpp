#ifndef MODULO_FILAS_H//include de guarda
#define MODULO_FILAS_H
#include <deque>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//para usar funcoes como strlen
#include "../include/arquivos.hpp"//para poder criar uma lista de processos
class filas{
public:
	std::deque<int> Fila0;
	std::deque<int> Fila1;
	std::deque<int> Fila2;
	std::deque<int> Fila3;
	filas();
	void insereFilas(arquivos);
	int existe_processo_para_executar_fila0(arquivos, int);
	int existe_processo_para_executar_fila1(arquivos, int);
	int existe_processo_para_executar_fila2(arquivos, int);
	int existe_processo_para_executar_fila3(arquivos, int);
	void retira_processo_fila0(int);
	void retira_processo_fila1(int);
	void retira_processo_fila2(int);
	void retira_processo_fila3(int);
	void destroiFilas(void);
};
#endif