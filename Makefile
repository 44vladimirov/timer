COMP    ?= cc
FLAGS   += -Wall
INCLUDE ?= -I /usr/local/include
LIB     ?= -L /usr/local/lib -l sndio -l pthread

OBJ = $(COMP) $(FLAGS)

x : main.c defaults.h messages.o args.o threads.o inter.o
	$(OBJ) $(INCLUDE) $(LIB) -o x main.c messages.o args.o threads.o inter.o

messages.o : messages.c messages.h
	$(OBJ) -c -o messages.o messages.c

args.o : args.c args.h defaults.h
	$(OBJ) -c -o args.o args.c

threads.o : threads.c threads.h messages.h
	$(OBJ) -c -o threads.o threads.c

inter.o : inter.c inter.h messages.h threads.h
	$(OBJ) -c -o inter.o inter.c

clean :
	rm -f x messages.o args.o threads.o inter.o
