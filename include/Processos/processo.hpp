#ifndef PROCESSO_H //include de guarda para evitar redefinicao da classe caso ela seja incluida em mais de um cpp
#define PROCESSO_H
#include <iostream>//para usar o std::cout e facilitar a impressao das informcoes na tela
//TODO: fazer metodo para calcular offset de memoria
class Processo{
//Inicio da definicao das variaveis do processo
//private:
public:
	int  PID;
	int  tempo_inicializacao, tempo_processador, tempo_rodando;
	int  prioridade;
	int  blocos_em_memoria;
	int  inicio;
	int  requisicao_impressora;
	bool requisicao_scanner,requisicao_modem;
	int  codigo_disco;
	int  Offset_da_memoria; 
	int  detemImpressora;
	bool detemScanner;
	bool detemModem;

	Processo();//construtor sem argumentos de entrada permite nao precisar passar todos os argumentos da classe de uma vez 
	//Inicio da declaracao dos setters

	void set_PID(int);
	void set_tempos(int,int);//tempos de inicializacao e de processador respectivamente
	void set_requisicoes(int,bool,bool);//requisicoes de impressora,scanner e modem respectivamente
	void set_prioridade(int);
	void set_blocos_memoria(int);
	void set_inicio(int);
	void set_codigo_disco(int);
	void set_tempo_admissao(int);
	void set_tempo_rodando(int);
	//Fim da declaracao dos setters

	//Inicio da declaracao dos getters
	int get_PID();
	int get_tempo_rodando();
	int get_tempo_inicializacao();
	int get_tempo_processador();
	int get_requisicao_impressora();
	bool get_requisicao_scanner();
	bool get_requisicao_modem();
	int get_prioridade();
	int get_blocos_memoria();
	int get_inicio();
	int get_codigo_disco();
	//Fim da declaracao dos getters
	void imprime_informacoes_processo();//sera passado a ele o PID
//Fim da definicao dos metodos do processo
};
#endif
