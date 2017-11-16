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
	void imprime_infos_arquivo();

//Fim da definicao dos metodos da classe

};

#endif