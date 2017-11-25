#ifndef RECURSOS_H //include de guarda para evitar redefinicao da classe caso ela seja incluida em mais de um cpp
#define RECURSOS_H

#include<iostream>
#define OCUPADO false
#define DISPONIVEL true


class Recursos{

public:
 
    static void inicializaRecursos ();
    static void imprimeStatus ();

    static bool solicitaScanner ();
    static void liberaScanner ();

    static bool solicitaModem ();
    static void liberaaModem ();

    static bool solicitaImpressora (int);
    static void liberaImpressora (int);

};

#endif