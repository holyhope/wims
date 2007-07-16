
all: input.jar test

input.jar: input.java
	javac input.java
	jar cvf input.jar input.class inp_*.class
	rm -f input.class inp_*.class

test:
	appletviewer test.html

