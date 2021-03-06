//Classe para implemetar os metodos definidos em processos.hpp
//TODO: fazer metodo para calcular offset de memoria
#include "../../include/Processos/Processo.hpp"
	Processo::Processo(){//construtor sem argumentos de entrada permite nao precisar passar todos os argumentos da classe de uma vez 

		detemImpressora = 0;
		detemModem = false;
		detemScanner = false;

	}
	//Inicio da implementacao dos setters
	void Processo::set_PID(int pid){//tempos de inicializacao e de processador respectivamente
		this->PID = pid;
	}

	void Processo::set_tempos(int inicializacao,int processador){//tempos de inicializacao e de processador respectivamente
		this->tempo_inicializacao = inicializacao;
		this->tempo_processador = processador;
	}
	void Processo::set_requisicoes(int impressora,bool scanner ,bool modem){//requisicoes de impressora,scanner e modem respectivamente
		this->requisicao_impressora =  impressora;
		this->requisicao_scanner = scanner;
		this->requisicao_modem = modem;
	}
	void Processo::set_prioridade(int p){
		this->prioridade = p;
	}
	void Processo::set_blocos_memoria(int blocos_memoria){
		this->blocos_em_memoria = blocos_memoria;
	}
	void Processo::set_inicio(int inicio){
		this->inicio = inicio;
	}
	void Processo::set_codigo_disco(int codigo_disco){
		this->codigo_disco = codigo_disco;
	}

	void Processo::set_tempo_rodando(int t){
		this->tempo_rodando=t;
	}
	
	//Fim da declaracao dos setters

	//Inicio da declaracao dos getters
	int Processo::get_tempo_rodando(){
		return tempo_rodando;

	}
	
	int Processo::get_PID(){
		return this->PID;
	}
	
	//Fim da implementacao dos setters

	//Inicio da implementacao dos getters
	int Processo::get_tempo_inicializacao(){
		return this->tempo_inicializacao;
	}
	int Processo::get_tempo_processador(){
		return this->tempo_processador;
	}
	int Processo::get_requisicao_impressora(){
		return this->requisicao_impressora;
	}
	bool Processo::get_requisicao_scanner(){
		return this->requisicao_scanner;
	}
	bool Processo::get_requisicao_modem(){
		return this->requisicao_modem;
	}
	int Processo::get_prioridade(){
		return this->prioridade;
	}
	int Processo::get_blocos_memoria(){
		return this->blocos_em_memoria;
	}
	int Processo::get_inicio(){
		return this->inicio;
	}
	int Processo::get_codigo_disco(){
		return this->codigo_disco;
	}
	//Fim da implementacao dos getters
	void Processo::imprime_informacoes_processo(){
		std::cout<<"Processo "<<this->PID<<std::endl;
		std::cout<<"PID: "<<this->PID<<std::endl;
		std::cout<<"blocks: "<<this->blocos_em_memoria<<std::endl;
		std::cout<<"priority: "<<this->prioridade<<std::endl;
		std::cout<<"time: "<<this->tempo_processador<<std::endl;
		std::cout<<"printers: "<<this->requisicao_impressora<<std::endl;
		std::cout<<"scanners: "<<this->requisicao_scanner<<std::endl;
		std::cout<<"modems: "<<this->requisicao_modem<<std::endl;
		std::cout<<std::endl;
	}
