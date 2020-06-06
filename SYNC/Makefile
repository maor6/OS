CC = gcc
AR = ar -rcs
FLAGS = -pthread


all: q211 q212 q221 q231

q211: 2_1_1.o 
	$(CC) $(FLAGS) -o q211 2_1_1.o

2_1_1.o: 2_1_1.c
	$(CC) $(FLAGS) -c 2_1_1.c

q212: 2_1_2.o 
	$(CC) $(FLAGS) -o q212 2_1_2.o

2_1_2.o: 2_1_2.c
	$(CC) $(FLAGS) -c 2_1_2.c

q221: 2_2_1.o 
	$(CC) $(FLAGS) -o q221 2_2_1.o

2_2_1.o: 2_2_1.c
	$(CC) $(FLAGS) -c 2_2_1.c

q231: 2_3_1.o 
	$(CC) $(FLAGS) -o q231 2_3_1.o

q231.o: 2_3_1.c
	$(CC) $(FLAGS) -c 2_3_1.c


.PHONY: clean all q211 q212 q221 q231

clean: 
	rm -f *.o q211 q212 q221 q231