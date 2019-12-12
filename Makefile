CC = gcc
SRC = fortress.c rules.c controls.c
OBJ = $(SRC:.c=.o)
HEADERS = fortress.h rules.h controls.h
CFLAGS = -Wall
PROG = fortress

$(PROG): $(OBJ) $(HEADERS)
	$(CC) -o $@ $(OBJ)
%.o: %.c
	$(CC) -c $< $(CFLAGS)