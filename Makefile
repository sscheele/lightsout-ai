OBJS = build/lightboard.o build/main.o
OBJDIR = build
CC = g++
DEBUG = -g
CFLAGS = -Wall -c
LFLAGS = -Wall

main: $(OBJS)
	g++ $(LFLAGS) $(OBJS) -o main
#$@ is the name of the file being generated, $< is the name of the first dependency
$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@