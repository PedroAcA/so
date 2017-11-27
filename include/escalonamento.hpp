#ifndef ESCALONAMENTO_H//include de guarda
#define ESCALONAMENTO_H
#include <deque>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//para usar funcoes como strlen
#include "../include/arquivos.hpp"//para poder criar uma lista de processos
#include "../include/filas.hpp"//para poder criar as filas de prioridade
#include "../include/Memoria.hpp"
#include "../include/Recursos.hpp"
class escalonador{
public:
	escalonador();
	bool alocaRecursos(arquivos,int, Recursos);
	void algoritmoEscalonamento(arquivos, filas, Memoria, Recursos);
};
#endif