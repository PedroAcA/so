//Modulo principal que simula e gernecia as partes do pseudo-so
#include "../include/arquivos.hpp"
#include "../include/Processos/processo.hpp"
#include <deque>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/**
A interface que propicia o gerenciamento das filas de prioridade é a biblioteca deque, que ja fornece
uma lista do tipo parametrizada e com as operações de inserção, retirada e exclusão da lista.
http://www.cplusplus.com/reference/deque/deque/
**/

int main(int argc, char* argv[]){
	int i, tempoInicializacao, tempoProcessador, prioridade;
	arquivos leitor_arquivos;
	leitor_arquivos.le_arquivos(argc,argv);
	//Fila de prioridade 0: processos de tempo real
	deque<int> Fila0;
	//Fila de prioridade 1: processos de usuario
	deque<int> Fila1;
	//Fila de prioridade 2: processos de usuario
	deque<int> Fila2;
	//Fila de prioridade 3: processos de usuario
	deque<int> Fila3;

//Laco for abaixo eh uma das maneiras de se acessar a lista de processos
//Outras formas de acesso a lista (std::vector) podem ser encontradas na 
//secao "Element access " de http://www.cplusplus.com/reference/vector/vector/
//(acessado em 26/10/2017 as 11:50)
/**	for (i = 0; i < (int) leitor_arquivos.lista_processos.size(); i++){
		//Metodo imprime_infomacoes_processo() espera como argumento de entrada
		//o PID, que eh simplesmente o (indice atual da lista de processsos +1)
		leitor_arquivos.lista_processos[i].imprime_infomacoes_processo(i+1);	
	}
**/
	//Apos ler todos os processos o escalonador decide baseado na prioridade dos processos
	//em qual fila será alocado
	for (i = 0; i < (int) leitor_arquivos.lista_processos.size(); i++){
		if(leitor_arquivos.lista_processos[i].get_prioridade() == 0) Fila0.push_back(i);
		if(leitor_arquivos.lista_processos[i].get_prioridade() == 1) Fila1.push_back(i);
		if(leitor_arquivos.lista_processos[i].get_prioridade() == 2) Fila2.push_back(i);
		if(leitor_arquivos.lista_processos[i].get_prioridade() == 3) Fila3.push_back(i);
	}
	//gerenciamento das filas:
	while(true)
	{	//caso a fila de prioridade maxima não esteja vazia
		if(!Fila0.empty()){
			//cede tempo de CPU em preempção
			cout << "Dispatcher =>" << endl;
			leitor_arquivos.lista_processos[Fila0.front()].imprime_infomacoes_processo(Fila0.front()+1);
			for(i = 1; i <= leitor_arquivos.lista_processos[Fila0.front()].get_tempo_processador(); i++)
			{
				cout << "P" << Fila0.front()+1 << " instruction " << i << endl;
			}
			cout << "\n";
			Fila0.pop_front();
		}else{ //caso contrário começa a executar os processos de usuários
			//cede tempo de CPU com preempção usando um quantum de 1
			i = 1;
			while(!Fila1.empty() || !Fila2.empty() || !Fila3.empty())
			{
				if(!Fila1.empty()){
					cout << "Dispatcher =>" << endl;
					leitor_arquivos.lista_processos[Fila1.front()].imprime_infomacoes_processo(Fila1.front()+1);
					cout << "P" << Fila1.front()+1 << " instruction " << i << endl;
					cout << "\n";
					tempoInicializacao = leitor_arquivos.lista_processos[Fila1.front()].get_tempo_inicializacao();
					tempoProcessador = leitor_arquivos.lista_processos[Fila1.front()].get_tempo_processador();
					prioridade = leitor_arquivos.lista_processos[Fila1.front()].get_prioridade();
					//diminui a prioridade
					leitor_arquivos.lista_processos[Fila1.front()].set_prioridade(prioridade + 1);
					//decrementa o tempo de CPU
					leitor_arquivos.lista_processos[Fila1.front()].set_tempos(tempoInicializacao, tempoProcessador - 1);
					Fila2.push_back(Fila1.front());
					Fila1.pop_front();
				}else if(!Fila2.empty()){
					cout << "Dispatcher =>" << endl;
					leitor_arquivos.lista_processos[Fila2.front()].imprime_infomacoes_processo(Fila2.front()+1);
					cout << "P" << Fila2.front()+1 << " instruction " << i << endl;
					cout << "\n";
					tempoInicializacao = leitor_arquivos.lista_processos[Fila2.front()].get_tempo_inicializacao();
					tempoProcessador = leitor_arquivos.lista_processos[Fila2.front()].get_tempo_processador();
					prioridade = leitor_arquivos.lista_processos[Fila2.front()].get_prioridade();
					//diminui a prioridade
					leitor_arquivos.lista_processos[Fila2.front()].set_prioridade(prioridade + 1);
					//decrementa o tempo de CPU
					leitor_arquivos.lista_processos[Fila2.front()].set_tempos(tempoInicializacao, tempoProcessador - 1);
					Fila3.push_back(Fila2.front());
					Fila2.pop_front();
				}else if(!Fila3.empty()){
					cout << "Dispatcher =>" << endl;
					leitor_arquivos.lista_processos[Fila3.front()].imprime_infomacoes_processo(Fila3.front()+1);
					cout << "P" << Fila3.front()+1 << " instruction " << i << endl;
					cout << "\n";
					tempoInicializacao = leitor_arquivos.lista_processos[Fila3.front()].get_tempo_inicializacao();
					tempoProcessador = leitor_arquivos.lista_processos[Fila3.front()].get_tempo_processador();
					//decrementa o tempo de CPU
					leitor_arquivos.lista_processos[Fila3.front()].set_tempos(tempoInicializacao, tempoProcessador - 1);
					if(tempoProcessador - 1 > 0) Fila3.push_back(Fila3.front());
					Fila3.pop_front();
				}
				i++;
			}
			break;
		}
	}
	// desalocar todas as fila
	Fila0.clear();
	Fila1.clear();
	Fila2.clear();
	Fila3.clear();
	return 0;
}