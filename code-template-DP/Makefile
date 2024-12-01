CC=g++

all: data_gen main analyser

data_gen:data_gen.cpp
	$(CC) data_gen.cpp -o data_gen

main:main.cpp algorithm.cpp test.cpp algorithm.h test.h
	$(CC)  main.cpp algorithm.cpp test.cpp -o main

analyser:analyser.cpp algorithm.cpp test.cpp algorithm.h test.h
	$(CC) analyser.cpp algorithm.cpp test.cpp -o analyser

.PHONY(clean):
clean:
	rm -rf *.o *.data data_gen main analyser
