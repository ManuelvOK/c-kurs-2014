#include <stdio.h>

long long int fac(int);

int main(int argc, const char *argv[]){
	int n;
	long long int result;
	scanf("%d", &n);
	result = fac(n);
	printf("%lld\n", result);
	return 0;
}

long long int fac(int n){
	if(n < 2) return 1;
	return n*fac(n-1);
}
