CC = g++
TARGET = main.o client.o server.o lexer.o command.o parser.o data_base.o tools.o
CFLAGS = -pthread

main:	$(TARGET)
		$(CC) -o main $(TARGET) $(CFLAGS)

main.o: main.cpp parser.cpp parser.hpp
		$(CC) -std=c++17 -Wall -pedantic -c main.cpp

parser.o: parser.cpp parser.hpp lexer.cpp lexer.hpp command.cpp command.hpp
		$(CC) -std=c++17 -Wall -pedantic -c parser.cpp

lexer.o: lexer.cpp lexer.hpp tools.cpp tools.hpp
		$(CC) -std=c++17 -Wall -pedantic -c lexer.cpp 

command.o: command.cpp command.hpp lexer.cpp lexer.hpp parser.cpp parser.hpp server.cpp server.hpp client.cpp client.hpp data_base.cpp data_base.hpp shunting_yard.cpp
		$(CC) -std=c++17 -Wall -pedantic -c command.cpp $(CFLAGS)

server.o: server.cpp server.hpp tools.cpp tools.hpp data_base.cpp data_base.hpp 
		$(CC) -std=c++17 -Wall -pedantic -c server.cpp $(CFLAGS)

tools.o: tools.cpp tools.hpp
		$(CC) -std=c++17 -Wall -pedantic -c tools.cpp

client.o: client.cpp client.hpp 
		$(CC) -std=c++17 -Wall -pedantic -c client.cpp

data_base.o: data_base.cpp data_base.hpp
		$(CC) -std=c++17 -Wall -pedantic -c data_base.cpp

clean:
		rm *.o main
