CC = g++
TARGET = main.o client.o server.o lexer.o command.o parser.o data_base.o tools.o
CFLAGS = -pthread

main:	$(TARGET)
		$(CC) -o main $(TARGET) $(CFLAGS)

main.o: main.cpp parser.cpp parser.hpp
		$(CC) -c main.cpp

parser.o: parser.cpp parser.hpp lexer.cpp lexer.hpp command.cpp command.hpp
		$(CC) -c parser.cpp

lexer.o: lexer.cpp lexer.hpp tools.cpp tools.hpp
		$(CC) -c lexer.cpp 

command.o: command.cpp command.hpp lexer.cpp lexer.hpp parser.cpp parser.hpp server.cpp server.hpp client.cpp client.hpp data_base.cpp data_base.hpp shunting_yard.cpp
		$(CC) -c command.cpp $(CFLAGS)

server.o: server.cpp server.hpp tools.cpp tools.hpp data_base.cpp data_base.hpp 
		$(CC) -c server.cpp $(CFLAGS)

tools.o: tools.cpp tools.hpp
		$(CC) -c tools.cpp

client.o: client.cpp client.hpp 
		$(CC) -c client.cpp

data_base.o: data_base.cpp data_base.hpp
		$(CC) -c data_base.cpp

clean:
		rm *.o main
