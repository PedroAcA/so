//Classe para armazenar as configuracoes inciais do disco descritas em 
//um arquivo txt e manipular esses dados, criando um gerenciador
// de arquivos para a simulacao do so (sistema operacional)
#ifndef SISTEMA_ARQUIVOS_H //include de guarda para evitar redefinicao da classe caso ela seja incluida em mais de um cpp
#define SISTEMA_ARQUIVOS_H
#include <iostream>//para usar o std::cout e facilitar a impressao das informcoes na tela
#include <deque>
#include <vector>//para usar std::vector (estrutura que permite trabalahr como vetor, pilha ou lista)
#include <stdlib.h>
#include <stdio.h>
#include "operacao_arquivo.hpp"//para poder criar a lista_operacoes_arquivo
#include "arquivo_gravado.hpp"//para poder criar a lista_arquivos_gravados
#include "../Processos/Processo.hpp"//para ter acesso aos pids e prioridades dos processos
class SistemaArquivos{
//Obs.:processos de tempo real tem prioridade 0
//Inicio da definicao da estrutura contida no arquivo files.txt
	private:
		//Inicio da definicao da estrutura contida no arquivo files.txt
		int total_blocos_disco;
		int n;//variavel para indicar quantidade de segmentos ocupados
		
		//lista_arquivos_gravados contem as informacoes da linha 3
		//ate n+2 do arquivo files.txt (informacoes sobre arquivos e 
		//numero de blocos gravados no disco)
		std::vector<arquivo_gravado> lista_arquivos_gravados;
	
		/*lista_operacoes_arquivo contem as infomacoes da linha n+3
		ate o final de files.txt(informacoes sobre operacoes de create
		ou delete que os processos podem requisitar para um arquivo)*/
		std::vector <operacao_arquivo> lista_operacoes_arquivo;
//Fim da definicao da estrutura contida no arquivo files.txt

//ocupacao_memoria vai conter uma lista informando o nome do arquivo 
//gravado naquele bloco (caso exista) ou o caractere '0' (caso
// nao exista) 
//tamanho da lista de ocupacao_memoria = numero total de blocos
		std::vector<char> ocupacao_memoria;

//Inicio da definicao dos metodos da classe
	private:
		/**Metodo que imprime uma mensagem indicando sucesso na criacao
		do arquivo, bem como as seguintes informacoes: pid do processo
		criador, nome do arquivo criado, bloco inicial no qual o arquivo
		foi criado e bloco final no qual o arquivo foi criado.
		   Tem que ser chamado apos o arquivo ter sido criado, por isso
		o metodo é internamente chamado em tenta_criar_arquivo()
			
			@param operacao_arquivo: classe (definida 
			em operacao_arquivo.hpp) que contem os dados da operacao
			atual a ser realizada pelo sistema de arquivos. Os
			seguintes atributos sao utilizados no metodo: pid, nome
			do arquivo e numero de blocos que serao ocupados.

			@param int : bloco inicial onde o arquivo comecou a ser 
			gravado

		**/
		void imprime_mensagem_sucesso_criacao_arquivo(operacao_arquivo,int);
		/**Metodo para criar o arquivo se for possivel (ha espaco
		contiguo no disco e nao ha arquivo com mesmo nome). Essas
		condicoes sao verificadas dentro do metodo 
		**/
		void tenta_criar_arquivo();
		/**Metodo para deletar arquivo se for possivel (arquivo a 
		ser deletado existe e processo que o quer deletar é de tempo
		real ou é de usuário e criou o arquivo ). Essas
		condicoes sao verificadas dentro do metodo
		   Tem que ser chamado por uma funcao/metodo no qual é 
		verificado se o processo está contido na lista de processos.
		Por esse motivo, método é chamado internamente em
		executa_operacoes_sobre_arquivo(std::deque<Processo>)

			@param std::deque<Processo>: lista com todos os processos
			existentes (os atributos e metodos de um processo estao
			definidos na classe Processo). Somente a informacao de 
			prioriadade é utilizada da lista de processos 
		**/
		void tenta_deletar_arquivo(std::deque<Processo>);
		/**Método para verificar se o pid do processo criador do 
		arquivo cujo nome foi passado pela funcao como char 
		é o mesmo pid do processo que o quer deletar
			
			@param int: pid do processo de usuário que quer deletar
			o arquivo

			@param char: nome do arquivo a ser deletado
			
			Retorna true se o nome do arquivo a ser deletado existe
			na lista de arquivos gravados E o pid do processo que
			criou aquele arquivo é igual ao pid passado como 
			parametro de entrada para a funcao. 
			Observação: caso o arquivo a ser deletado esteja entre
			as linhas 3 e n+2, o pid do processo associado a ele é
			negativo. Logo, para esses casos, a funcao deve retornar
			false
		**/
		bool processo_criou_arquivo(int,char);
		/**Método que obtem as informacões sobre o arquivo gravado
		no disco para que ele possa ser deletado. As informacoes sao
		encapsuladas como atributos da classe definida em 
		"arquivo_gravado.hpp"  

			@param char: nome do arquivo a ser deletado

			Retorna o indice do arquivo gravado correpondente ao nome
			passado como parametro de entrada da funcao. Retorna -1
			caso nao exista a correspondencia

		**/
		int procura_arquivo_a_ser_deletado(char);
		/**Método que obtem o bloco inicial e o total de blocos 
		ocupados por um arquivo e deleta esse arquivo. Apoós esse
		processo, imprime na tela uma mensagem informando que o
		arquivo foi deletado

			@param char: nome do arquivo que sera deletado

			@param operacao_arquivo: objeto da classe definida em
			operacao_arquivo. Utilizado para saber o pid do processo
			que deletou o arquivo  

		**/
		void deleta_arquivo(char,operacao_arquivo);
		/**Método que escreve na estrutura que simula o disco 
		(ocupacao_memoria), efetivamente salvando o conteudo no
		'disco'
		Parametros da esquerda para a direita:

			@param int: bloco inicial onde se encontra o arquivo

			@param int: total de blocos a serem escritos

			@param char: nome do arquivo a ser escrito ou '0' para
			arquivo ser deletado

		**/
		void escreve_no_disco(int,int,char);
		/**Método que procura encontrar espacos adjacentes com um
		tamanho qu e caiba o arquivo. Utiliza técnica de firs-fit

			Retorna o numero do primeiro bloco que possua espacos
			adjacentes suficientes para escrever arquivo ou -1 se
			nao ha espaco para criar o arquivo 
		**/
		int busca_espacos_adjacentes();
		/**Método que busca na lista de ocupacao_memoria se existe
		um arquivo cujo nome foi passado como parametro de entrada

			@param char: nome do arquivo

			Retorna true se há pelo menos um bloco com nome de 
			arquivo igual ao passado pela funcao ou false caso 
			contrário 
		**/
		bool existe_arquivo_gravado_com_mesmo_nome(char);
		/**Método que salva informacoes, úteis para a operação de 
		deletar, do arquivo que esta sendo criado. Essas informacoes
		sao:nome, pid do processo criador, numero do primeiro bloco
		a ser gravado e quantidade de blocos ocupados pelo arquivo
		sendo ocupado

			@param operacao_arquivo: operacao de criacao do arquivo
			atual

			@param int: numero do primeiro bloco no qual o arquivo
			foi gravado

		**/
		void salva_processo_criador_do_arquivo(operacao_arquivo,int);
	public:
		/*construtor sem argumentos de entrada permite nao precisar
		passar todos os argumentos da classe de uma vez*/
		SistemaArquivos();
		//Inicio da declaracao dos setters
		void set_total_blocos_disco(int);
		void set_n(int); 
		//Fim da declaracao dos setters

		/**Metodo que adiciona um elemento a lista_arquivos_gravados. 
			As informacoes a serem adicionadas estao no paramentro de entrada
			@param char*: linha lida de files.txt contendo  as informacoes de
				arquivo salvo na memoria (informacoes da linha 3 ate n+2) 
		*/
		void adiciona_arquivo_gravado(char*);

		/**Metodo que adiciona um elemento a lista_operacoes_arquivo. 
			As informacoes a serem adicionadas estao no paramentro de entrada
			@param char*: linha lida de files.txt contendo  as informacoes de
				operacao que um processo requisitou fazer em um aruqivo
				(informacoes da linha n+2 ate final do arquivo) 
		*/
		void adiciona_operacao_arquivo(char*);
		/**Método que percorre a lista de operacoes sobre os arquivos
		e as executa se possível (processo que quer fazer a operacao
		existe)

			@param std::deque<Processo>: lista de processos que o 
			sistema executou

		**/
		void executa_operacoes_sobre_arquivo(std::deque<Processo>);

		/**
		*	Metodo para imprimir os valores atuais das variaveis:
		* total_blocos_disco, n e para percorrrer as listas de arquivos
		*gravadas e operacoes com arquivos (imprimindo o conteudo de
		*cada um dos elementos da lista)  
		**/
		void imprime_informacoes_disco();
		//Inicio da declaracao dos getters
		int get_total_blocos_disco();
		int get_n();
		//Fim da declaracao dos getters

//Fim da definicao dos metodos da classe
};

#endif