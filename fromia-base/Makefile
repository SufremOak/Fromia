all:
	gcc -shared -pthread -fPIC -fwrapv -O2 -Wall -I/usr/include/python3.11 -o FWorkspace.o FWorkspace.c
	gcc -shared -pthread -fPIC -fwrapv -O2 -Wall -stdc++ -I/usr/local/include/Fromia -o main.cpp main.o
	