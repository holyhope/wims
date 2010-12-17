
all: input.jar test

input.jar: input.java
	javac -Xlint -target 1.4 -source 1.4 input.java
	jar cvf input.jar input.class inp_*.class
	rm -f input.class inp_*.class

test:
	appletviewer test.html

