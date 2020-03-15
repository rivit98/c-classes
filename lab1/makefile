CC=g++
CFLAGS=-Wall

main: clean cone main.o
	$(CC) $(CFLAGS) main.o cone.o -o a

main.o:
	$(CC) $(CFLAGS) -c main.cpp -o main.o

cone:
	$(CC) $(CFLAGS) -c cone.cpp -o cone.o

clean:
	rm -f *.o a

test: main
	./a
