#include "../include/modulo_filas.hpp"

using namespace std;
//construtor
	filas::filas()
	{

	}

	void filas::insereFilas(arquivos leitor_arquivos)
	{
		int i;
		for (i = 0; i < (int) leitor_arquivos.lista_processos.size(); i++)
		{
			if(leitor_arquivos.lista_processos[i].get_prioridade() == 0) this->Fila0.push_back(i);
			if(leitor_arquivos.lista_processos[i].get_prioridade() == 1) this->Fila1.push_back(i);
			if(leitor_arquivos.lista_processos[i].get_prioridade() == 2) this->Fila2.push_back(i);
			if(leitor_arquivos.lista_processos[i].get_prioridade() == 3) this->Fila3.push_back(i);
		}
	}
	void filas::algoritmoEscalonamento(arquivos leitor_arquivos)
	{
		int i, tempoInicializacao, tempoProcessador, prioridade;
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
	}
	void filas::destroiFilas(void)
	{
		this->Fila0.clear();
		this->Fila1.clear();
		this->Fila2.clear();
		this->Fila3.clear();
	}