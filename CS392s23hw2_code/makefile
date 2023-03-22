CC=gcc
CFLAGS=-I.
DEPS=utils.h insertion.h
OBJ=main.o utils.o insertion.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

insertmake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
