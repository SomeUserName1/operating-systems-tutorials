CFLAGS = -std=c99 -g -Wall -Wextra -Wpedantic -Wbad-function-cast \
	-Wconversion -Wwrite-strings -Wstrict-prototypes

calc : calc.c stack.h token.h stack.o token.o
	gcc $(CFLAGS) -o calc calc.c stack.o token.o

stack.o : stack.c stack.h
	gcc -c $(CFLAGS) stack.c

token.o : token.c token.h
	gcc -c $(CFLAGS) token.c


.PHONY: clean

clean: 
	rm -rf *.o
	rm -rf calc
