SOURCES = src/Processos/processo.cpp src/arquivos.cpp src/so.cpp

SO: 
	@ g++ -Wall -o so $(SOURCES) -I. 