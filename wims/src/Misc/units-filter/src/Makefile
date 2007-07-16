cc=gcc
CFLAGS=-g -O2

units-filter : unites.o
	$(cc) $(CFLAGS) -o units-filter unites.o -lfl

unites.o : unites.c
	$(cc) $(CFLAGS) -c unites.c

unites.c : unites.l unites.y unites.h
	flex  unites.l
	bison  --verbose -o unites.c unites.y

clean :
	rm -f *~ *.o *.output units-filter
