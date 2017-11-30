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

#include "Processos/Processo.hpp"


class Memoria{

public:

    /*TODOS ESTES MÉTODOS SÃO ESTATICOS,PORTANTO NAO NECESSITAM A CRIAÇÃO DE UM OBJETO
      AO CHAMÁ-LOS UTILIZE A FORMA Memoria::metodo(parametros);
    
    */
    /**
    *  Método que verifica disponibilidade e aloca memoria para processos de tempo real
    *  @param *p ponteiro para o processo que deseja alocar espaço de memoria
    *  @param i indica onde iniciar buscar por memoria, é utilizado para auxiliar a recursão
    *  da função (ao chamar, usar default: INICIO_TEMPO_REAL)
    *  Retorna false se não houver espaço disponível e não foi possível alocar, e true se 
    *  o processo foi alocado com sucesso.
    *  Exemplo de chamada: Memoria::aloca_tempo_real(&p,INICIO_TEMPO_REAL);
    */
    static bool aloca_tempo_real (Processo *p, int i);
    /*
    *  Método que verifica disponibilidade e aloca memoria para processos de usuarios
    *  @param *p ponteiro para o processo que deseja alocar espaço de memoria
    *  @param i indica onde iniciar buscar por memoria, é utilizado para auxiliar a recursão
    *  da função (ao chamar, usar default: INICIO_USUARIO)
    *  Retorna false se não houver espaço disponível e não foi possível alocar, e true se 
    *  o processo foi alocado com sucesso.
    *  Exemplo de chamada: Memoria::aloca_usuario(&p,INICIO_USUARIO);
    */
    static bool aloca_usuario (Processo *p, int i);
    /**
    *  Método que desaloca memoria para processos de tempo real e processos de usuario
    *  @param *p ponteiro para o processo que deseja liberar espaço de memoria
    *  Exemplo de chamada: Memoria::desaloca_processo(&p);
    */
    static void desaloca_processo (Processo *p);
    /**
    *  Método que imprime na tela o estado atual da memória
    *  Exemplo de chamada: Memoria::dump_memory();
    */
    static void dump_memory ();
    /**
    *  Método que coloca a memória no estado inicial
    *  Exemplo de chamada: Memoria::inicializa_memoria();
    */
    static void inicializa_memoria ();


};

#endif
