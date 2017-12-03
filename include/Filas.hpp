#ifndef MODULO_FILAS_H//include de guarda
#define MODULO_FILAS_H
#include <deque>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Processos/Processo.hpp"
#include "../include/LeitorEntradas.hpp"
class Filas{
public:

	/*
		Esta classe implementa as filas de prioridade simples.
		São, na pratica quatro filas de inteiros. Ou seja, nestas filas, apenas os PID's dos processos
		serão guardados.
	*/


	std::deque<int> Fila0; //fila prioridade 0
	std::deque<int> Fila1; //fila prioridade 1
	std::deque<int> Fila2; //fila prioridade 2
	std::deque<int> Fila3; //fila prioridade 3
	
	Filas();
	
	
	void insereProcesso(Processo );//Metodo que verifica a prioridade do processo e o coloca na fila adequada

	bool existe_processo_para_executar();

	bool existe_processo_para_executar_fila0();

	bool existe_processo_para_executar_fila1();

	bool existe_processo_para_executar_fila2();

	bool existe_processo_para_executar_fila3();

	int retira_processo_fila0();

	int retira_processo_fila1();

	int retira_processo_fila2();

	int retira_processo_fila3();

	void destroiFilas();

	void imprimeEstado();
};
#endif