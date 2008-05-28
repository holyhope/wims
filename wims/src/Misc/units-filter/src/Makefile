CC = gcc
all : units-filter

test : all
	sh units-test

units-filter : unites.o
	${CC} -g -o units-filter unites.o -lfl -lm -lrecode

unites.o : unites.c
	${CC} -g -c unites.c

unites.c : unites.l unites.y unites.h
	flex  unites.l
	bison  --verbose -o unites.c unites.y

clean :
	rm -f *~ unites.c *.o lex.yy.c *.output units-filter
