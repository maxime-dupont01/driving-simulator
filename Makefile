CC = g++
LDFLAGS = -lm -lglut -lGL -lGLU
OPTS =  -I"./irrKlang/include" ./irrKlang/bin/linux-gcc-64/libIrrKlang.so -pthread

all:
	$(CC) driving-simulator.cpp library.cpp $(LDFLAGS) $(OPTS) -o main

clean:
	rm main