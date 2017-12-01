#ifndef ESCALONADOR_H//include de guarda
#define ESCALONADOR_H
#include <deque>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//para usar funcoes como strlen
#include "../include/LeitorEntradas.hpp"//para poder criar uma lista de processos
#include "../include/Filas.hpp"//para poder criar as filas de prioridade
#include "../include/Memoria.hpp"
#include "../include/Recursos.hpp"
#include "../include/Processos/Processo.hpp"
#include "../include/Sistema_Arquivos/SistemaArquivos.hpp"

class Escalonador{
public:
	
	//filas utilizadas para o escalonamento
	std::deque<Processo> processosFuturos;
	std::deque<Processo> processosEsperandoMemoria; 
	std::map<int,Processo> processosRodando; 
	std::deque<Processo> processosTerminados;

	//filas de bloqueados so armazenam pid de processos que estao na fila processosRodando
	std::deque<int> bloqueadosImp1;
	std::deque<int> bloqueadosImp2;
	std::deque<int> bloqueadosModem;
	std::deque<int> bloqueadosScanner;

	int pidExec; 
	bool CPU_livre;


	Filas filasDeProcessos; //filas de prioridade so armazenam pid de processos que estao na fila processosRodando
	Memoria memoria;
	Recursos recursos;
	int Tempo;

	Escalonador();

	void inicializa(std::deque<Processo> listaProcessos,  Recursos recursos, Memoria memoria);
	
	void verificaChegadaProcessos(); 
	void admiteProcesso(int pid);

	bool alocaMemoria(int pid);
	void desalocaMemoria(int pid);

	bool alocaRecursos(int); 
	void desalocaRecursos(int);
	
	void desbloqueiaFilaScanner();
	void desbloqueiaFilaModem();
	void desbloqueiaFilaImpressora(int);
	
	
	void rodaProcessos();
	void executaProcessoCPU();
	void retiraProcessoCPU();
	void mataProcesso(int pid);

	void imprimeEstado();



};
#endif