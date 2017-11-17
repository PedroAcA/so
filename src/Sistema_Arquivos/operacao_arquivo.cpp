#include "../../include/Sistema_Arquivos/operacao_arquivo.hpp"
#include <string.h>//para poder usar as funcoes de 'tokenizar'
operacao_arquivo::operacao_arquivo(){//construtor padrao (default)
}
void operacao_arquivo::insere_informacoes_lidas(char* informacao_operacao){
//Usar strtok nessa funcao so foi possivel pois a linha que ela recebe 
//como entrada foi gerado em um trecho de codigo que nao estava utilizando 
//strtok naquele momento 
	char *token = strtok(informacao_operacao,", ");//divide a linha em tokens e pega o primeiro
	if(token!=NULL){//se existe PID do processo que vai realizar operacao
		this->pid = atoi(token);
		token =  strtok(NULL,", ");//pega proximo token
		if(token!=NULL){//se existe codigo da operacao
			this->codigo_operacao = atoi(token);
			token =  strtok(NULL,", ");//pega proximo token
			if(token!=NULL){//se existe nome do arquivo
				this->nome_arquivo = token[0];
				if(this->codigo_operacao==criar_arquivo){
					token =  strtok(NULL,", ");//pega proximo token
					if(token!=NULL){//se a operacao eh criar arquivo e existe numero de blocos a serem ocupados
						this->numero_blocos = atoi(token);
					}else{
						printf("Arquivo do tipo 'files.txt' nao especificou numero de blocos a serem ocupados!\n");
					}
				}
			}else{
				printf("Arquivo do tipo 'files.txt' sem nome do arquivo para realizar operacao!\n");	
			}
		}else{
			printf("Arquivo do tipo 'files.txt' sem codigo da operacao!\n");	
		}
	}else{
		printf("Arquivo do tipo 'files.txt' sem PID do processo que vai realizar operacao!\n");
	}
}

int operacao_arquivo::get_pid(){
	return this->pid;
}

bool operacao_arquivo::desja_criar(){//vai indiicar se a operacao eh criar arquivo
	return (this->codigo_operacao==criar_arquivo);
}
int operacao_arquivo::get_numero_blocos(){
	return this->numero_blocos;
}

char operacao_arquivo::get_nome_arquivo(){
	return this->nome_arquivo;
}

void operacao_arquivo::imprime_infos_operacao(){
	printf("\n");
	printf("PID do processo que vai fazer operacao: %d \n",this->pid );
	printf("Codigo operacao: %d \n",this->codigo_operacao);
	printf("Nome arquivo para fazer operacao: %c \n",this->nome_arquivo);
	if(this->codigo_operacao==criar_arquivo)
		printf("Numero de blocos a serem criados: %d \n",this->numero_blocos);
	printf("\n");
}