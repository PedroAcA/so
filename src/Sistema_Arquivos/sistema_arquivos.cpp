#include "../../include/Sistema_Arquivos/sistema_arquivos.hpp"
sistema_arquivos::sistema_arquivos(){//construtor sem argumentos de entrada
//permite nao precisar passar todos os argumentos da classe de uma vez
}
void sistema_arquivos::set_total_blocos_disco(int total_blocos){
	this->total_blocos_disco = total_blocos;
}

void sistema_arquivos::set_n(int n){
	this->n = n;
}
void sistema_arquivos::adiciona_arquivo_gravado(char* informacao_arquivo){
	arquivo_gravado novo_arquivo_disco;
	novo_arquivo_disco.insere_informacoes_lidas(informacao_arquivo);
	this->lista_arquivos_gravados.push_back(novo_arquivo_disco);
}
void sistema_arquivos::adiciona_operacao_arquivo(char* informacao_operacao){
	operacao_arquivo nova_operacao;
	nova_operacao.insere_informacoes_lidas(informacao_operacao);
	this->lista_operacoes_arquivo.push_back(nova_operacao);
}

int sistema_arquivos::get_total_blocos_disco(){
	return this->total_blocos_disco;
}

int sistema_arquivos::get_n(){
	return this->n;
}
void sistema_arquivos::imprime_informacoes_disco(){
	int i;//itera sobre as listas de operacoes e de arquivos gravados no disco
	printf("Total de blocos do disco: %d\n",this->total_blocos_disco);
	printf("n: %d \n",this->n);
	printf("\n");
	for(i=0;i<(int)this->lista_arquivos_gravados.size();i++){
		this->lista_arquivos_gravados[i].imprime_infos_arquivo();
	}
	printf("\n");
	for(i=0;i<(int)this->lista_operacoes_arquivo.size();i++){
		this->lista_operacoes_arquivo[i].imprime_infos_operacao();
	}
}