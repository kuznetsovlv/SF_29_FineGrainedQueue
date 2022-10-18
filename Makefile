#Makefile
objects = main.o fine_grained_queue.o

.PHONY: all clean
all: queue

queue: ${objects}
	gcc -o queue ${objects} -lstdc++

main.o: fine_grained_queue.h
fine_grained_queue.o:

clean:
	-rm -f queue *.o 2>/dev/null
