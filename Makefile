CC=g++
DLIBS=-lbcm2835 -lrt -lpthread
main:main.o sim7000.o
	$(CC) -Wall -o main main.o arduPi.o sim7x00.o sim7000.o $(DLIBS)
arduPi.o:arduPi.cpp arduPi.h
	$(CC) -Wall -c arduPi.cpp $(DLIBS)
sim7x00.o:sim7x00.cpp sim7x00.h arduPi.cpp arduPi.h
	$(CC) -Wall -c arduPi.cpp sim7x00.cpp $(DLIBS)
sim7000.o:sim7000.cpp sim7000.h sim7x00.cpp sim7x00.h arduPi.cpp arduPi.h
	$(CC) -Wall -c sim7000.cpp sim7x00.cpp arduPi.cpp $(DLIBS)
main.o:arduPi.o sim7x00.o sim7000.o
	$(CC) -Wall -c arduPi.cpp sim7x00.cpp sim7000.cpp main.cpp $(DLIBS)
clean:
	rm main.o  main

