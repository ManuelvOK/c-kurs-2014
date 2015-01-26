objects = linklist2.o tree.o main.o

all : $(objects)
	gcc -o main $(objects)

main.o : linklist2.h tree.h main.c
	gcc -c main.c

%.o : %.c
	gcc -c $<

clean :
	rm -rf main *.o
