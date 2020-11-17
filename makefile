all: main.o
	gcc -o randfile main.o
main.o: main.c 
	gcc -c main.c
run: 
	./randfile
clean:
	rm *.o
	rm copy.txt