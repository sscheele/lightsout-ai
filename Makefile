OBJS = build/lightboard.o build/main.o
OBJDIR = build
CC = g++
DEBUG = -g
CFLAGS = -Wall -c
LFLAGS = -Wall
OUTFILE = main

main: $(OBJS)
	g++ $(LFLAGS) $(OBJS) -o $(OUTFILE)
#$@ is the name of the file being generated, $< is the name of the first dependency
$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm $(OBJS) $(OUTFILE) 