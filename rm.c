#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
	printf("ENter filename: ");
	char f[1024];
	scanf("%s",f);
	if (remove(f)==0){
		printf("file deleted.\n");
	}else{
		printf("unable to delete file.\n");
	}
	return 0;
}