#ifndef MEMORIA_H //include de guarda para evitar redefinicao da classe caso ela seja incluida em mais de um cpp
#define MEMORIA_H

#include<stdlib.h>
#include<stdio.h>
#define SUCESSO true
#define FRACASSO false
#define INICIO_TEMPO_REAL 0
#define FIM_TEMPO_REAL 63
#define INICIO_USUARIO 64
#define FIM_USUARIO 1023

#include "Processos/processo.hpp"

bool memoria_ram[1024];

class Memoria{

public:

    /**
    *  Método que verifica disponibilidade e aloca memoria para processos de tempo real
    *  @param *p ponteiro para o processo que deseja alocar espaço de memoria
    *  @param i indica onde iniciar buscar por memoria (usar default: INICIO_TEMPO_REAL)
    */
    static bool aloca_tempo_real (processo *p, int i);
    /**
    *  Método que verifica disponibilidade e aloca memoria para processos de usuarios
    *  @param *p ponteiro para o processo que deseja alocar espaço de memoria
    *  @param i indica onde iniciar buscar por memoria (usar default: INICIO_USUARIO)
    */
    static bool aloca_usuario (processo *p, int i);
    /**
    *  Método que desaloca memoria para processos de tempo real e processos de usuario
    *  @param *p ponteiro para o processo que deseja liberar espaço de memoria
    */
    static void desaloca_processo (processo *p);
    /**
    *  Método que imprime na tela o estado atual da memória
    */
    static void dump_memory ();
    /**
    *  Método que coloca a memória no estado inicial
    */
    static void inicializa_memoria ();


};

#endif
