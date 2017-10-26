//Classe para implemetar os metodos definidos em processos.hpp
//TODO: fazer metodo para calcular offset de memoria
#include "../../include/Processos/processo.hpp"
	processo::processo(){//construtor sem argumentos de entrada permite nao precisar passar todos os argumentos da classe de uma vez 

	}
	//Inicio da implementacao dos setters
	void processo::set_tempos(int inicializacao,int processador){//tempos de inicializacao e de processador respectivamente
		this->tempo_inicializacao = inicializacao;
		this->tempo_processador = processador;
	}
	void processo::set_requisicoes(bool impressora,bool scanner ,bool modem){//requisicoes de impressora,scanner e modem respectivamente
		this->requisicao_impressora =  impressora;
		this->requisicao_scanner = scanner;
		this->requisicao_modem = modem;
	}
	void processo::set_prioridade(int prioridade){
		this->prioridade = prioridade;
	}
	void processo::set_blocos_memoria(int blocos_memoria){
		this->blocos_em_memoria = blocos_memoria;
	}
	void processo::set_codigo_disco(int codigo_disco){
		this->codigo_disco = codigo_disco;
	}
	//Fim da implementacao dos setters

	//Inicio da implementacao dos getters
	int processo::get_tempo_inicializacao(){
		return this->tempo_inicializacao;
	}
	int processo::get_tempo_processador(){
		return this->tempo_processador;
	}
	bool processo::get_requisicao_impressora(){
		return this->requisicao_impressora;
	}
	bool processo::get_requisicao_scanner(){
		return this->requisicao_scanner;
	}
	bool processo::get_requisicao_modem(){
		return this->requisicao_modem;
	}
	int processo::get_prioridade(){
		return this->prioridade;
	}
	int processo::get_blocos_memoria(){
		return this->blocos_em_memoria;
	}
	int processo::get_codigo_disco(){
		return this->codigo_disco;
	}
	//Fim da implementacao dos getters
	void processo::imprime_infomacoes_processo(int PID){//sera passado a ele o PID
		std::cout<<std::endl;
		std::cout<<"PID: "<<PID<<std::endl;
		std::cout<<"blocks: "<<this->blocos_em_memoria<<std::endl;
		std::cout<<"priority: "<<this->prioridade<<std::endl;
		std::cout<<"time: "<<this->tempo_processador<<std::endl;
		std::cout<<"printers: "<<this->requisicao_impressora<<std::endl;
		std::cout<<"scanners: "<<this->requisicao_scanner<<std::endl;
		std::cout<<"modems: "<<this->requisicao_modem<<std::endl;
		//drives: 0//nao tem essa informacao no processes.txt, certo?
		std::cout<<std::endl;
	}