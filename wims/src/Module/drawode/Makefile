# Module/drawode/Makefile.  Generated from Makefile.in by configure.

cc=gcc
cflags=-g -O2 -Wall
LIB=-L../../Flydraw/gd -lgd -lm
O=drawode.o drawode_func.o

all: drawode drawode_g

%.o: %.c drawode.h
	$(cc) $(cflags) -ffast-math -fomit-frame-pointer -o $@ -c $<

drawode: $(O)
	$(cc) $(cflags) -ffast-math -fomit-frame-pointer -o $@ $(O) $(LIB)

drawode_g: drawode.c drawode_func.c drawode.h
	$(cc) $(cflags) -DDEBUG -o $@ drawode.c drawode_func.c $(LIB)

clean:
	-rm -f drawode drawode_g *.o
