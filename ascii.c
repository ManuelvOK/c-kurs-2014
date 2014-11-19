#include <stdio.h>

int main(int argc, char *argv[]){
	unsigned char i;
	while(i < 255)
		printf("%d -  %c \t", i, i++);
	return 0;
}
