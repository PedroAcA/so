//Classe para implemetar os metodos definidos em Memoria.hpp
#include "../include/Memoria.hpp"

bool memoria_ram[1024];

bool Memoria::aloca_usuario (processo *p, int i){

    //procura um espaço livre na memoria
    while(i<=FIM_USUARIO && memoria_ram[i]==true)i++;

    //se nao houver espaço livre, retorna fracasso
    if(i==FIM_USUARIO+1) return FRACASSO;

    int j;

    //se houver espaço livre, verificar se o espaço é suficiente
    for (j=i;j<i+p->get_blocos_memoria();j++){
        //se estourar a memoria retorna fracasso
        if(j==FIM_USUARIO+1) return FRACASSO;
        //se o espaço nao for suficiente, tenta achar outro espaço
        if(memoria_ram[j] == true) return aloca_usuario(p,j);
    }

    //se o espaço é suficiente, aloca o espaço
    for (j=i;j<i+p->get_blocos_memoria();j++){
        memoria_ram[j] = true;
    }

    //armazena endereço do primeiro bloco em memoria
    p->set_inicio(i);

    return SUCESSO;
}
void Memoria::desaloca_processo (processo *p){
    int i;

    //a partir do primeiro bloco até o ultimo, seta a memoria como livre
    for(i=p->get_inicio();i<p->get_inicio()+p->get_blocos_memoria();i++){
        memoria_ram[i] = false;
    }

}
bool Memoria::aloca_tempo_real (processo *p, int i){

    //procura um espaço livre na memoria
    while(i<=FIM_TEMPO_REAL && memoria_ram[i]==true)i++;

    //se nao houver espaço livre, retorna fracasso
    if(i==FIM_TEMPO_REAL+1) return FRACASSO;

    int j;

    //se houver espaço livre, verificar se o espaço é suficiente
    for (j=i;j<i+p->get_blocos_memoria();j++){
        //se estourar a memoria retorna fracasso
        if(j==FIM_TEMPO_REAL+1) return FRACASSO;
        //se o espaço nao for suficiente, tenta achar outro espaço
        if(memoria_ram[j] == true) return aloca_tempo_real(p,j);
    }

    //se o espaço é suficiente, aloca o espaço
    for (j=i;j<i+p->get_blocos_memoria();j++){
        memoria_ram[j] = true;
    }

    //armazena endereço do primeiro bloco em memoria
    p->set_inicio(i);

    return SUCESSO;
}

void Memoria::dump_memory (){

    int i;
    for (i= 0; i<1024;i++){
        printf("%d",memoria_ram[i]);
    }
    printf("\n\n");
}

void Memoria::inicializa_memoria (){
    int i;
    for (i= 0; i<1024;i++){
        memoria_ram[i] = false;
    }
}
