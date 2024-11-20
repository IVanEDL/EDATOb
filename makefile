all: main.o empresa.o listaOrdenes.o personas.o
	g++ -o main main.o empresa.o listaOrdenes.o personas.o
main.o: main.c
	g++ -c main.c
empresa.o: empresa.h empresa.c
	g++ -c empresa.c
listaOrdenes.o:
	g++ -c listaOrdenes.c
personas.o:
	g++ -c personas.c
clean:
	rm *.o
	rm main

