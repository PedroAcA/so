#include "../include/Recursos.hpp"

	bool scanner;
    bool impressora[2];
    bool modem;

	void Recursos::inicializaRecursos (){
    	scanner = DISPONIVEL;
    	impressora[0]=DISPONIVEL;
    	impressora[1]=DISPONIVEL;
    	modem = DISPONIVEL;
    	std::cout << "recursos inicializados..\n";

    }

    void Recursos::imprimeStatus (){
    	std::cout << "Scanner: ";
    	if(scanner==DISPONIVEL) std::cout << "DISPONIVEL\n";
    	else std::cout << "OCUPADO\n";

    	std::cout << "Modem: ";
    	if(modem==DISPONIVEL) std::cout << "DISPONIVEL\n";
    	else std::cout << "OCUPADO\n";

    	std::cout << "Impressora1: ";
    	if(impressora[0]==DISPONIVEL) std::cout << "DISPONIVEL\n";
    	else std::cout << "OCUPADO\n";

    	std::cout << "Impressora2: ";
    	if(impressora[1]==DISPONIVEL) std::cout << "DISPONIVEL\n";
    	else std::cout << "OCUPADO\n";

    	std::cout<<"\n";

    }

    bool Recursos::solicitaScanner (){
    	if(scanner==DISPONIVEL){
    		scanner=OCUPADO;
    		return true;
    	}
    	return false;

    }
    void  Recursos::liberaScanner (){
    	scanner = DISPONIVEL;

    }

    bool  Recursos::solicitaModem (){
    	if(modem==DISPONIVEL){
    		modem = OCUPADO;
    		return true;
    	}
    	return false;
    }
    
    void  Recursos::liberaaModem (){
    	modem=DISPONIVEL;
    }

    bool  Recursos::solicitaImpressora (int num){
    	num--;
    	if(impressora[num]==DISPONIVEL){
    		impressora[num]=OCUPADO;
    		return true;
    	}
    	return false;
    }
    
    void  Recursos::liberaImpressora (int num){
    	num--;
    	impressora[num]=DISPONIVEL;
    }