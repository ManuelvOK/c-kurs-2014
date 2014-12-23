objects = main.o conio.o

dungeon : $(objects)
	gcc -o dungeon $(objects)

main.o : main.c conio.h
	gcc -c main.c -std=c99

conio.o : conio.c
	gcc -c conio.c -std=c99

.PHONY : clean
clean :
	rm dungeon $(objects)

