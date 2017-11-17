#ifndef ARQUIVO_GRAVADO_H //include de guarda para evitar redefinicao da classe caso ela seja incluida em mais de um cpp
#define ARQUIVO_GRAVADO_H
#include <iostream>//para usar o std::cout e facilitar a impressao das informcoes na tela
#include <stdlib.h>
#include <stdio.h>
class arquivo_gravado{
/*nome do arquivo (indicado por uma letra), número do primeiro bloco gravado,
 quantidade de blocos ocupados por este arquivo*/

//Inicio da definicao da estrutura com informacoes de blocos gravados
private:
	char nome_arquivo;
	int num_primeiro_bloco;//numero do primeiro bloco a ser gravado
	int blocos_ocupados;//quantidade de blocos ocupados por este arquiv
//Fim da definicao da estrutura com informacoes de blocos gravados

//pid_criador armazena do pid do processo criador para que seja possivel
//saber se um processo de usuario que quer deletar o arquivo realmente o criou
//pid_criador valido somente para arquivos que nao estao originalmente em
//files.txt. Se estiver, pi_criador = -1 (para que somente processos de
//tempo real possam exculir)
		int pid_criador;
public:
	arquivo_gravado();//construtor padrao (default)
//Inicio da definicao dos metodos da classe
	/**
	*	Metodo vai pegar a linha do arquivo de configuracao do disco 
	*(files.txt) aberto e vai separar as informacoes da linha nos 
	*devidos campos desta classe. 
	*	  
	*	@param char*: linha a ser avaliada. Espera-se que a linha contenha
	*informacoes sobre arquivos e blocos gravados no disco  
	**/
	void insere_informacoes_lidas(char*);
	/**
	*	Metodo para imprimir os valores atuais das variaveis desta classe
	**/
	void imprime_infos_arquivo();
	//Inicio da definicao dos setters
	void set_nome_arquivo(char);
	void set_pid_criador(int);
	//Fim da definicao dos setters

	//Inicio da definicao dos getters
	int get_num_primeiro_bloco();
	int get_blocos_ocupados();
	char get_nome_arquivo();
	//Fim da definicao dos getters

//Fim da definicao dos metodos da classe

};

#endif