#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#define NY (-4)
#define L (1)


int chdir(const char *path);
char *getcwd(char *buf, size_t size);

void pwd(){
    char cwd[1024];
    chdir("/path/to/change/directory/to");
    getcwd(cwd, sizeof(cwd));
    printf(">>Current directory: %s\n", cwd);
}

void *date(){
	time_t t;
	time(&t);
	printf(">>%s",ctime(&t));
	return NULL;
}
void *gmt(){
	time_t t;
	struct tm *info;
	time(&t);
	info = gmtime(&t);
	printf(">>Current world clock:\n");
	printf("  London : %2d:%02d\n", (info->tm_hour+L)%24, info->tm_min);
	printf("  New York  : %2d:%02d\n", (info->tm_hour+NY)%24, info->tm_min); 
}
void *cat(){
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
	return NULL;
}
void *rm(){
	printf("Enter filename: ");
	char f[1024];
	scanf("%s",f);
	if (remove(f)==0){
		printf("file deleted.\n");
	}else{
		printf("unable to delete file.\n");
	}
	return NULL;
}
void *mkdir1()
{	
	char dname[16];
	printf("Enter name of directory to be created: ");
	scanf("%s",dname);
	if (mkdir(dname,0755)==0){
		printf("Directory created successfully\n");
	}
	else{
		printf("Unable to create directory\n");
	}
	return NULL;
}
void *_ls(const char *dir,int op_a,int op_l){
	struct dirent *d;
	DIR *dh = opendir(dir);
	if (!dh){
		if (errno = ENOENT){
			perror("Directory does not exist");
		}
		else{
			perror("Unable to read directory");
		}
		exit(EXIT_FAILURE);
	}
	while ((d = readdir(dh)) != NULL){
		if (!op_a && d->d_name[0] == '.')
			continue;
		printf("%s  ", d->d_name);
		if(op_l) printf("\n");
	}
	if(!op_l)
	printf("\n");
}
int main(){
	while(true){
		char cmd[1024];
        printf("Anay's shell$ ");
        scanf("%s",cmd);
        if (strcmp(cmd,"pwd")==0){
            pwd();
        }
        if (strcmp(cmd,"ls")==0){
        	char t2[1024];
            scanf("%[^\n]",t2);
            int rc = fork();
            if(rc == 0){
                if (strcmp(t2," ")==0){
                    char *arg[] = {"./ls",NULL};
                    if (execvp("ls",arg) == -1){
                        printf(">>ERROR:exec failed\n");
                    }
                }
                if (strcmp(t2," -l")==0){
                    char *arg[] = {"./ls","-l",NULL};
                    if (execvp("ls",arg) == -1){
                        printf(">>ERROR:exec failed\n");
                    }
                }
                if (strcmp(t2," -a")==0){
                    char *arg[] = {"./ls","-a",NULL};
                    if (execvp("ls",arg) == -1){
                        printf("ERROR:exec failed\n");
                    }
                }
            }if (rc > 0){
                int rc_w = wait(NULL);
            }
        }
        if (strcmp(cmd,"echo")==0){
            char str[1024];
            scanf("%[^\n]",str);
            printf(">>%s\n",str);
        }
        if (strcmp(cmd,"exit")==0){
        	break;
        }
        if (strcmp(cmd,"date")==0){
        	char t1[1023];
            scanf("%[^\n]",t1);
        	pthread_t p1;
        	int rc;
        	if (strcmp(t1," ")==0){
	        	pthread_create(&p1,NULL,date,NULL);
	        	pthread_join(p1,NULL);
        	}
        	if (strcmp(t1," -gmt")==0){
        		pthread_create(&p1,NULL,gmt,NULL);
        		pthread_join(p1,NULL);
        	}
        	if (strcmp(t1," -h")==0){
        		printf(">>date command tells current date and time in current timezone\n  use '-gmt' to get current time in NY and London\n");
        	}
        }
        if (strcmp(cmd,"cat")==0){
        	pthread_t p1;
        	int rc;
        	pthread_create(&p1,NULL,cat,NULL);
        	pthread_join(p1,NULL);
        }
        if (strcmp(cmd,"rm")==0){
        	pthread_t p1;
        	int rc;
        	pthread_create(&p1,NULL,rm,NULL);
        	pthread_join(p1,NULL);
        }
        if (strcmp(cmd,"mkdir")==0){
        	pthread_t p1;
        	int rc;
        	char t1[1023];
            scanf("%[^\n]",t1);
            if (strcmp(t1," ")==0){
	        	pthread_create(&p1,NULL,mkdir1,NULL);
	        	pthread_join(p1,NULL);
	        }
	        if (strcmp(t1," --version")==0){
	        	printf(">>mkdir (GNU coreutils) 8.32\n  Written by Anay Chauhan\n");
	        }
        }
        if (strcmp(cmd,"echo")!=0 && strcmp(cmd,"pwd")!=0 && strcmp(cmd,"ls")!=0 && strcmp(cmd,"mkdir")!=0 && strcmp(cmd,"rm")!=0 && strcmp(cmd,"cat")!=0 && strcmp(cmd,"date")!=0 && strcmp(cmd,"cd")!=0){
        	printf("Command not found\n");
        }
	}
}