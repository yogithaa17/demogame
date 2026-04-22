CC=gcc
CFLAGS=-fPIC
LIBS=-lncurses

all:game game_shared

#final executable
game:main.o game.c libgame.a
	$(CC) main.o -o game -L. -lgame $(LIBS)

#compile main
main.o:main.c game.h
	$(CC) $(CFLAGS) -c main.c

#compile object file 
game.o:game.c game.h
	$(CC) $(CFLAGS) -c game.c

#static lib
libgame.a:game.o
	ar rcs libgame.a game.o

#shared lib
libgame.so:game.o
	$(CC) -shared -o libgame.so game.o

#build with shared lib
game_shared:main.o libgame.so
	$(CC) main.o -o game_shared -L. -lgame $(LIBS)
	
clean:
	rm -f *.o *.a *.so game game_shared
