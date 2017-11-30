#ifndef ESCALONADOR_H//include de guarda
#define ESCALONADOR_H
#include <deque>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//para usar funcoes como strlen
#include "../include/LeitorEntradas.hpp"//para poder criar uma lista de processos
#include "../include/Filas.hpp"//para poder criar as filas de prioridade
#include "../include/Memoria.hpp"
#include "../include/Recursos.hpp"
class Escalonador{
public:
	Escalonador();
	bool alocaRecursos(LeitorEntradas,int, Recursos);
	void desalocaRecursos(LeitorEntradas,int, Recursos);
	void algoritmoEscalonamento(LeitorEntradas, Filas, Memoria, Recursos);
};
#endif