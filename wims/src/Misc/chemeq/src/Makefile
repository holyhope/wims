# -*- coding: utf-8 -*-
CXX = g++
CXXFLAGS= -g -O1

chemeq : chemeq.o chemparser.o mendeleiev.o
	${CXX} $(CXXFLAGS) -o chemeq chemeq.o chemparser.o mendeleiev.o -lfl


mendeleiev.o : mendeleiev.c chemeq.h
	${CXX} $(CXXFLAGS) -c $<

chemeq.o : chemeq.cc chemeq.h
	${CXX} $(CXXFLAGS) -c chemeq.cc

chemparser.o : chemparser.cc chemeq.h
	${CXX} $(CXXFLAGS) -c chemparser.cc

chemparser.cc : chemlex.cc chemeq.y chemeq.h
	bison  --verbose -o chemparser.cc chemeq.y

chemlex.cc : chemeq.l
	flex  -ochemlex.cc chemeq.l

clean :
	rm -f *~ *.o semantic.cache chemlex.cc  chemparser.cc *.output chemeq

