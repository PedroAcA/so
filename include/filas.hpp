#ifndef MODULO_FILAS_H//include de guarda
#define MODULO_FILAS_H
#include <deque>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//para usar funcoes como strlen
#include "Processos/Processo.hpp"
#include "../include/LeitorEntradas.hpp"//para poder criar uma lista de processos
class Filas{
public:

	std::deque<int> Fila0; //fila de prioridade máxima: processos de tempo real
	//Filas destinadas aos processos de usuário:
	std::deque<int> Fila1; //prioridade 1
	std::deque<int> Fila2; //prioridade 2
	std::deque<int> Fila3; //prioridade 3
	
	Filas();
	/**
	metodo que verifica a prioridade de cada processo e os separa entre as filas
	@param : uma lista de processos
	**/
	void insereProcesso(Processo );
	/**
	metodo que verifica de acordo com o tempo de chegada de cada processo pertencente
	a Fila0 se existe um processo que está pronto pra ser executado
	@param : uma lista de processos
	@param : tempo da CPU
	**/
	bool existe_processo_para_executar();

	bool existe_processo_para_executar_fila0();
	/**
	metodo que verifica de acordo com o tempo de chegada de cada processo pertencente
	a Fila1 se existe um processo que está pronto pra ser executado
	@param : uma lista de processos
	@param : tempo da CPU
	**/
	bool existe_processo_para_executar_fila1();
	/**
	metodo que verifica de acordo com o tempo de chegada de cada processo pertencente
	a Fila2 se existe um processo que está pronto pra ser executado
	@param : uma lista de processos
	@param : tempo da CPU
	**/
	bool existe_processo_para_executar_fila2();
	/**
	metodo que verifica de acordo com o tempo de chegada de cada processo pertencente
	a Fila3 se existe um processo que está pronto pra ser executado
	@param : uma lista de processos
	@param : tempo da CPU
	**/
	bool existe_processo_para_executar_fila3();
	/**
	metodo que retira aquele processo da fila0
	@param : o identificador de um processo PID
	**/
	int retira_processo_fila0();
	/**
	metodo que retira aquele processo da fila1
	@param : o identificador de um processo PID
	**/
	int retira_processo_fila1();
	/**
	metodo que retira aquele processo da fila2
	@param : o identificador de um processo PID
	**/
	int retira_processo_fila2();
	/**
	metodo que retira aquele processo da fila3
	@param : o identificador de um processo PID
	**/
	int retira_processo_fila3();
	/**
	metodo que destroi todas as filas
	**/
	void destroiFilas();

	void imprimeEstado();
};
#endif