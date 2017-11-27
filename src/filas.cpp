#include "../include/filas.hpp"

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
	int filas::existe_processo_para_executar_fila0(arquivos leitor_arquivos, int tempoCPU)
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
	int filas::existe_processo_para_executar_fila1(arquivos leitor_arquivos, int tempoCPU)
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
	int filas::existe_processo_para_executar_fila2(arquivos leitor_arquivos, int tempoCPU)
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
	int filas::existe_processo_para_executar_fila3(arquivos leitor_arquivos, int tempoCPU)
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
	void filas::retira_processo_fila0(int pid)
	{
		this->Fila0.erase(this->Fila0.begin()+pid);
	}
	void filas::retira_processo_fila1(int pid)
	{
		this->Fila1.erase(this->Fila1.begin()+pid);
	}
	void filas::retira_processo_fila2(int pid)
	{
		this->Fila2.erase(this->Fila2.begin()+pid);
	}
	void filas::retira_processo_fila3(int pid)
	{
		this->Fila3.erase(this->Fila3.begin()+pid);
	}
	void filas::destroiFilas(void)
	{
		this->Fila0.clear();
		this->Fila1.clear();
		this->Fila2.clear();
		this->Fila3.clear();
	}