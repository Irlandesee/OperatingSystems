#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	unsigned long i;
	srand( (unsigned)time(NULL) );
	for(int j = 0; j < 100500; j++){
		int n;
		while( (n = rand() > RAND_MAX - (RAND_MAX-5)%6)){}
		printf("%d, \t%d\n", n, n % 6+1);
	}
	return 0;
}