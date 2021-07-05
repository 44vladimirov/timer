COMP    ?= cc
FLAGS   += -Wall
INCLUDE ?= -I /usr/local/include
LIB     ?= -L /usr/local/lib -l sndio -lpthread

x : main.c timer.h defaults.h args.o inter.o
	$(COMP) $(FLAGS) $(INCLUDE) $(LIB) -o x main.c args.o inter.o

args.o : args.c args.h timer.h defaults.h
	$(COMP) $(FLAGS) -c -o args.o args.c

inter.o : inter.c inter.h
	$(COMP) $(FLAGS) -c -o inter.o inter.c

clean :
	rm -f x args.o inter.o
