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
	void algoritmoEscalonamento(arquivos);
	void destroiFilas(void);
};
#endif