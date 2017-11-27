#include "../include/escalonamento.hpp"

using namespace std;

	escalonador::escalonador()
	{

	}
	bool escalonador::alocaRecursos(arquivos leitor_arquivos, int pid, Recursos recursos)
	{
		//verifica se solicita algum recurso
		if(leitor_arquivos.lista_processos[pid].get_requisicao_impressora() || leitor_arquivos.lista_processos[pid].get_requisicao_scanner() || leitor_arquivos.lista_processos[pid].get_requisicao_modem())
		{
			if(leitor_arquivos.lista_processos[pid].get_requisicao_impressora() == true)
			{
				if(recursos.solicitaImpressora(2) == false)
				{
					if(recursos.solicitaImpressora(1) == false) return false;
				}
			}
			if(leitor_arquivos.lista_processos[pid].get_requisicao_scanner() == true)
			{
				if(recursos.solicitaScanner() == false) return false;
			}
			if(leitor_arquivos.lista_processos[pid].get_requisicao_modem() == true)
			{
				if(recursos.solicitaModem() == false) return false;
			}
		}else{//se nao solicita nenhum recurso
			return true;
		}
		return true;
	}
	void escalonador::desalocaRecursos(arquivos leitor_arquivos, int pid, Recursos recursos)
	{
		//verifica se solicita algum recurso
		if(leitor_arquivos.lista_processos[pid].get_requisicao_impressora() || leitor_arquivos.lista_processos[pid].get_requisicao_scanner() || leitor_arquivos.lista_processos[pid].get_requisicao_modem())
		{
			if(leitor_arquivos.lista_processos[pid].get_requisicao_impressora() == true)
			{
				if(recursos.solicitaImpressora(2) == false) {
					recursos.liberaImpressora (2);
					return;
				}
				if(recursos.solicitaImpressora(1) == false) recursos.liberaImpressora (1);
			}
			if(leitor_arquivos.lista_processos[pid].get_requisicao_scanner() == true) recursos.liberaScanner ();
			if(leitor_arquivos.lista_processos[pid].get_requisicao_modem() == true) recursos.liberaaModem ();
		}else{//se nao solicita nenhum recurso
			return;
		}
		return;
	}
	void escalonador::algoritmoEscalonamento(arquivos leitor_arquivos, filas processos, Memoria memoria, Recursos recursos)
	{
		int i,tempoCPU = 0, pid, tempoInit, tempoProc;
		int pid1 = -1, pid2 = -1, pid3 = -1, tempo1 = 0, tempo2 = 0, tempo3 = 0;
		//gerenciamento das filas:
		while(!processos.Fila0.empty() || !processos.Fila1.empty() || !processos.Fila2.empty() || !processos.Fila3.empty())
		{	//caso a fila de prioridade maxima não esteja vazia
			if(!processos.Fila0.empty())
			{
				pid = processos.existe_processo_para_executar_fila0(leitor_arquivos, tempoCPU);
				//processos de tempo real não precisam de recursos de I/O
				if(pid != -1 && memoria.aloca_tempo_real(&leitor_arquivos.lista_processos[pid],INICIO_TEMPO_REAL))
				{
					cout << "Dispatcher =>" << endl;
					leitor_arquivos.lista_processos[pid].imprime_infomacoes_processo(pid);
					for(i = 1; i <= leitor_arquivos.lista_processos[pid].get_tempo_processador(); i++)
					{
						cout << "P" << pid+1 << " instruction " << i << endl;
					}
					cout << "P" << pid+1 << " return SIGINT " << endl;
					cout << "\n";
					tempoCPU = tempoCPU + leitor_arquivos.lista_processos[pid].get_tempo_processador();
					processos.retira_processo_fila0(pid);
					//desaloca memoria:
					memoria.desaloca_processo(&leitor_arquivos.lista_processos[pid]);
					printf("ok\n");
				} else{
					if(leitor_arquivos.lista_processos[pid].get_blocos_memoria() > 64){
						processos.retira_processo_fila0(pid);
					}
					tempoCPU++;
				}
			}
			//caso a fila de prioridade 1 não esteja vazia
			if(!processos.Fila1.empty())
			{
				pid = processos.existe_processo_para_executar_fila1(leitor_arquivos, tempoCPU);
				if(pid != -1 && memoria.aloca_usuario(&leitor_arquivos.lista_processos[pid],INICIO_USUARIO) && this->alocaRecursos(leitor_arquivos, pid,recursos))
				{
					cout << "Dispatcher =>" << endl;
					leitor_arquivos.lista_processos[pid].imprime_infomacoes_processo(pid); 
					cout << "P" << pid+1 << " instruction " << tempo1 << endl;
					tempoInit = leitor_arquivos.lista_processos[pid].get_tempo_inicializacao();
					tempoProc = leitor_arquivos.lista_processos[pid].get_tempo_processador() - 1;
					leitor_arquivos.lista_processos[pid].set_tempos(tempoInit,tempoProc);
					tempoCPU++;
					tempo1++;
					if(tempoProc == 0)
					{
						cout << "P" << pid+1 << " return SIGINT " << endl;
						cout << "\n";
						processos.retira_processo_fila1(pid);
						//desaloca memoria
						memoria.desaloca_processo(&leitor_arquivos.lista_processos[pid]);
						//desaloca recursos:
						this->desalocaRecursos(leitor_arquivos, pid,recursos);
					}else{
						pid1 = processos.existe_processo_para_executar_fila2(leitor_arquivos, tempoCPU);
						pid2 = processos.existe_processo_para_executar_fila3(leitor_arquivos, tempoCPU);
						pid3 = processos.existe_processo_para_executar_fila0(leitor_arquivos, tempoCPU);
						if(pid1 != -1 || pid2 != -1 || pid3 != -1)
						{
							processos.retira_processo_fila1(pid);
							leitor_arquivos.lista_processos[pid].set_prioridade(2);
							//insere na fila 2:
							processos.Fila2.push_back(pid);
						}
					}
				} else{
					tempoCPU++;
				}
			}
			//caso a fila de prioridade 2 não esteja vazia
			if(!processos.Fila2.empty())
			{
				pid = processos.existe_processo_para_executar_fila2(leitor_arquivos, tempoCPU);
				if(pid != -1 && memoria.aloca_usuario(&leitor_arquivos.lista_processos[pid],INICIO_USUARIO) && this->alocaRecursos(leitor_arquivos, pid,recursos))
				{
					//aloca memoria
					cout << "Dispatcher =>" << endl;
					leitor_arquivos.lista_processos[pid].imprime_infomacoes_processo(pid); 
					cout << "P" << pid+1 << " instruction " << tempo1 << endl;
					tempoInit = leitor_arquivos.lista_processos[pid].get_tempo_inicializacao();
					tempoProc = leitor_arquivos.lista_processos[pid].get_tempo_processador() - 1;
					leitor_arquivos.lista_processos[pid].set_tempos(tempoInit,tempoProc);
					tempoCPU++;
					tempo2++;
					if(tempoProc == 0)
					{
						cout << "P" << pid+1 << " return SIGINT " << endl;
						cout << "\n";
						processos.retira_processo_fila2(pid);
						//desaloca memoria
						memoria.desaloca_processo(&leitor_arquivos.lista_processos[pid]);
						//desaloca recursos:
						this->desalocaRecursos(leitor_arquivos, pid,recursos);
					}else{
						pid1 = processos.existe_processo_para_executar_fila1(leitor_arquivos, tempoCPU);
						pid2 = processos.existe_processo_para_executar_fila3(leitor_arquivos, tempoCPU);
						pid3 = processos.existe_processo_para_executar_fila0(leitor_arquivos, tempoCPU);
						if(pid1 != -1 || pid2 != -1 || pid3 != -1)
						{
							processos.retira_processo_fila2(pid);
							leitor_arquivos.lista_processos[pid].set_prioridade(3);
							//insere na fila 3:
							processos.Fila3.push_back(pid);
						}
					}
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
					leitor_arquivos.lista_processos[pid].imprime_infomacoes_processo(pid); 
					cout << "P" << pid+1 << " instruction " << tempo1 << endl;
					tempoInit = leitor_arquivos.lista_processos[pid].get_tempo_inicializacao();
					tempoProc = leitor_arquivos.lista_processos[pid].get_tempo_processador() - 1;
					leitor_arquivos.lista_processos[pid].set_tempos(tempoInit,tempoProc);
					tempoCPU++;
					tempo3++;
					if(tempoProc == 0)
					{
						cout << "P" << pid+1 << " return SIGINT " << endl;
						cout << "\n";
						processos.retira_processo_fila3(pid);
						//desaloca memoria
						memoria.desaloca_processo(&leitor_arquivos.lista_processos[pid]);
						//desaloca recursos:
						this->desalocaRecursos(leitor_arquivos, pid,recursos);
					}else{
						pid1 = processos.existe_processo_para_executar_fila1(leitor_arquivos, tempoCPU);
						pid2 = processos.existe_processo_para_executar_fila2(leitor_arquivos, tempoCPU);
						pid3 = processos.existe_processo_para_executar_fila0(leitor_arquivos, tempoCPU);
						if(pid1 != -1 || pid2 != -1 || pid3 != -1)
						{
							processos.retira_processo_fila3(pid);
							//insere na fila 3:
							processos.Fila3.push_back(pid);
						}
					}
				} else{
					tempoCPU++;
				}
			}
			if(processos.Fila0.empty() && processos.Fila1.empty() && processos.Fila2.empty() && processos.Fila3.empty())
				return;	
		}
	} 