#ifndef ESCALONAMENTO_H//include de guarda
#define ESCALONAMENTO_H
#include <deque>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//para usar funcoes como strlen
#include "../include/arquivos.hpp"//para poder criar uma lista de processos
#include "../include/modulo_filas.hpp"//para poder criar as filas de prioridade
#include "../include/Memoria.hpp"
class escalonador{
public:
	escalonador();
	void algoritmoEscalonamento(arquivos, filas);
};
#endif