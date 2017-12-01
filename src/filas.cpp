#include "../include/Filas.hpp"

using namespace std;
//construtor
	Filas::Filas()
	{

	}
	void Filas::insereProcesso(Processo processo)
	{
	
		if(processo.get_prioridade() == 0) this->Fila0.push_back(processo.get_PID());
		if(processo.get_prioridade() == 1) this->Fila1.push_back(processo.get_PID());
		if(processo.get_prioridade() == 2) this->Fila2.push_back(processo.get_PID());
		if(processo.get_prioridade() == 3) this->Fila3.push_back(processo.get_PID());
	
	}


	bool Filas::existe_processo_para_executar()
	{
		return !this->Fila0.empty() || !this->Fila1.empty() || !this->Fila2.empty() || !this->Fila3.empty() ;
	}


	bool Filas::existe_processo_para_executar_fila0()
	{
		return !this->Fila0.empty();
	}

	bool Filas::existe_processo_para_executar_fila1()
	{
		return !this->Fila1.empty();	
	}
	bool Filas::existe_processo_para_executar_fila2()
	{
		return !this->Fila2.empty();
	}
	
	bool Filas::existe_processo_para_executar_fila3()
	{
		return !this->Fila3.empty();
	}

	int Filas::retira_processo_fila0()
	{
		int pid = this->Fila0.front();
		this->Fila0.pop_front();
		return pid;
	}
	int Filas::retira_processo_fila1()
	{
		int pid = this->Fila1.front();
		this->Fila1.pop_front();
		return pid;
	}
	int Filas::retira_processo_fila2()
	{
		int pid = this->Fila2.front();
		this->Fila2.pop_front();
		return pid;
	}
	int Filas::retira_processo_fila3()
	{
		int pid = this->Fila3.front();
		this->Fila3.pop_front();
		return pid;
	}
	void Filas::destroiFilas()
	{
		this->Fila0.clear();
		this->Fila1.clear();
		this->Fila2.clear();
		this->Fila3.clear();
	}
	void Filas::imprimeEstado(){
		std::cout<<"Filas de Prioridade:\n";
		std::cout<<"Fila 0:";
		for(unsigned int i=0; i<Fila0.size(); ++i)
			std::cout<<"\t"<< Fila0[i];
		std::cout<<"\nFila 1:";
		for(unsigned int i=0; i<Fila1.size(); ++i)
			std::cout<<"\t"<< Fila1[i];
		std::cout<<"\nFila 2:";
		for(unsigned int i=0; i<Fila2.size(); ++i)
			std::cout<<"\t"<< Fila2[i];
		std::cout<<"\nFila 3:";
		for(unsigned int i=0; i<Fila3.size(); ++i)
			std::cout<<"\t"<< Fila3[i];
		std::cout<<"\n";

	}