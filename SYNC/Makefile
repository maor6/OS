CC = gcc
AR = ar -rcs
FLAGS = -Wall


all: q211 q212 q221 q231

q211: q211.o 
	$(CC) $(FLAGS) -o q1 q211.o

q211.o: q211.c
	$(CC) $(FLAGS) -c q211.c

q212: q212.o 
	$(CC) $(FLAGS) -o q1 q212.o

q212.o: q212.c
	$(CC) $(FLAGS) -c q212.c

q221: q221.o 
	$(CC) $(FLAGS) -o q1 q221.o

q221.o: q221.c
	$(CC) $(FLAGS) -c q221.c

q231: q231.o 
	$(CC) $(FLAGS) -o q1 q231.o

q231.o: q231.c
	$(CC) $(FLAGS) -c q231.c


.PHONY: clean all q1 q2 q3

clean: 
	rm -f *.o q1 q2 q3
