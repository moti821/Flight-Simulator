CC = g++
OBJS = main.cpp client.cpp server.cpp lexer.cpp command.cpp parser.cpp data_base.cpp
CFLAGS = -pthread

main:	$(OBJS)
		$(CC) -o main $(OBJS) $(CFLAGS)
