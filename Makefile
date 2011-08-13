main: socket_connection.o main.o
	cc socket_connection.o main.o -o main

main.o: main.c
			cc -c main.c -o main.o
socket_connection.o: socket_connection.c
			cc -c socket_connection.c -o socket_connection.o
