#ifndef RECURSOS_H //include de guarda para evitar redefinicao da classe caso ela seja incluida em mais de um cpp
#define RECURSOS_H

#include<iostream>
#include"../include/Processos/Processo.hpp"
#define OCUPADO false
#define DISPONIVEL true


class Recursos{

public:

	bool scanner;
    bool impressora[2];
    bool modem;
 
    void inicializaRecursos();
    void imprimeStatus ();

    bool solicitaScanner (Processo *);
    void liberaScanner ();

    bool solicitaModem (Processo *);
    void liberaModem ();

    bool solicitaImpressora (Processo *);
    void liberaImpressora (int);

    void liberaRecursos(Processo *);

};

#endif