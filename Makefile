COMP    ?= cc
FLAGS   += -Wall
INCLUDE ?= -I /usr/local/include
LIB     ?= -L /usr/local/lib -l sndio -l pthread

x : main.c timer.h defaults.h args.o threads.o inter.o
	$(COMP) $(FLAGS) $(INCLUDE) $(LIB) -o x main.c args.o threads.o inter.o

args.o : args.c args.h timer.h defaults.h
	$(COMP) $(FLAGS) -c -o args.o args.c

threads.o : threads.c threads.h timer.h
	$(COMP) $(FLAGS) -c -o threads.o threads.c

inter.o : inter.c inter.h timer.h threads.h
	$(COMP) $(FLAGS) -c -o inter.o inter.c

clean :
	rm -f x args.o threads.o inter.o
