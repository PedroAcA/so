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


	void Escalonador::verificaChegadaProcessos(){

		for(unsigned int i=0; i<this->processosFuturos.size(); i++){	
			if(this->processosFuturos[i].get_tempo_inicializacao() <= this->Tempo){
				if(alocaMemoria(processosFuturos[i].get_PID())){
					admiteProcesso(i);
					i--;
				}
				else std::cout<<"NAO FOI POSSIVEL ALOCAR MEMORIA PARA O PROCESSO "<< processosFuturos[i].get_PID()<<"\n";
			}
		}

	}

	void Escalonador::admiteProcesso(int i){

		this->processosFuturos[i].set_tempo_rodando(0);
		this->filasDeProcessos.insereProcesso(processosFuturos[i]);
		this->processosRodando[processosFuturos[i].get_PID()] = processosFuturos[i];
		this->processosFuturos.erase(processosFuturos.begin() + i);

	}



	bool Escalonador::alocaMemoria(int pid){
		if(processosRodando[pid].get_prioridade()==0)
			return Memoria::aloca_tempo_real(&processosRodando[pid], INICIO_TEMPO_REAL);
		
		return Memoria::aloca_usuario(&processosRodando[pid],INICIO_USUARIO);
		
	}

	void Escalonador::desalocaMemoria(int pid){
		if(processosRodando[pid].get_prioridade()==0)
			return Memoria::desaloca_tempo_real(&processosRodando[pid]);
		
		return Memoria::desaloca_usuario(&processosRodando[pid]);
		
	}




	bool Escalonador::alocaRecursos(int pid)
	{
	
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

	

	void Escalonador::rodaProcessos()
	{
		int pid;	
		while(!processosFuturos.empty() || !processosRodando.empty()){
			
			Escalonador::verificaChegadaProcessos();

			if( CPU_livre && filasDeProcessos.existe_processo_para_executar()){


				if(filasDeProcessos.existe_processo_para_executar_fila0()){
					pid = filasDeProcessos.retira_processo_fila0();	
					CPU_livre=false;	
				}

				else if(filasDeProcessos.existe_processo_para_executar_fila1()){
					pid = filasDeProcessos.retira_processo_fila1();
					CPU_livre=false;
				}
				else if(filasDeProcessos.existe_processo_para_executar_fila2()){
					pid = filasDeProcessos.retira_processo_fila2();
					CPU_livre=false;
					
				}
				else if(filasDeProcessos.existe_processo_para_executar_fila3()){
					pid = filasDeProcessos.retira_processo_fila3();
					CPU_livre=false;
				}

				if(pidExec!=pid)
					std::cout<< "\nprocess " << pid << "=>\n";
				pidExec=pid;
			}

			//imprimeEstado();
			//std::cout<<"Rodando..: " << pidExec << "\n";
			
			
			if(!CPU_livre){
				executaProcessoCPU();
				retiraProcessoCPU();
			}	
			
			this->Tempo++;
			if(Tempo>50) break;

		}
				
		
	} 

	void Escalonador::executaProcessoCPU(){

		//Primeira Execução?
		if(processosRodando[pidExec].get_tempo_rodando()==0){


			if(!alocaRecursos(pidExec)){
				std::cout<<"P"<< pidExec << " Blocked\n";
				CPU_livre=true;
				//pidExec=0; 
				return;
			}

			std::cout<<"P"<<pidExec<<" STARTED\n";
			
		}

		processosRodando[pidExec].set_tempo_rodando(processosRodando[pidExec].tempo_rodando + 1);
		std::cout<<"P"<<processosRodando[pidExec].get_PID()<<" instruction "<<processosRodando[pidExec].get_tempo_rodando()<< "\n";

		

	}

	void Escalonador::retiraProcessoCPU(){

		if(/*pidExec==0*/CPU_livre) return;

		if(processosRodando[pidExec].get_tempo_rodando()==processosRodando[pidExec].get_tempo_processador()){
			std::cout<<"P"<<processosRodando[pidExec].get_PID()<< " return SIGINT\n";
			mataProcesso(processosRodando[pidExec].get_PID());
			std::cout<<"P"<<pidExec<<" TERMINATED\n";
			//pidExec=0;
			CPU_livre=true;
			return;
		}

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

			//pidExec=0;
			return;
		}
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


















