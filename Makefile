FLAGS = -Wall
CC = clang

program.bin: simulation.o tui.o
	$(CC) $(FLAGS) simulation.o tui.o -o program.bin -lncurses

simulation.o: simulation.c
	$(CC) $(FLAGS) -c simulation.c

tui.o: tui.c
	$(CC) $(FLAGS) -c tui.c
clean:
	rm *.o *.bin
