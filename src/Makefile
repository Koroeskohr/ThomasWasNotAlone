CC=gcc
CFLAGS=-Wall -O2 -g 
LIB=-lSDL -lGLU -lGL -lm
EXEC=thomas
SRC= dessinPrimitives.c rectangle.c physics.c player.c windowManager.c main.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

thomas: $(OBJ)
	$(CC) -o $@ $^ $(LIB)

%.o: %.c
	$(CC) -o obj/$@ -c $< $(CFLAGS)


clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)