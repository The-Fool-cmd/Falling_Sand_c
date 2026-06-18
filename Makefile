FLAGS = -Wall
CC = clang

simulation.bin: simulation.o
	$(CC) $(FLAGS) simulation.o -o simulation.bin -lncurses

simulation.o: simulation.c
	$(CC) $(FLAGS) -c simulation.c

clean:
	rm *.o *.bin
