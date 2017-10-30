//Classe para implemetar os metodos definidos em arquivos.hpp
//arquivos.cpp nao eh thread safe! (pois usa strktok e variaveis de arquivos.hpp
//sao escritas sem mutexes)

#include "../include/arquivos.hpp"
	arquivos::arquivos(){

	}
	//Na versao incial, le_arquivos so le processes.txt (TODO:implementar
	//leitura de files.txt)

/*Argumentos esperados para le_arquivos(int argc,char** argv) (os quais sao passados primeiramente para a main via terminal)
	argc = 2 (versao atual) ou 3(versao que le o arquivo files.txt)
	argv[0] = ./nome_do_executavel
	argv[1] = caminho relativo do executavel ate o arquivo de processos (no formato txt)
	argv[2] = caminho relativo do executavel ate o arquivo de configuracoes do disco (no formato txt)
*/
	void arquivos::le_arquivos(int argc,char** argv){//argumentos argc e argv da main
		//argc contem 1 (nome do prgrama) + numero de elementos passados por terminal
		// argv contem o nome do programa chamado + elementos passados por terminal
		FILE *arq_processos,*arq_disco;// ponteiros para contem os arquivos abertos
		if(argc==2){// nome do progrmaa + arquivo de processos
			if(this->arquivo_contem_extensao_txt(argv) ){
				arq_processos = fopen(argv[1],"r");
				if(arq_processos!=NULL){
					this->extrai_informacoes_processos(arq_processos);
					fclose(arq_processos);
				}else{//arquivo de processos nao pode ser aberto
					printf("Nao foi possivel abrir o arquivo de processos!\n Por favor, tente novamente! \n");
					exit(4);
				}
			}else{
				printf("Um dos arquivos nao possui a extensao .txt!\n Por favor, tente novamente! \n");
				exit(4);
			}
		}else{//so tem o nome do programa (logo, nao tem arquivos para abrir)
			printf("Caminho relativo dos arquivos nao especificado!\n Por favor, tente novamente! \n");
			exit(3);
		}
	}
	//Nao foi utilizada a funcao strstr (da biblioteca string.h) para identificar
	//a eextensao pois a strstr poderia retornar que um arquivo de nome proc.txtess
	//seria valido por conter a string ".txt" 
	bool arquivos::arquivo_contem_extensao_txt(char** argv){
		char txt[] = ".txt";
		int maior_indice_extensao_txt = (int)strlen(txt) -1;// pois os indices vao de 0 ..(N-1)
		//argv[1] argv 1 contem o caminho ate o arquivo processes.txt
		int maior_indice_arquivo_processos = (int)strlen(argv[1]) -1;// pois os indices vao de 0 ..(N-1)
		int i;//indice para iterar sobre a parte relativa a extensao
		for(i=0;i<=maior_indice_extensao_txt;i++){
			/*compara caracter a caracter as strings txt e a regiao que deve
			conter a extensao no argumento passado pela linha de comando. Se
			algum desses caracteres nao for igual, entao a extensao nao eh .txt
			Faz a comparacao do final da string para o inicio (entao compara
			t,x,t,.)
			*/
			if(txt[maior_indice_extensao_txt - i] != argv[1][maior_indice_arquivo_processos-i] )
				return false;
		}
		return true;//se chegou a esse ponto, entao a extensao passada em argv eh .txt
	}
	void arquivos::extrai_informacoes_processos(FILE* arq_processos){//ponteiro para arquivos de processo
		char *linha_atual,*tokens;
		int tempo_inicializacao, tempo_processador;
		bool requisicao_impressora,requisicao_scanner,requisicao_modem;
		processo processo_atual;
		while(!feof(arq_processos)){
			linha_atual = le_proxima_linha(arq_processos);
			if(linha_atual[0]!='\0'){//So analisa a linha se ela nao esta vazia
				//primeira chamada ao strtok separa a string em tokens 
				//e ja retorna o primeiro token 
				tokens = strtok(linha_atual,", ");//pois as informacoes dos processos sao separadas por virgulas e espacos
				//Inicio da atribuicao dos campos do processo (para ver a ordem das informacoes, ver arquivo formato_arquivos_entrada.txt)
				tempo_inicializacao = atoi(tokens);
				
				tokens = this->proximo_token();
				processo_atual.set_prioridade(atoi(tokens));

				tokens = this->proximo_token();
				tempo_processador= atoi(tokens);
				

				tokens = this->proximo_token();
				processo_atual.set_blocos_memoria(atoi(tokens));

				tokens = this->proximo_token();
				requisicao_impressora = (bool)atoi(tokens);//valores bool sao armazenados como 0 ou 1

				tokens = this->proximo_token();
				requisicao_scanner = (bool)atoi(tokens);//valores bool sao armazenados como 0 ou 1

				tokens = this->proximo_token();
				requisicao_modem = (bool)atoi(tokens);//valores bool sao armazenados como 0 ou 1

				tokens = this->proximo_token();
				processo_atual.set_codigo_disco(atoi(tokens));
		
				processo_atual.set_tempos(tempo_inicializacao,tempo_processador);
				processo_atual.set_requisicoes(requisicao_impressora,requisicao_scanner,requisicao_modem);
				//Fim da atribuicao dos campos do processo			
				this->lista_processos.push_back(processo_atual);//adicionamos o processo a lista de processos no fim da lista (fim do vetor)
			}//if(linha_atual[0]!='\0')
			free(linha_atual);//pois a funcao le_proxima_linha retorna a linha alocada dinamicamente
		}//while(!feof(arq_processos))
	}//void arquivos::extrai_informacoes_processos(FILE* arq_processos)
	char* arquivos::le_proxima_linha(FILE* arq){
		int i;
   		char c = fgetc(arq);
    	char* linha = (char*)calloc(1,sizeof(char));
    	/*laco percorre cada posicao da string linha (de i =0  incrementando i++)
    	e a cada iteracao le o proximo caracter do arquivo. Se esse caracter for
    	o fim do arquivo ou '\n', ou '\r'(windows) entao encerra o laco. A cada itercao, salva o
    	caracter na string e aloca espaco para receber o proximo caracter*/
    	for(i=0;(c!=EOF && c!='\n' && c!='\r' );i++,c=fgetc(arq) ){
       		linha[i] = c;
       		linha = (char*) realloc(linha,(i+2)*sizeof(char));
    	}
        linha[i] = '\0';
		return linha;
	}
	char* arquivos::proximo_token(){
		return strtok(NULL,", ");
	}
	//Metodo imprime_informacoes_processos() pode ser usado quando
	//alguem quer imprimir todas as informcaoes dos processos lidos do
	//arquivo de forma automatica
	void arquivos::imprime_informacoes_processos(){
		int i;
		for (i = 0; i < (int) this->lista_processos.size(); i++){
			this->lista_processos[i].imprime_infomacoes_processo(i+1);	
		}
	}
	void arquivos::libera_lista_processos(){
		std::cout<<"Liberando lista de aqruivos!"<<std::endl;
		if(!this->lista_processos.empty()){
			this->lista_processos.clear();
		}
		std::cout<<"Lista de aqruivos liberada!"<<std::endl;
	}