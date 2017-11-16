#include "../include/escalonamento.hpp"

using namespace std;

	escalonador::escalonador()
	{

	}
	void escalonador::algoritmoEscalonamento(arquivos leitor_arquivos, filas processos)
	{
		int i,tempoCPU = 0, pid, tempoInit, tempoProc;
		int tempo1 = 0, tempo2 = 0, tempo3 = 0;
		//gerenciamento das filas:
		while(!processos.Fila0.empty() || !processos.Fila1.empty() || !processos.Fila2.empty() || !processos.Fila3.empty())
		{	//caso a fila de prioridade maxima não esteja vazia
			if(!processos.Fila0.empty())
			{
				pid = processos.existe_processo_para_executar_fila0(leitor_arquivos, tempoCPU);
				if(pid != -1)
				{
					//aloca memoria
					cout << "Dispatcher =>" << endl;
					leitor_arquivos.lista_processos[pid].imprime_infomacoes_processo(pid+1);
					for(i = 1; i <= leitor_arquivos.lista_processos[pid].get_tempo_processador(); i++)
					{
						cout << "P" << pid+1 << " instruction " << i << endl;
					}
					cout << "P" << pid+1 << " return SIGINT " << endl;
					cout << "\n";
					tempoCPU = tempoCPU + leitor_arquivos.lista_processos[pid].get_tempo_processador();
					processos.retira_processo_fila0(pid);
					//desaloca memoria
				} else{
					tempoCPU++;
				}
			}
			//caso a fila de prioridade 1 não esteja vazia
			if(!processos.Fila1.empty())
			{
				pid = processos.existe_processo_para_executar_fila1(leitor_arquivos, tempoCPU);
				if(pid != -1)
				{
					//aloca memoria
					cout << "Dispatcher =>" << endl;
					leitor_arquivos.lista_processos[pid].imprime_infomacoes_processo(pid+1); 
					cout << "P" << pid+1 << " instruction " << tempo1 << endl;
					tempoInit = leitor_arquivos.lista_processos[pid].get_tempo_inicializacao();
					tempoProc = leitor_arquivos.lista_processos[pid].get_tempo_processador() - 1;
					leitor_arquivos.lista_processos[pid].set_tempos(tempoInit,tempoProc);
					tempo1++;
					if(tempoProc == 0)
					{
						cout << "P" << pid+1 << " return SIGINT " << endl;
						cout << "\n";
						processos.retira_processo_fila1(pid);
						printf("ok\n");
					}
					//desaloca memoria
					tempoCPU++;
				} else{
					tempoCPU++;
				}
			}
			//caso a fila de prioridade 2 não esteja vazia
			if(!processos.Fila2.empty())
			{
				pid = processos.existe_processo_para_executar_fila2(leitor_arquivos, tempoCPU);
				if(pid != -1)
				{
					//aloca memoria
					cout << "Dispatcher =>" << endl;
					leitor_arquivos.lista_processos[pid].imprime_infomacoes_processo(pid+1); 
					cout << "P" << pid+1 << " instruction " << tempo1 << endl;
					tempoInit = leitor_arquivos.lista_processos[pid].get_tempo_inicializacao();
					tempoProc = leitor_arquivos.lista_processos[pid].get_tempo_processador() - 1;
					leitor_arquivos.lista_processos[pid].set_tempos(tempoInit,tempoProc);
					tempo2++;
					if(tempoProc == 0)
					{
						cout << "P" << pid+1 << " return SIGINT " << endl;
						cout << "\n";
						processos.retira_processo_fila2(pid);
					}
					//desaloca memoria
					tempoCPU++;
				} else{
					tempoCPU++;
				}
			}
			//caso a fila de prioridade 3 não esteja vazia
			if(!processos.Fila3.empty())
			{
				pid = processos.existe_processo_para_executar_fila3(leitor_arquivos, tempoCPU);
				if(pid != -1)
				{
					//aloca memoria
					cout << "Dispatcher =>" << endl;
					leitor_arquivos.lista_processos[pid].imprime_infomacoes_processo(pid+1); 
					cout << "P" << pid+1 << " instruction " << tempo1 << endl;
					tempoInit = leitor_arquivos.lista_processos[pid].get_tempo_inicializacao();
					tempoProc = leitor_arquivos.lista_processos[pid].get_tempo_processador() - 1;
					leitor_arquivos.lista_processos[pid].set_tempos(tempoInit,tempoProc);
					tempo3++;
					if(tempoProc == 0)
					{
						cout << "P" << pid+1 << " return SIGINT " << endl;
						cout << "\n";
						processos.retira_processo_fila2(pid);
					}
					//desaloca memoria
					tempoCPU++;
				} else{
					tempoCPU++;
				}
			}
			if(processos.Fila0.empty() && processos.Fila1.empty() && processos.Fila2.empty() && processos.Fila3.empty())
				return;	
		}
	}