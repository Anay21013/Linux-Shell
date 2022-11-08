#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char t[1024];
	scanf("%[^\n]",t);
	if (strcmp(t," ")==0){
		printf("Enter file name: ");
		char f[1024];
		scanf("%s",f);
		FILE *ptr;
		char c;
		ptr = fopen(f,"r");
		if (ptr == NULL){
			printf("Cannot open file");
		}
		else{
			do{
				c = fgetc(ptr);
				printf("%c",c);
			}while (c != EOF);

			fclose(ptr);
		}
	}
	if (strcmp(t," -n")==0){
		printf("Enter file name: ");
		char f[1024];
		scanf("%s",f);
		FILE *ptr;
		char c;
		ptr = fopen(f,"r");
		if (ptr == NULL){
			printf("Cannot open file");
		}
		else{
			char *buffer = NULL;
			size_t len = 0;
			ssize_t read;
			int count = 1;
			while ((read = getline(&buffer,&len,ptr))!= -1){
				printf("%d %s",count++,buffer);
			}
			fclose(ptr);
		}
	}
	if (strcmp(t," >")==0){
		char f1[1024];
		scanf("%s",f1);
		FILE *ptr;
		ptr = fopen(f1,"w");
		fclose(ptr);
	}
	return 0;
}