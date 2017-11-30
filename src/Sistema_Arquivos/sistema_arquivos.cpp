#include "../../include/Sistema_Arquivos/sistema_arquivos.hpp"
#define livre '0'
#define tempo_real 0 //processos de tempo real tem prioridade 0
sistema_arquivos::sistema_arquivos(){//construtor sem argumentos de entrada permite nao precisar passar todos os argumentos da classe de uma vez	
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
	//for(i=bloco_inicial;i<(bloco_inicial+num_blocos_gravados) && i<this->total_blocos_disco;i++){//possivel protecao contra usuario 
	for(i=bloco_inicial;i<bloco_inicial+num_blocos_gravados;i++){//para debug
		this->ocupacao_memoria[i] = nome_arq;
	}
}
void sistema_arquivos::executa_operacoes_sobre_arquivo(std::vector<Processo> lista_processos){
	int indice_operacao=0;
	printf("Sistema de arquivos =>\n");
	while(!this->lista_operacoes_arquivo.empty()){
		operacao_arquivo operacao_atual = this->lista_operacoes_arquivo.front();
		indice_operacao++;
		printf("Operacao %d =>",indice_operacao);
		if(operacao_atual.get_pid()<(int)lista_processos.size()){
			//os PIDs das listas de operacoes e processos sao indices 
			//de vetores. So faz sentido executar uma operacao no arquivo
			//se o processo existe
			if(this->lista_operacoes_arquivo.front().desja_criar()){
				this->tenta_criar_arquivo();
			}else{
				this->tenta_deletar_arquivo(lista_processos);
			}
		}else{
			printf("Falha\n");
			printf("Nao existe o processo.\n\n");			
		}
		//apos ter executado a operacao, retira ela da lista 		
		this->lista_operacoes_arquivo.erase(this->lista_operacoes_arquivo.begin());
	}
}
void sistema_arquivos::tenta_deletar_arquivo(std::vector<Processo> lista_processos){
	operacao_arquivo operacao_para_deletar = this->lista_operacoes_arquivo.front();
	int pid_processo=operacao_para_deletar.get_pid();//pid do processo que quer deletar o arquivo
	char nome_arq = operacao_para_deletar.get_nome_arquivo();//nome do arquivo a ser deletado 
	if(this->existe_arquivo_gravado_com_mesmo_nome(nome_arq) ){
		if(lista_processos[pid_processo].get_prioridade()==tempo_real){//se o processo for de tempo real
			this->deleta_arquivo(nome_arq,operacao_para_deletar);
		}else if(this->processo_criou_arquivo(pid_processo,nome_arq) ){//se for de usuario e tiver criado o arquivo
			this->deleta_arquivo(nome_arq,operacao_para_deletar);
		}else{//se for de usuario e nao tiver criado o arquivo
			printf("Falha\n");
			printf("O proceso de usuario %d nao criou o arquivo %c e nem tem permissao para o deletar\n\n",pid_processo,nome_arq );
		}
	}else{// se nao existe o arquivo a ser deletado, somente informamos o fato para o usuario
		printf("Nenhuma operacao realizada\n");
		printf("O arquivo %c a ser deletado nao existe\n\n",nome_arq );
	}
}
bool sistema_arquivos::processo_criou_arquivo(int pid_processo, char nome_arq){
	int i;//indice_arquivos_gravdos
	for(i=0;i<(int)this->lista_arquivos_gravados.size();i++){
		if(	(this->lista_arquivos_gravados[i].get_nome_arquivo()==nome_arq)
		 	&& 
		 	(this->lista_arquivos_gravados[i].get_pid_criador()==pid_processo)
		  ){
			return true;
		}
	}
	return false;
}
void sistema_arquivos::deleta_arquivo(char nome_arq, operacao_arquivo operacao_para_deletar){
	arquivo_gravado arquivo_para_deletar = this->procura_arquivo_a_ser_deletado(nome_arq);
	int bloco_inicial = arquivo_para_deletar.get_num_primeiro_bloco();
	int qte_blocos=arquivo_para_deletar.get_blocos_ocupados();//informacoes de blocos do arquivo a serem deletados 
	int pid_processo=operacao_para_deletar.get_pid();//pid do processo que quer deletar o arquivo
	this->escreve_no_disco(bloco_inicial,qte_blocos,livre);
	printf("Sucesso\n");
	printf("O processo %d deletou o arquivo %c\n\n",pid_processo,nome_arq );
}
//metodo tem que ser chamado apos conferir se o arquivo a ser deletado existe
arquivo_gravado sistema_arquivos::procura_arquivo_a_ser_deletado(char nome_arq){
	int i;
	for(i=0;i<(int)this->lista_arquivos_gravados.size();i++){
		if(this->lista_arquivos_gravados[i].get_nome_arquivo() == nome_arq){
			return this->lista_arquivos_gravados[i];
		}
	}
	printf("Arquivo a ser deletado nao encontrado!\n");
	return this->lista_arquivos_gravados[0];//para evitar seg faults
}
void sistema_arquivos::tenta_criar_arquivo(){
	operacao_arquivo operacao_para_criar = this->lista_operacoes_arquivo.front();
	int posicao_inicial_para_gravar_arquivo;
	if(!this->existe_arquivo_gravado_com_mesmo_nome(operacao_para_criar.get_nome_arquivo())){
		if(operacao_para_criar.get_numero_blocos()<=this->total_blocos_disco){
			//se o tamanho do arquivo a ser criado for menor que o tamanho
			//total do disco, tentamos procurar por espacos vazios contiguos
			posicao_inicial_para_gravar_arquivo = this->busca_espacos_adjacentes();
			if(posicao_inicial_para_gravar_arquivo>=0){//achou um espaco continuo que caiba o arquivo
				this->escreve_no_disco( posicao_inicial_para_gravar_arquivo,
										operacao_para_criar.get_numero_blocos(),
									    operacao_para_criar.get_nome_arquivo()
									  );
				this->salva_processo_criador_do_arquivo(operacao_para_criar,posicao_inicial_para_gravar_arquivo);
				this->imprime_mensagem_sucesso_criacao_arquivo(operacao_para_criar,posicao_inicial_para_gravar_arquivo);
			}else{
				printf("Falha\n");
				printf("O processo %d nao pode criar o arquivo %c (nao ha espaco)\n\n",operacao_para_criar.get_pid(),operacao_para_criar.get_nome_arquivo() );
			}
		}else{
			printf("Falha\n");
			printf("O processo %d nao pode criar o arquivo %c (tamanho do arquivo>tamanho disco)\n\n",operacao_para_criar.get_pid(),operacao_para_criar.get_nome_arquivo() );
		}
	}else{
		printf("Falha\n");
		printf("Ja existe um arquivo de nome %c \n\n",operacao_para_criar.get_nome_arquivo() );
	}
}
void sistema_arquivos::salva_processo_criador_do_arquivo(operacao_arquivo operacao_para_criar, int bloco_inicial){
	//operacao_para_criar eh parte da descricao das operacoes sobre o arquivo
	//enquanto que dados_a_serem_gravados eh parte da descricao sobre
	//os arquivos efetivamente gravados no disco. Os dados a serem gravados
	// dizem respeito as informacoes que facilitam deletar o arquivo
	arquivo_gravado dados_a_serem_gravados;
	dados_a_serem_gravados.set_nome_arquivo(operacao_para_criar.get_nome_arquivo());
	dados_a_serem_gravados.set_pid_criador(operacao_para_criar.get_pid());
	dados_a_serem_gravados.set_num_primeiro_bloco(bloco_inicial);
	dados_a_serem_gravados.set_blocos_ocupados(operacao_para_criar.get_numero_blocos());
	this->lista_arquivos_gravados.push_back(dados_a_serem_gravados);//guarda informacoes uteis para deletar um arquivo, caso necessario
}
void sistema_arquivos::imprime_mensagem_sucesso_criacao_arquivo(operacao_arquivo operacao_para_criar, int posicao_inicial_para_gravar_arquivo){
	printf("Sucesso\n");
	printf("O processo %d criou o arquivo %c (blocos %d a %d)\n\n",
				operacao_para_criar.get_pid(),
				operacao_para_criar.get_nome_arquivo(),
				posicao_inicial_para_gravar_arquivo,
				(posicao_inicial_para_gravar_arquivo+operacao_para_criar.get_numero_blocos()-1)
		  );
} 
bool sistema_arquivos::existe_arquivo_gravado_com_mesmo_nome(char nome){
	int bloco;
	for(bloco=0;bloco<this->total_blocos_disco;bloco++ ){
		if(this->ocupacao_memoria[bloco]==nome){
			return true;//se achou qualquer bloco que possui um arquivo com nome especificado
		}
	}
	return false;//se chegou ate esse ponto eh pq nao existe arquivo gravado com o nome especificado
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
					}else if(this->ocupacao_memoria[blocos_adjacentes]==livre){
						num_blocos_adjacentes_livres++;
					}else if(num_blocos_adjacentes_livres<num_blocos_para_criar){
						//nao achou a quantidade certa de blocos adjacentes livres
						bloco_inicial = blocos_adjacentes;
						break;
					}
					
				}//for(blocos_adjacentes...)
		}//for(bloco_inicial...)
	return -1;//caso nao achar espaco
}
void sistema_arquivos::imprime_informacoes_disco(){
	int i;//itera sobre as listas de operacoes e de arquivos gravados no disco, alem da estrutura para simualr o disco
	printf("Total de blocos do disco: %d\n",this->total_blocos_disco);
	//printf("n: %d \n",this->n);
	printf("Mapa de ocupação do disco:\n");
	for(i=0;i<this->total_blocos_disco;i++){//itera sobre a estrutura de simulacao do disco
		printf("|%c|",this->ocupacao_memoria[i]);
	}
	printf("\n");
}
