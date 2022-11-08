#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <dirent.h>
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

int main(){
    while(true){
        char cmd[1024];
        printf("Anay's shell$ ");
        scanf("%s",cmd);
        if (strcmp(cmd,"pwd")==0){
            pwd();
        }
        if (strcmp(cmd,"echo")==0){
            char str[1024];
            scanf("%[^\n]",str);
            printf(">>%s\n",str);
        }
        if (strcmp(cmd,"date")==0){
            char t1[1023];
            scanf("%[^\n]",t1);
            int rc = fork();
            if (rc == 0){
                if (strcmp(t1," ")==0){
                    char *argument[] = {"./date",NULL};
                    if (execvp("date",argument)<0){
                        printf("ERROR:exec failed!\n");
                    }
                    break;
                }
                if (strcmp(t1," --gmt")==0){
                    time_t t;
                    struct tm *info;
                    time(&t);
                    info = gmtime(&t);
                    printf(">>Current world clock:\n");
                    printf("  London : %2d:%02d\n", (info->tm_hour+L)%24, info->tm_min);
                    printf("  New York  : %2d:%02d\n", (info->tm_hour+NY)%24, info->tm_min);            
                }
                if (strcmp(t1," --h")==0){
                    printf(">>date command tells current date and time in current timezone\n  use '--gmt' to get current time in NY and London\n");
                }
            }
            if (rc < 0){
                printf("Unexpected error occurred!");
            }else{
                int rc_w = wait(NULL);
            }
        }
        if (strcmp(cmd,"exit")==0){
            exit(1);
        }
        if (strcmp(cmd,"rm")==0){
            int rc = fork();
            char t3[1024];
            scanf("%[^\n]",t3);
            if (rc == 0){
                if (strcmp(t3," ")==0){
                    char f2[1024];
                    printf("Enter filename: ");
                    scanf("%s",f2);
                    char *arg[] = {"./rm",f2,NULL};
                    if (execvp("rm",arg) == -1){
                        printf("ERROR:exec failed\n");
                    }
                }
            }
            if (rc > 0){
                int rc_w = wait(NULL);
            }
        }
        if (strcmp(cmd,"cat")==0){
            int rc = fork();
            char t3[1024];
            scanf("%[^\n]",t3);
            if (rc == 0){
                if (strcmp(t3," ")==0){
                    char fname[1024];
                    printf("Enter filename: ");
                    scanf("%s",fname);
                    char *arg[] = {"./cat",fname,NULL};
                    if (execvp("cat",arg) == -1){
                        printf("ERROR:exec failed\n");
                    }
                }
                if (strcmp(t3," -n")==0){
                    char fname[1024];
                    printf("Enter filename: ");
                    scanf("%s",fname);
                    char *arg[] = {"./cat","-n",fname,NULL};
                    if (execvp("cat",arg) == -1){
                        printf("ERROR:exec failed\n");
                    }
                }
                if (strcmp(t3," >")==0){
                    char f1[1024];
                    printf("Enter name of file to be created using cat: ");
                    scanf("%s",f1);
                    FILE *ptr;
                    ptr = fopen(f1,"w");
                    fclose(ptr);
                }

            }
            if (rc > 0){
                int rc_w = wait(NULL);
            }
        }
        if (strcmp(cmd,"mkdir")==0){
            char t3[1024];
            scanf("%[^\n]",t3);
            int rc = fork();
            if (rc == 0){
                if (strcmp(t3," ")==0){
                    printf("Enter directory name: ");
                    char dname[16];
                    scanf("%s",dname);
                    char *arg[] = {"./mkdir",dname,NULL};
                    if (execvp("mkdir",arg) == -1){
                        printf("ERROR:exec failed\n");
                    }
                }
                if (strcmp(t3," --version")==0){
                    printf(">>mkdir (GNU coreutils) 8.32\n  Written by Anay Chauhan\n");
                }
            }
            if (rc > 0){
                int rc_w = wait(NULL);
            }
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
        if (strcmp(cmd,"echo")!=0 && strcmp(cmd,"pwd")!=0 && strcmp(cmd,"ls")!=0 && strcmp(cmd,"mkdir")!=0 && strcmp(cmd,"rm")!=0 && strcmp(cmd,"cat")!=0 && strcmp(cmd,"date")!=0 && strcmp(cmd,"cd")!=0){
            printf("Command not found\n");
        }
    }
}