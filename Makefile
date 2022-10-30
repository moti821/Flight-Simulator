CC = g++
TARGET = main.o client.o server.o lexer.o command.o parser.o data_base.o tools.o
CFLAGS = -pthread

main:	$(TARGET)
		$(CC) -o main $(TARGET) $(CFLAGS)

main.o: main.cpp parser.cpp parser.hpp
		$(CC) -Wall -c main.cpp

parser.o: parser.cpp parser.hpp lexer.cpp lexer.hpp command.cpp command.hpp
		$(CC) -Wall -c parser.cpp

lexer.o: lexer.cpp lexer.hpp tools.cpp tools.hpp
		$(CC) -Wall -c lexer.cpp 

command.o: command.cpp command.hpp lexer.cpp lexer.hpp parser.cpp parser.hpp server.cpp server.hpp client.cpp client.hpp data_base.cpp data_base.hpp shunting_yard.cpp
		$(CC) -Wall -c command.cpp $(CFLAGS)

server.o: server.cpp server.hpp tools.cpp tools.hpp data_base.cpp data_base.hpp 
		$(CC) -Wall -c server.cpp $(CFLAGS)

tools.o: tools.cpp tools.hpp
		$(CC) -Wall -c tools.cpp

client.o: client.cpp client.hpp 
		$(CC) -Wall -c client.cpp

data_base.o: data_base.cpp data_base.hpp
		$(CC) -Wall -c data_base.cpp

clean:
		rm *.o main
