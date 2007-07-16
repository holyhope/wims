# Misc/symtext/Makefile.  Generated from Makefile.in by configure.

wims_home=../../..
cc=gcc
cflags=-g -O2 -Wall
defines=-DGNU_SOURCE -DVERSION_DATE=\"2007-06-25\"
rpath=
STRIP=strip
lopt=$(rpath)

all:: symtext

clean::
	rm -f symtext

distclean:
	rm -f symtext
	cd $(wims_home)/public_html/bin; rm -f symtext 2>/dev/null; cd ../../src/Misc/symtext
	rm -f Makefile

symtext: *.c *.h
	$(cc) $(cflags) $(lopt) -o symtext symtext.c
	./symtext -t
	$(STRIP) $@
	cp $@ $(wims_home)/public_html/bin


