SOURCES_1 = src/Processos/processo.cpp src/arquivos.cpp src/modulo_filas.cpp src/so.cpp src/Memoria.cpp
#sources da gerencia de arquivos
SOURCES_arquivos =  src/Sistema_Arquivos/arquivo_gravado.cpp src/Sistema_Arquivos/operacao_arquivo.cpp src/Sistema_Arquivos/sistema_arquivos.cpp
#todos os soruces combinados (exemplo extraido de https://sites.google.com/site/michaelsafyan/software-engineering/how-to-write-a-makefile em 15/11/2017)
SOURCES = $(SOURCES_1) $(SOURCES_arquivos)
SO: 
	@ g++ -Wall -o so $(SOURCES) -I. 
