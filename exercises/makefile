CC = gcc -Wall
PRG = main
OBJ = main.o menu.o calendar.o tools.o datetime.o

$(PRG): $(OBJ)
	$(CC) -o $@ $^

main.o: main.c menu.h calendar.h tools.h
	$(CC) -c $<

menu.o: menu.c menu.h tools.h
	$(CC) -c $<

calendar.o: calendar.c calendar.h tools.h datastructure.h datetime.h escapesequenzen.h
	$(CC) -c $<

datetime.o: datetime.c datetime.h tools.h datastructure.h escapesequenzen.h
	$(CC) -c $<

tools.o: tools.c tools.h datetime.h escapesequenzen.h
	$(CC) -c $<

clean:
	rm -f $(OBJ) $(PRG)

run:
	./$(PRG)

all: clean $(PRG) run
