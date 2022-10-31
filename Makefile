CC = g++
TARGET = main.o client.o DBserver.o lexer.o command.o parser.o symbol_table.o tools.o
CFLAGS = -std=c++17 -Wall -pedantic -c

main:	$(TARGET)
		$(CC) -o main $(TARGET) -pthread

main.o: main.cpp parser.cpp
		$(CC)  $(CFLAGS) main.cpp

parser.o: parser.cpp lexer.cpp command.cpp
		$(CC) $(CFLAGS) parser.cpp

lexer.o: lexer.cpp tools.cpp
		$(CC) $(CFLAGS) lexer.cpp 

command.o: command.cpp lexer.cpp parser.cpp DBserver.cpp client.cpp symbol_table.cpp shunting_yard.cpp
		$(CC) $(CFLAGS) command.cpp -pthread

DBserver.o: DBserver.cpp tools.cpp symbol_table.cpp 
		$(CC) $(CFLAGS) DBserver.cpp -pthread

tools.o: tools.cpp
		$(CC) $(CFLAGS) tools.cpp

client.o: client.cpp
		$(CC) $(CFLAGS) client.cpp

symbol_table.o: symbol_table.cpp
		$(CC) $(CFLAGS) symbol_table.cpp

clean:
		rm *.o main
