CC = gcc
SRC = fortress.c rules.c
OBJ = $(SRC:.c=.o)
HEADERS = fortress.h rules.h
CFLAGS = -Wall
PROG = fortress

$(PROG): $(OBJ) $(HEADERS)
	$(CC) -o $@ $(OBJ)
%.o: %.c
	$(CC) -c $< $(CFLAGS)