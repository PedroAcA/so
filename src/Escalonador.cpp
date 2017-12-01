#include "../include/Escalonador.hpp"
#include "../include/Memoria.hpp"

using namespace std;

	Escalonador::Escalonador()
	{

	}

	void Escalonador::inicializa(std::deque<Processo> listaProcessos, Recursos recursos, Memoria memoria){
		this->processosFuturos = listaProcessos;
		this->recursos = recursos;
		this->memoria = memoria;
		this->Tempo=0;
		this->CPU_livre=true;
	}

	/* Metodo que verifica cronologicamente se chegou um processo (baseado no tempo atual) 
	caso tenha chegado, verifica se existe espaço na memória para o processo. se houver, coloca na fila de processos Rodando.
	Este método também coloca um processo na lista de processos esperando por memória caso a alocação dele seja negada.
	*/
	void Escalonador::verificaChegadaProcessos(){

		for(unsigned int i=0; i<this->processosFuturos.size(); i++){	
			if(this->processosFuturos[i].get_tempo_inicializacao() <= this->Tempo){
				if(alocaMemoria(i)){
					std::cout<<"[t="<<Tempo<<"]"<<"dispatcher==> Processo "<< processosFuturos[i].get_PID()<<": Alocado em memória.\n";
					processosFuturos[i].imprime_informacoes_processo();	
					admiteProcesso(i);
					i--;
				}
				else{
					std::cout<<"[t="<<Tempo<<"]"<<"dispatcher==> Processo "<< processosFuturos[i].get_PID()<<": Não foi possível alocar memória.\n";

					//se for tempo real com mais de 64 blocos, é apagado
					if(processosFuturos[i].prioridade==0 && processosFuturos[i].blocos_em_memoria>64){
						this->processosFuturos.erase(processosFuturos.begin() + i);
						i--;
					}
					//se for de usuario com mais de 960 blocos, é apagado
					else if(processosFuturos[i].blocos_em_memoria>960){
						this->processosFuturos.erase(processosFuturos.begin() + i);
						i--;
					}
					//aqui coloca o processo na lista de processos esperando por memoria
					else{
						processosEsperandoMemoria.push_back(processosFuturos[i]);
						this->processosFuturos.erase(processosFuturos.begin() + i);
						i--;
					}

				} 
			}
		}

	}

	void Escalonador::admiteProcesso(int i){

		this->processosFuturos[i].set_tempo_rodando(0);
		this->filasDeProcessos.insereProcesso(processosFuturos[i]);
		this->processosRodando[processosFuturos[i].get_PID()] = processosFuturos[i];
		this->processosFuturos.erase(processosFuturos.begin() + i);

	}



	bool Escalonador::alocaMemoria(int i){
		if(processosFuturos[i].get_prioridade()==0)
			return memoria.aloca_tempo_real(&processosFuturos[i],INICIO_TEMPO_REAL);
		
		return memoria.aloca_usuario(&processosFuturos[i],INICIO_USUARIO);
		
	}

	void Escalonador::desalocaMemoria(int pid){
		memoria.desaloca_processo(&processosRodando[pid]);
		
		/*quando retira um processo da memoria, devolve todos os processos esperando por memoria
		para a fila de processos futuros, para terem sua alocação verificada novamente.
		*/
		for(unsigned int i=0; i<processosEsperandoMemoria.size(); ++i)
			processosFuturos.push_back(processosEsperandoMemoria[i]);
		processosEsperandoMemoria.clear();

	}




	bool Escalonador::alocaRecursos(int pid)
	{
	
		/*
		Aqui a tentativa sequencial de alocação de recursos. Primeiro impressora, depois scanner e por fim modem.
		*/

		if(processosRodando[pid].requisicao_impressora != 0){
			int impressora = processosRodando[pid].get_requisicao_impressora();

			if(!recursos.solicitaImpressora(&processosRodando[pid])){
				if(impressora==1){
					bloqueadosImp1.push_back(pid);
				}
				else if(impressora==2){
					bloqueadosImp2.push_back(pid);
				}
				return false;
			}
		}

		if(processosRodando[pid].requisicao_scanner)
			if(!recursos.solicitaScanner(&processosRodando[pid])){
				bloqueadosScanner.push_back(pid);
				return false;
			}
		

		if(processosRodando[pid].requisicao_modem)
			if(!recursos.solicitaModem(&processosRodando[pid])){
				bloqueadosModem.push_back(pid);
				return false;
			}

		return true;
	}

	void Escalonador::desalocaRecursos(int pid)
	{

		/* Quando um processo desaloca seus recursos, o escalonador vai nas filas de processos
		bloqueados correspondentes e libera todos os processos.
		*/
		if(processosRodando[pid].detemImpressora !=0){
			desbloqueiaFilaImpressora(processosRodando[pid].detemImpressora);
		}

		if(processosRodando[pid].detemScanner){
			desbloqueiaFilaScanner();
		}

		if(processosRodando[pid].detemModem){
			desbloqueiaFilaModem();
		}
		

		recursos.liberaRecursos(&processosRodando[pid]);
		return;
	}



	void Escalonador::desbloqueiaFilaScanner(){
		for(unsigned int i=0; i<bloqueadosScanner.size(); ++i)
			filasDeProcessos.insereProcesso(processosRodando[bloqueadosScanner[i]]);
		bloqueadosScanner.clear();
	}

	void Escalonador::desbloqueiaFilaModem(){
		for(unsigned int i=0; i<bloqueadosModem.size(); ++i)
			filasDeProcessos.insereProcesso(processosRodando[bloqueadosModem[i]]);
		bloqueadosModem.clear();


	}

	void Escalonador::desbloqueiaFilaImpressora(int imp){

		if(imp==1){

			for(unsigned int i=0; i<bloqueadosImp1.size(); ++i)
				filasDeProcessos.insereProcesso(processosRodando[bloqueadosImp1[i]]);
			bloqueadosImp1.clear();
		}

		if(imp==2){

			for(unsigned int i=0; i<bloqueadosImp2.size(); ++i)
				filasDeProcessos.insereProcesso(processosRodando[bloqueadosImp2[i]]);
			bloqueadosImp2.clear();

		}

	}

	
	/* Todo o funcionamento cronológico do escalonador está contido neste método */
	void Escalonador::rodaProcessos()
	{
		int pidExecAnterior=pidExec;	
		//laço que incrementa o tempo até que os não exista nenhum processo nem rodando nem por vir.
		while(!processosFuturos.empty() || !processosRodando.empty()){
			
			verificaChegadaProcessos();

			if( CPU_livre && filasDeProcessos.existe_processo_para_executar()){

				//Se o cpu está livre, ele varre as filas de maior para menor a procura do proximo
				// processo, quando encontra, coloca na CPU para rodar.

				if(filasDeProcessos.existe_processo_para_executar_fila0()){
					pidExec = filasDeProcessos.retira_processo_fila0();	
					CPU_livre=false;	
				}

				else if(filasDeProcessos.existe_processo_para_executar_fila1()){
					pidExec = filasDeProcessos.retira_processo_fila1();
					CPU_livre=false;
				}
				else if(filasDeProcessos.existe_processo_para_executar_fila2()){
					pidExec = filasDeProcessos.retira_processo_fila2();
					CPU_livre=false;
					
				}
				else if(filasDeProcessos.existe_processo_para_executar_fila3()){
					pidExec = filasDeProcessos.retira_processo_fila3();
					CPU_livre=false;
				}

				if(pidExec!=pidExecAnterior)
					std::cout<<"\n[t="<<Tempo<<"]"<< "process " << pidExecAnterior << "=>\n";
			}

			//imprimeEstado();
			//std::cout<<"Rodando..: " << pidExec << "\n";
			
			//Se os passos anteriores resultaram em uma CPU ocupada, chama os metodos de execução e retirada de processo da CPU
			if(!CPU_livre){
				executaProcessoCPU();
				retiraProcessoCPU();
			}	
			
			this->Tempo++; // incrementa o tempo (laço cronológico)
		}

		std::cout<<"\n";
		filasDeProcessos.destroiFilas();
		processosRodando.clear();
		processosFuturos.clear();
		processosTerminados.clear();
				
		
	} 

	void Escalonador::executaProcessoCPU(){

		// verifica se é a primeira vez que o processo vai pra CPU, se for, solicita todos os recursos.
		if(processosRodando[pidExec].get_tempo_rodando()==0){
			if(!alocaRecursos(pidExec)){
				/*
					Caso os recursos não estejam disponíveis, dentro do proprio metodo alocaRecurso() o processo é colocado na 
					fila de bloqueio correspondente. Resta a este método apenas setar a CPU como livre. 
				*/	
				std::cout<<"[t="<<Tempo<<"]"<<"P"<< pidExec << " Blocked\n";
				CPU_livre=true; 
				return;
			}
			std::cout<<"[t="<<Tempo<<"]"<<"P"<<pidExec<<" STARTED\n";
		}

		//incrementa o atributo tempo_rodando do processo.
		processosRodando[pidExec].set_tempo_rodando(processosRodando[pidExec].tempo_rodando + 1);
		std::cout<<"[t="<<Tempo<<"]"<<"P"<<processosRodando[pidExec].get_PID()<<" instruction "<<processosRodando[pidExec].get_tempo_rodando()<< "\n";		

	}

	void Escalonador::retiraProcessoCPU(){

		if(CPU_livre) return;

		//Se o processo já terminou de rodar, mata o processo e retorna CPU livre.
		if(processosRodando[pidExec].get_tempo_rodando()==processosRodando[pidExec].get_tempo_processador()){
			std::cout<<"[t="<<Tempo<<"]"<<"P"<<processosRodando[pidExec].get_PID()<< " return SIGINT\n";
			mataProcesso(processosRodando[pidExec].get_PID());
			std::cout<<"[t="<<Tempo<<"]"<<"P"<<pidExec<<" TERMINATED\n";
			CPU_livre=true;
			return;
		}

		/*
			Se o processo é de usuario e não terminou de rodar, ele procura a fila correspondente para devolver o processo 
			e depois retorna CPU livre.
		
			Aqui, processo de prioridade 1 se torna 2, de prioridade 2 se torna 3, e de prioridade 3 se torna 1. Isso é feito para evitar starvation
		*/
		if(processosRodando[pidExec].get_prioridade()!=0){
			CPU_livre=true;
			if(processosRodando[pidExec].get_prioridade()==1){
				processosRodando[pidExec].set_prioridade(2);
				filasDeProcessos.insereProcesso(processosRodando[pidExec]);
			}

			else if(processosRodando[pidExec].get_prioridade()==2){
				processosRodando[pidExec].set_prioridade(3);
				filasDeProcessos.insereProcesso(processosRodando[pidExec]);
			}


			else if(processosRodando[pidExec].get_prioridade()==3){
				processosRodando[pidExec].set_prioridade(1);
				filasDeProcessos.insereProcesso(processosRodando[pidExec]);
			}
			return;
		}

		/* Se o processo é de tempo real e não terminou, ele não libera a CPU */
		CPU_livre = false;
		return;

	}


	void Escalonador::mataProcesso(int pid){
		desalocaMemoria(pid);
		desalocaRecursos(pid);
		processosTerminados.push_back(processosRodando[pid]);
		processosRodando.erase(pid);

	}

	


	void Escalonador::imprimeEstado(){

		std::cout<<"\n\nTEMPO: "<< Tempo << "\n";
		std::cout<<"\nProcessos Futuros:";
		for(unsigned int i=0; i<processosFuturos.size(); ++i)
			std::cout<<"\t"<< processosFuturos[i].get_PID();
		std::cout<<"\n";

		filasDeProcessos.imprimeEstado();

		std::cout<<"Lista de Processos Rodando:\n";
		for(map<int,Processo>::const_iterator it = processosRodando.begin(); it != processosRodando.end(); ++it){
			    std::cout << "PID: "<< it->second.PID << " prior:" << it->second.prioridade << " rodou:" << it->second.tempo_rodando
			    << " total:" << it->second.tempo_processador<< "\n";
		}

		std::cout<<"Processos Terminados:";
		for(unsigned int i=0; i<processosTerminados.size(); ++i)
			std::cout<<"\t"<< processosTerminados[i].get_PID();
		std::cout<<"\n";
		std::cout<<"Bloqueados Impressora 1:";
		for(unsigned int i=0; i<bloqueadosImp1.size(); ++i)
			std::cout<<"\t"<< bloqueadosImp1[i];
		std::cout<<"\n";
		std::cout<<"Bloqueados Impressora 2:";
		for(unsigned int i=0; i<bloqueadosImp2.size(); ++i)
			std::cout<<"\t"<< bloqueadosImp2[i];
		std::cout<<"\n";
		std::cout<<"Bloqueados Scanner";
		for(unsigned int i=0; i<bloqueadosScanner.size(); ++i)
			std::cout<<"\t"<< bloqueadosScanner[i];
		std::cout<<"\n";
		std::cout<<"Bloqueados Modem:";
		for(unsigned int i=0; i<bloqueadosModem.size(); ++i)
			std::cout<<"\t"<< bloqueadosModem[i];
		std::cout<<"\n";
		


	}


















