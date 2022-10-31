CC = g++
TARGET = main.o client.o server.o lexer.o command.o parser.o data_base.o tools.o
CFLAGS = -std=c++17 -Wall -pedantic -c

main:	$(TARGET)
		$(CC) -o main $(TARGET) -pthread

main.o: main.cpp parser.cpp
		$(CC)  $(CFLAGS) main.cpp

parser.o: parser.cpp lexer.cpp command.cpp
		$(CC) $(CFLAGS) parser.cpp

lexer.o: lexer.cpp tools.cpp
		$(CC) $(CFLAGS) lexer.cpp 

command.o: command.cpp lexer.cpp parser.cpp server.cpp client.cpp data_base.cpp shunting_yard.cpp
		$(CC) $(CFLAGS) command.cpp -pthread

server.o: server.cpp tools.cpp data_base.cpp 
		$(CC) $(CFLAGS) server.cpp -pthread

tools.o: tools.cpp
		$(CC) $(CFLAGS) tools.cpp

client.o: client.cpp
		$(CC) $(CFLAGS) client.cpp

data_base.o: data_base.cpp
		$(CC) $(CFLAGS) data_base.cpp

clean:
		rm *.o main
