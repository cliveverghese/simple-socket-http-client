main: socket_connection.o main.o 
	cc socket_connection.o main.o phraser.o -o main
main.o: main.c
			cc -c main.c -o main.o
socket_connection.o: socket_connection.c phraser.o
			cc -c socket_connection.c phraser.o -o socket_connection.o
phraser.o: phraser.c
	cc -c phraser.c -o phraser.o
