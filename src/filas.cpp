#include "../include/Filas.hpp"

using namespace std;
//construtor
	Filas::Filas()
	{

	}
	void Filas::insereProcessos(std::vector<Processo> lista_processos)
	{
		int i;
		for (i = 0; i < (int) lista_processos.size(); i++)
		{
			lista_processos[i].set_PID(i);

			if(lista_processos[i].get_prioridade() == 0) this->Fila0.push_back(i);
			if(lista_processos[i].get_prioridade() == 1) this->Fila1.push_back(i);
			if(lista_processos[i].get_prioridade() == 2) this->Fila2.push_back(i);
			if(lista_processos[i].get_prioridade() == 3) this->Fila3.push_back(i);
		}
	}
	int Filas::existe_processo_para_executar_fila0(LeitorEntradas leitor_arquivos, int tempoCPU)
	{
		if(this->Fila0.empty()) return -1;
		int id = 0, menor = leitor_arquivos.lista_processos[this->Fila0.front()].get_tempo_inicializacao();
		if(tempoCPU == 0)
		{
			for (deque<int>::iterator it = this->Fila0.begin(); it != this->Fila0.end(); ++it)
			{
				if(leitor_arquivos.lista_processos[*it].get_tempo_inicializacao() < menor)
				{
					menor = leitor_arquivos.lista_processos[*it].get_tempo_inicializacao();
					id = *it;
				}
			}
			return id;
		}else{
			for (deque<int>::iterator it = this->Fila0.begin(); it != this->Fila0.end(); ++it)
			{
				if(leitor_arquivos.lista_processos[*it].get_tempo_inicializacao() <= tempoCPU) return *it;
			}
		}
		return -1;
	}
	int Filas::existe_processo_para_executar_fila1(LeitorEntradas leitor_arquivos, int tempoCPU)
	{
		if(this->Fila1.empty()) return -1;
		int id = 0, menor = leitor_arquivos.lista_processos[this->Fila1.front()].get_tempo_inicializacao();
		if(tempoCPU == 0)
		{
			for (deque<int>::iterator it = this->Fila1.begin(); it != this->Fila1.end(); ++it)
			{
				if(leitor_arquivos.lista_processos[*it].get_tempo_inicializacao() < menor)
				{
					menor = leitor_arquivos.lista_processos[*it].get_tempo_inicializacao();
					id = *it;
				}
			}
			return id;
		}else{
			for (deque<int>::iterator it = this->Fila1.begin(); it != this->Fila1.end(); ++it)
			{
				if(leitor_arquivos.lista_processos[*it].get_tempo_inicializacao() <= tempoCPU) return *it;
			}
		}
		return -1;
	}
	int Filas::existe_processo_para_executar_fila2(LeitorEntradas leitor_arquivos, int tempoCPU)
	{
		if(this->Fila2.empty()) return -1;
		int id = 0, menor = leitor_arquivos.lista_processos[this->Fila2.front()].get_tempo_inicializacao();
		if(tempoCPU == 0)
		{
			for (deque<int>::iterator it = this->Fila2.begin(); it != this->Fila2.end(); ++it)
			{
				if(leitor_arquivos.lista_processos[*it].get_tempo_inicializacao() < menor)
				{
					menor = leitor_arquivos.lista_processos[*it].get_tempo_inicializacao();
					id = *it;
				}
			}
			return id;
		}else{
			for (deque<int>::iterator it = this->Fila2.begin(); it != this->Fila2.end(); ++it)
			{
				if(leitor_arquivos.lista_processos[*it].get_tempo_inicializacao() <= tempoCPU) return *it;
			}
		}
		return -1;
	}
	int Filas::existe_processo_para_executar_fila3(LeitorEntradas leitor_arquivos, int tempoCPU)
	{
		if(this->Fila3.empty()) return -1;
		int id = 0, menor = leitor_arquivos.lista_processos[this->Fila3.front()].get_tempo_inicializacao();
		if(tempoCPU == 0)
		{
			for (deque<int>::iterator it = this->Fila3.begin(); it != this->Fila3.end(); ++it)
			{
				if(leitor_arquivos.lista_processos[*it].get_tempo_inicializacao() < menor)
				{
					menor = leitor_arquivos.lista_processos[*it].get_tempo_inicializacao();
					id = *it;
				}
			}
			return id;
		}else{
			for (deque<int>::iterator it = this->Fila3.begin(); it != this->Fila3.end(); ++it)
			{
				if(leitor_arquivos.lista_processos[*it].get_tempo_inicializacao() <= tempoCPU) return *it;
			}
		}
		return -1;
	}
	void Filas::retira_processo_fila0(int pid)
	{
		this->Fila0.erase(this->Fila0.begin()+pid);
	}
	void Filas::retira_processo_fila1(int pid)
	{
		this->Fila1.erase(this->Fila1.begin()+pid);
	}
	void Filas::retira_processo_fila2(int pid)
	{
		this->Fila2.erase(this->Fila2.begin()+pid);
	}
	void Filas::retira_processo_fila3(int pid)
	{
		this->Fila3.erase(this->Fila3.begin()+pid);
	}
	void Filas::destroiFilas(void)
	{
		this->Fila0.clear();
		this->Fila1.clear();
		this->Fila2.clear();
		this->Fila3.clear();
	}