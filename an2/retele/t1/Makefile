all: myfind-strip

myfind.o: myfind.c
	gcc -c -Wall myfind.c

myfind: myfind.o
	gcc -o myfind myfind.o

myfind-strip: myfind
	strip -s myfind -o myfind-strip

