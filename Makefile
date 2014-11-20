CC = gcc
OBJ = main.o memalloc.o stats.o nodes.o
FLAGS = -Wall -std=c99 -g -o

memalloc: $(OBJ)
	$(CC) $(OBJ) $(FLAGS) $@

.c.o:
	$(CC) -g -c $<

clean:
	rm *.o memalloc 
