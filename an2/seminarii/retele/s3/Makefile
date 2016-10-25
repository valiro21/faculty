

all: bin sendDataFifo recDataFifo mySendDataFifo myRecDataFifo

bin:
	mkdir bin

sendDataFifo: sendDataFifo.c
	gcc -o bin/sendDataFifo sendDataFifo.c

recDataFifo: recDataFifo.c
	gcc -o bin/recDataFifo recDataFifo.c

mySendDataFifo: mySendDataFifo.c
	gcc -o bin/mySendDataFifo mySendDataFifo.c

myRecDataFifo: myRecDataFifo.c
	gcc -o bin/myRecDataFifo myRecDataFifo.c
