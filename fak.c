#include <stdio.h>

#define MAX_N 42

int main(){
	int n, i;
	int values[MAX_N] = {1};
	printf("Gib eine Zahl < %d ein\n", MAX_N);
	scanf("%d",&n);

	if(n == 0)n++;

	for(i = 1; i <= n; i++)
		values[i] = values[i-1] * i;
	for(i = 0; i <= n; i++)
		printf("%d\n",values[i]);

}
