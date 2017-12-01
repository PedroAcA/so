#include "../include/Recursos.hpp"
/*
Esta classe implementa os recursos com suas solicitaçõe e liberações.
*/

	void Recursos::inicializaRecursos (){
    	scanner = DISPONIVEL;
    	impressora[0]=DISPONIVEL;
    	impressora[1]=DISPONIVEL;
    	modem = DISPONIVEL;
    }

/*
    Note que todos os métodos do tipo "solicita" implementam a política de liberar todos os recursos
    detidos por um processo caso um outro recurso o seja negado.
    Esta política é parte da prevenção contra dead-locks implementada neste trabalho pois, nenhum processo
    será bloqueado terá posse de NENHUM recurso, isso é garantido já aqui em "baixo nível" na implementação de recursos.
*/
    bool Recursos::solicitaScanner (Processo *p){
    	if(scanner==DISPONIVEL){
    		scanner=OCUPADO;
            p->detemScanner=true;
    		return true;
    	}

        liberaRecursos(p);
    	return false;

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

    void  Recursos::liberaScanner (){
        scanner = DISPONIVEL;
    }
    void  Recursos::liberaImpressora (int num){
        num--;
        if(num!=0 && num!=1){
            std::cout<<"Numero de impressora invalido!!\n";
        }
        impressora[num]=DISPONIVEL;
    }
    void  Recursos::liberaModem (){
        modem=DISPONIVEL;
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








