CC=g++ -std=c++11

all: mult

mult:mult.cpp
	$(CC) mult.cpp -o mult
