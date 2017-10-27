#ifndef PROCESSO_H //include de guarda para evitar redefinicao da classe caso ela seja incluida em mais de um cpp
#define PROCESSO_H
#include <iostream>//para usar o std::cout e facilitar a impressao das informcoes na tela
//TODO: fazer metodo para calcular offset de memoria
class processo{
//Inicio da definicao das variaveis do processo
private:
	//Inicio da definicao da estrutura contida no arquivo processes.txt
	int tempo_inicializacao, tempo_processador;
	int prioridade;
	int blocos_em_memoria;
	int inicio;
	bool requisicao_impressora,requisicao_scanner,requisicao_modem;
	int codigo_disco;
	//Fim da definicao da estrutura contida no arquivo processes.txt

	//Inicio da definicao de outras variaveis que devem aparecer na tela, mas nao estao no txt
		int Offset_da_memoria;//uma variavel que pode ser calculada 
	/*
		Observacao: cada processo sera colocado em uma estrutura de vetor 
		(std::vector). Logo, seu PID (ID do processo) pode ser entendido como
		o indice atual do vetor + 1 (+ 1, pois o PID comeca em 1 ). Por esse motivo,
		a classe processo nao possui a variavel PID
	*/
	//Fim da definicao de outras variaveis que devem aparecer na tela, mas nao estao no txt
//Fim da definicao das variaveis do processo

//Inicio da definicao dos metodos do processo

public:
	processo();//construtor sem argumentos de entrada permite nao precisar passar todos os argumentos da classe de uma vez 
	//Inicio da declaracao dos setters
	void set_tempos(int,int);//tempos de inicializacao e de processador respectivamente
	void set_requisicoes(bool,bool,bool);//requisicoes de impressora,scanner e modem respectivamente
	void set_prioridade(int);
	void set_blocos_memoria(int);
	void set_inicio(int);
	void set_codigo_disco(int);
	//Fim da declaracao dos setters

	//Inicio da declaracao dos getters
	int get_tempo_inicializacao();
	int get_tempo_processador();
	bool get_requisicao_impressora();
	bool get_requisicao_scanner();
	bool get_requisicao_modem();
	int get_prioridade();
	int get_blocos_memoria();
	int get_inicio();
	int get_codigo_disco();
	//Fim da declaracao dos getters
	void imprime_infomacoes_processo(int);//sera passado a ele o PID
//Fim da definicao dos metodos do processo
};
#endif
