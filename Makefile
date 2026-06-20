FLAGS = -Wall
CC = clang

program.bin: master.o simulation.o tui.o
	$(CC) $(FLAGS) simulation.o tui.o master.o -o program.bin -lncurses

master.o: master.c
	$(CC) $(FLAGS) -c master.c

simulation.o: simulation.c
	$(CC) $(FLAGS) -c simulation.c

tui.o: tui.c
	$(CC) $(FLAGS) -c tui.c
clean:
	rm *.o *.bin
