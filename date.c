#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int main()
{
	time_t t;
	time(&t);
	printf(">>%s",ctime(&t));
	return 0;
}