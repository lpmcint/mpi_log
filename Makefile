CC=g++ -std=c++11
CFLAGS=-Wall

all: main.cpp log.cpp log.h
	$(CC) $(CFLAGS) main.cpp log.cpp -o log

clean:
	rm log 