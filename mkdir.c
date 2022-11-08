#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

void mkdir1(int argc, char *c[])
{	
	if (argc == 1){
		printf("PLease enter directory name in future\n");
	}
	
	if (strcmp(c[1],"-n")==0){
		DIR *d = opendir(c[2]);
		if (d){
			printf("Directory already exists\n");
			closedir(d);
		}
		else{
			mkdir((const char *)c[2],S_IRWXU);
		}
	}
}
int main(int argc, char *argv[])
{
	mkdir1(argc,argv);
	return 0;
}