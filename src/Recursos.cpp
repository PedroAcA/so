#include "../include/Recursos.hpp"


	void Recursos::inicializaRecursos (){
    	scanner = DISPONIVEL;
    	impressora[0]=DISPONIVEL;
    	impressora[1]=DISPONIVEL;
    	modem = DISPONIVEL;
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

    bool Recursos::solicitaScanner (Processo *p){
    	if(scanner==DISPONIVEL){
    		scanner=OCUPADO;
            p->detemScanner=true;
    		return true;
    	}

        liberaRecursos(p);
    	return false;

    }

    void  Recursos::liberaScanner (){
    	scanner = DISPONIVEL;
    }

    bool  Recursos::solicitaModem (Processo *p){
    	if(modem==DISPONIVEL){
    		modem = OCUPADO;
            p->detemModem = true;
    		return true;
    	}

        liberaRecursos(p);
    	return false;
    }
    
    void  Recursos::liberaModem (){
    	modem=DISPONIVEL;
    }

    bool  Recursos::solicitaImpressora (Processo *p){
    	int num = p->requisicao_impressora;

        num--;
        if(num!=0 && num!=1){
            std::cout<<"Numero de impressora invalido!!\n";
            return false;
        }
    	if(impressora[num]==DISPONIVEL){
    		impressora[num]=OCUPADO;
            p->detemImpressora = num+1;
    		return true;
    	}
        liberaRecursos(p);
    	return false;
    }
    
    void  Recursos::liberaImpressora (int num){
    	num--;
        if(num!=0 && num!=1){
            std::cout<<"Numero de impressora invalido!!\n";
        }
    	impressora[num]=DISPONIVEL;
    }


    void Recursos::liberaRecursos(Processo *p){

        if(p->detemScanner){
            liberaScanner();
            p->detemScanner=false;
        }
        if(p->detemModem){            
            liberaModem();
            p->detemModem=false;
        }
        if(p->detemImpressora!=0){
            liberaImpressora(p->detemImpressora);
            p->detemImpressora=0;
        }

    }








