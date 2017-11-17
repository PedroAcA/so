#include "../../include/Sistema_Arquivos/sistema_arquivos.hpp"
#define livre '0'
sistema_arquivos::sistema_arquivos(){//construtor sem argumentos de entrada
//permite nao precisar passar todos os argumentos da classe de uma vez
//Obs.:processos de tempo real tem prioridade 0
}
void sistema_arquivos::set_total_blocos_disco(int total_blocos){
	this->total_blocos_disco = total_blocos;
	std::vector<char> config_inicial_disco(this->total_blocos_disco,'0');//cria um vetor de x posicaoes todas contendo '0'
	this->ocupacao_memoria=config_inicial_disco;//copia a configuracao inicial do disco para o mapa de ocupacao da memoria(disco)
}

void sistema_arquivos::set_n(int n){
	this->n = n;
}
void sistema_arquivos::adiciona_arquivo_gravado(char* informacao_arquivo){
	arquivo_gravado novo_arquivo_disco;
	novo_arquivo_disco.insere_informacoes_lidas(informacao_arquivo);
	this->escreve_no_disco(	novo_arquivo_disco.get_num_primeiro_bloco(),
								novo_arquivo_disco.get_blocos_ocupados(),
								novo_arquivo_disco.get_nome_arquivo()
							);
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
//escreve na estrutura que simula o disco (ocupacao_memoria)
void sistema_arquivos::escreve_no_disco(int bloco_inicial, int num_blocos_gravados,char nome_arq){ 
	int i;
	for(i=bloco_inicial;i<bloco_inicial+num_blocos_gravados;i++){
		this->ocupacao_memoria[i] = nome_arq;
	}
}
void sistema_arquivos::executa_operacoes_sobre_arquivo(std::vector<processo> lista_processos){
	int indice_operacao=0;
	while(!this->lista_operacoes_arquivo.empty()){
		operacao_arquivo operacao_atual = this->lista_operacoes_arquivo.front();
		indice_operacao++;
		printf("Operacao %d =>",indice_operacao);
		if(operacao_atual.get_pid()<(int)lista_processos.size()){
			//os PIDs das listas de operacoes e processos sao indices 
			//de vetores. So faz sentido executar uma operacao no arquivo
			//se o processo existe
			if(this->lista_operacoes_arquivo.front().desja_criar()){
				//operacao criar arquivo
				//printf("Requisicao para criar arquivo\n");
				this->tenta_criar_arquivo(lista_processos);
			}else{
				//operacao deletar arquivo
				printf("Requisicao para deletar arquivo\n");
			}
		}else{
			printf("Falha\n");
			printf("Nao existe o processo.\n\n");			
		}
		//apos ter executado a operaca, retira ela da lista 		
		this->lista_operacoes_arquivo.erase(this->lista_operacoes_arquivo.begin());
	}
}
void sistema_arquivos::tenta_criar_arquivo(std::vector<processo> lista_processos){
	operacao_arquivo arquivo_para_criar = this->lista_operacoes_arquivo.front();
	int posicao_inicial_para_gravar_arquivo;
	if(arquivo_para_criar.get_numero_blocos()<=this->total_blocos_disco){
		//se o tamanho do arquivo a ser criado for menor que o tamanho
		//total do disco, tentamos procurar por espacos vazios contiguos
		posicao_inicial_para_gravar_arquivo = this->busca_espacos_adjacentes();
		if(posicao_inicial_para_gravar_arquivo>=0){//achou um espaco continuo que caiba o arquivo
			this->escreve_no_disco(	posicao_inicial_para_gravar_arquivo,
									arquivo_para_criar.get_numero_blocos(),
									arquivo_para_criar.get_nome_arquivo()
								  );	
			printf("Sucesso\n");
			printf("O processo %d criou o arquivo %c (blocos %d a %d)\n\n",
				arquivo_para_criar.get_pid(),
				arquivo_para_criar.get_nome_arquivo(),
				posicao_inicial_para_gravar_arquivo,
				posicao_inicial_para_gravar_arquivo+arquivo_para_criar.get_numero_blocos()
			);

		}else{
			printf("Falha\n");
			printf("O processo %d nao pode criar o arquivo %c (nao ha espaco)\n\n",
				arquivo_para_criar.get_pid(),arquivo_para_criar.get_nome_arquivo()
			);
		}
	}else{
		printf("Falha\n");
		printf("O processo %d nao pode criar o arquivo %c (tamanho do arquivo>tamanho disco)\n\n",
				arquivo_para_criar.get_pid(),arquivo_para_criar.get_nome_arquivo()
			  );
	}
}
int sistema_arquivos::busca_espacos_adjacentes(){
	int bloco_inicial,blocos_adjacentes,num_blocos_adjacentes_livres;
	int num_blocos_para_criar = this->lista_operacoes_arquivo.front().get_numero_blocos();
	for(	bloco_inicial=0;bloco_inicial<(this->total_blocos_disco-num_blocos_para_criar);
			bloco_inicial++ 
		){//vai varrer os blocos do disco por janela do inicio ate a janela
		  //chegar ao fim do disco 
			num_blocos_adjacentes_livres=0;
			for(	blocos_adjacentes=bloco_inicial;
					blocos_adjacentes<this->total_blocos_disco;
					blocos_adjacentes++
				){
					if(num_blocos_adjacentes_livres == num_blocos_para_criar){
						return bloco_inicial;//caso achar espaco
					}
					if(this->ocupacao_memoria[blocos_adjacentes]==livre){
						num_blocos_adjacentes_livres++;
					}else if(num_blocos_adjacentes_livres<num_blocos_para_criar){
						//nao achou a quantidade certa de blocos adjacentes
						// livres
						bloco_inicial = blocos_adjacentes;
						break;
					}
					
				}//for(blocos_adjacentes...)
		}//for(bloco_inicial...)
	return -1;//caso nao achar espaco
}
void sistema_arquivos::imprime_informacoes_disco(){
	int i;//itera sobre as listas de operacoes e de arquivos gravados no disco, alem da estrutura para simualr o disco
	printf("Sistema de arquivos =>\n");
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
	printf("Mapa de ocupação do disco:\n");
	for(i=0;i<this->total_blocos_disco;i++){//itera sobre a estrutura de simulacao do disco
		printf("|%c|",this->ocupacao_memoria[i]);
	}
	printf("\n");
}