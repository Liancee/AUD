CC = gcc -Wall
PRG = ueb01
OBJ = ueb01.o tools.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^

ueb11.o: ueb01.c tools.h
	$(CC) -c $<

tools.o: tools.c tools.h
	$(CC) -c $<

clean:
	rm -f $(OBJ) $(PRG)

run:
	./$(PRG)

all: clean $(PRG) run
