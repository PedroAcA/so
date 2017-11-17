#include "../../include/Sistema_Arquivos/arquivo_gravado.hpp"
#include <string.h>//para poder usar as funcoes de 'tokenizar'
arquivo_gravado::arquivo_gravado(){//construtor padrao (default)
}
void arquivo_gravado::insere_informacoes_lidas(char* informacao_arquivo){
//Usar strtok nessa funcao so foi possivel pois a linha que ela recebe 
//como entrada foi gerado em um trecho de codigo que nao estava utilizando 
//strtok naquele momento 
	char *token = strtok(informacao_arquivo,", ");//divide a linha em tokens e pega o primeiro
	this->pid_criador = -1;//pid do criador so eh valido para arquivos que nao estao originalmente em files.txt
	if(token!=NULL){//se existe nome do arquivo na linha
		this->nome_arquivo = token[0];
		token =  strtok(NULL,", ");//pega proximo token
		if(token!=NULL){//se existe numero do primeiro bloco
			this->num_primeiro_bloco = atoi(token);
			token =  strtok(NULL,", ");//pega proximo token
			if(token!=NULL){//se existe total de blocos
				this->blocos_ocupados = atoi(token);
			}else{
				printf("Arquivo do tipo 'files.txt' sem total de blocos gravados no disco!\n");	
			}
		}else{
			printf("Arquivo do tipo 'files.txt' sem numero do primeiro bloco gravado no disco!\n");	
		}
	}else{
		printf("Arquivo do tipo 'files.txt' sem nome de arquivo gravado no disco!\n");
	}
}

int arquivo_gravado::get_num_primeiro_bloco(){
	return this->num_primeiro_bloco;
}

int arquivo_gravado::get_blocos_ocupados(){
	return this->blocos_ocupados;
}

char arquivo_gravado::get_nome_arquivo(){
	return this->nome_arquivo;
}

void arquivo_gravado::imprime_infos_arquivo(){
	printf("\n");
	printf("Nome arquivo gravado: %c \n",this->nome_arquivo);
	printf("Primeiro bloco do arquivo: %d \n",this->num_primeiro_bloco);
	printf("Total blocos ocupados pelo arquivo: %d \n",this->blocos_ocupados);
	printf("\n");
}