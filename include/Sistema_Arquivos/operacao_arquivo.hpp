#ifndef OPERACAO_ARQUIVO_H //include de guarda para evitar redefinicao da classe caso ela seja incluida em mais de um cpp
#define OPERACAO_ARQUIVO_H
#include <iostream>//para usar o std::cout e facilitar a impressao das informcoes na tela
#include <stdlib.h>
#include <stdio.h>

#define criar_arquivo 0
#define deletar_arquivo 1

class operacao_arquivo{
/*ID_Processo,Código_Operação,Nome_arquivo (indicado por uma letra)
,  se_operacaoCriar_numero_blocos
*/
//Inicio da definicao da estrutura com informacoes de operacoes sobre arquivos
private:
	int pid;
	int codigo_operacao;//0=criar arquivo ;1= deletar arquivo
	char nome_arquivo;
	int numero_blocos;//valido somente se a operacao for para criar arquivo
//Fim da definicao da estrutura com informacoes de operacoes sobre arquivos

public:
	operacao_arquivo();//construtor padrao (default)
//Inicio da definicao dos metodos da classe
	/**
	*	Metodo vai pegar a linha do arquivo de configuracao do disco 
	*(files.txt) aberto e vai separar as informacoes da linha nos  
	*devidos campos desta classe. 
	*	  
	*	@param char*: linha a ser avaliada. Espera-se que a linha contenha
	*informacoes sobre operacoes a serem realizadas com um arquivo  
	**/
	void insere_informacoes_lidas(char*);
	/**
	*	Metodo para imprimir os valores atuais das variaveis desta classe
	**/
	void imprime_infos_operacao();

	/**Método que vai indicar se a operacao é criar ou deletar
	um arquivo 
		
		Retorna true se o atributo do codigo_operacao atual é para
		criar um arquivo e false caso contrário
	**/
	bool desja_criar();

	//Inicio da definicao dos getters
	int get_pid();
	int get_numero_blocos();
	char get_nome_arquivo();
	//Fim da definicao dos getters
//Fim da definicao dos metodos da classe
};

#endif