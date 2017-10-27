SOURCES = src/Processos/processo.cpp src/arquivos.cpp src/modulo_filas.cpp src/so.cpp src/Memoria.cpp

SO: 
	@ g++ -Wall -o so $(SOURCES) -I. 
