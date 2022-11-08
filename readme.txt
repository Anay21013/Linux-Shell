INTERNAL COMMANDS:
1>Echo -> reads input and gives it as output
2>Pwd  -> provides current working directory
3>Exit -> used to terminate the shell
4>Cd   -> used to change directory

EXTERNAL COMMANDS:
1> Date
    i." "      -> Gives current date,day and time in current timezone
   ii." --gmt" -> Gives current time in NY and London w.r.t gmt
  iii." --h"   -> Help instruction

2> ls
    i. " " -> Simply lists all the files in the current directory
   ii. "-a"-> Lists all files in directory along with hidden files
  iii. "-l"-> Lists all files in the directory in a tabular format along with date on which it was made and read/write permissions

3> cat
    i. " " -> Reads out and prints contents of the file with the filename as input
   ii. "-n"-> Reads out and prints contents of the file with the filename as input along with the line number
  iii. " >"-> Creates a new file with filename as input from user

4> mkdir
    i. " " -> Creates a new directory with directory name as input
   ii. "--version"-> Tells version of mkdir currently in use

5> rm
    i. " "->Removes the file with filename taken as input from user

ERRORS HANDLED:
1> In 'rm' I have made sure that the command does not remove any directories and checks whether file exists or not.
2> As such no corner cases exist for 'date' command therefore, I have not added any error check here.
3>'mkdir' gives an error statement if no directory name is given as input or if the directory already exists.
4> 'cat' will give an error statement if wrong filename is given as input for 'cat' and 'cat -n'.
    In case of 'cat >' the shell script will make sure that the user has to input a name and command would not terminate until the user does so.
5>'ls' will give an error statement both when the given filename/directory name does not exist and when the permission for reading the file are denied.
6> If command given is not amongst these 9 then the shell will give a 'command not found' error.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Sample Testcase//
anay@anay-virtual-machine:~/Documents$ gcc shell1.c
anay@anay-virtual-machine:~/Documents$ ./a.out 
Anay's shell$ echo hi this is Anay
>> hi this is Anay
Anay's shell$ pwd
>>Current directory: /home/anay/Documents
Anay's shell$ ls 
a.out  cat.c  date.c  forktst2.c  forktst.c  hehe  hey.c  ls.c	Makefile  mkdir1.c  mkdir.c  p1.c  p2.c  pwd.c	rm.c  shell1.c	shell.c  thread1.c  thread.c  threadcreate.c  tst.c  wait.c
Anay's shell$ ls -l
total 112
-rwxrwxr-x 1 anay anay 16576 Oct 31 04:45 a.out
-rw-rw-r-- 1 anay anay   914 Oct 30 12:53 cat.c
-rw-rw-r-- 1 anay anay   172 Oct 24 16:45 date.c
-rw-rw-r-- 1 anay anay   389 Oct 23 13:15 forktst2.c
-rw-rw-r-- 1 anay anay   122 Oct 14 15:44 forktst.c
drwxr-xr-x 2 anay anay  4096 Oct 31 01:19 hehe
-rw-rw-r-- 1 anay anay    92 Oct 28 20:58 hey.c
-rw-rw-r-- 1 anay anay   908 Oct 29 09:25 ls.c
-rw-rw-r-- 1 anay anay   128 Oct 31 04:16 Makefile
-rw-rw-r-- 1 anay anay   396 Oct 29 08:02 mkdir1.c
-rw-rw-r-- 1 anay anay   503 Oct 30 02:12 mkdir.c
-rw-rw-r-- 1 anay anay   168 Oct 23 13:15 p1.c
-rw-rw-r-- 1 anay anay   521 Oct 15 03:50 p2.c
-rw-rw-r-- 1 anay anay   191 Oct 14 19:16 pwd.c
-rw-rw-r-- 1 anay anay   232 Oct 29 19:55 rm.c
-rw-rw-r-- 1 anay anay  5934 Oct 31 01:21 shell1.c
-rw-rw-r-- 1 anay anay  5416 Oct 31 02:59 shell.c
-rw-rw-r-- 1 anay anay   573 Oct 14 14:23 thread1.c
-rw-rw-r-- 1 anay anay   400 Oct 14 13:48 thread.c
-rw-rw-r-- 1 anay anay   338 Oct 14 22:59 threadcreate.c
-rw-rw-r-- 1 anay anay    92 Oct 14 12:57 tst.c
-rw-rw-r-- 1 anay anay   460 Oct 14 17:12 wait.c
Anay's shell$ ls -a
.  ..  a.out  cat.c  date.c  forktst2.c  forktst.c  hehe  hey.c  ls.c  Makefile  mkdir1.c  mkdir.c  p1.c  p2.c	pwd.c  rm.c  shell1.c  shell.c	thread1.c  thread.c  threadcreate.c  tst.c  wait.c
Anay's shell$ cat 
Enter filename: ls.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

void _ls(const char *dir,int op_a,int op_l){
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
int main(int argc, const char *argv[]){
	if (argc == 1){
		_ls(".",0,0);
	}
	else if (argc == 2){
		if (argv[1][0] == '-'){
			int op_a = 0, op_l = 0;
			char *p = (char*)(argv[1] + 1);
			while(*p){
				if(*p == 'a') op_a = 1;
				else if(*p == 'l') op_l = 1;
				else{
					perror("PLease select an option that is available");
					exit(EXIT_FAILURE);
				}
				p++;
			}
			_ls(".",op_a,op_l);
		}
	}
	return 0;
}
Anay's shell$ cat -n
Enter filename: ls.c
     1	#include <stdio.h>
     2	#include <stdlib.h>
     3	#include <errno.h>
     4	#include <dirent.h>
     5	
     6	void _ls(const char *dir,int op_a,int op_l){
     7		struct dirent *d;
     8		DIR *dh = opendir(dir);
     9		if (!dh){
    10			if (errno = ENOENT){
    11				perror("Directory does not exist");
    12			}
    13			else{
    14				perror("Unable to read directory");
    15			}
    16			exit(EXIT_FAILURE);
    17		}
    18		while ((d = readdir(dh)) != NULL){
    19			if (!op_a && d->d_name[0] == '.')
    20				continue;
    21			printf("%s  ", d->d_name);
    22			if(op_l) printf("\n");
    23		}
    24		if(!op_l)
    25		printf("\n");
    26	}
    27	int main(int argc, const char *argv[]){
    28		if (argc == 1){
    29			_ls(".",0,0);
    30		}
    31		else if (argc == 2){
    32			if (argv[1][0] == '-'){
    33				int op_a = 0, op_l = 0;
    34				char *p = (char*)(argv[1] + 1);
    35				while(*p){
    36					if(*p == 'a') op_a = 1;
    37					else if(*p == 'l') op_l = 1;
    38					else{
    39						perror("PLease select an option that is available");
    40						exit(EXIT_FAILURE);
    41					}
    42					p++;
    43				}
    44				_ls(".",op_a,op_l);
    45			}
    46		}
    47		return 0;
    48	}
Anay's shell$ cat > hi
Anay's shell$ ls 
a.out  cat.c  date.c  forktst2.c  forktst.c  hehe  hey.c  ls.c	Makefile  mkdir1.c  mkdir.c  p1.c  p2.c  pwd.c	rm.c  shell1.c	shell.c  thread1.c  thread.c  threadcreate.c  tst.c  wait.c
Anay's shell$ cat >
Enter name of file to be created using cat: hi
Anay's shell$ ls 
a.out  cat.c  date.c  forktst2.c  forktst.c  hehe  hey.c  hi  ls.c  Makefile  mkdir1.c	mkdir.c  p1.c  p2.c  pwd.c  rm.c  shell1.c  shell.c  thread1.c	thread.c  threadcreate.c  tst.c  wait.c
Anay's shell$ mkdir 
Enter directory name: newdir
Anay's shell$ ls 
a.out  cat.c  date.c  forktst2.c  forktst.c  hehe  hey.c  hi  ls.c  Makefile  mkdir1.c	mkdir.c  newdir  p1.c  p2.c  pwd.c  rm.c  shell1.c  shell.c  thread1.c	thread.c  threadcreate.c  tst.c  wait.c
Anay's shell$ rm 
Enter filename: hey.c
Anay's shell$ ls 
a.out  cat.c  date.c  forktst2.c  forktst.c  hehe  hi  ls.c  Makefile  mkdir1.c  mkdir.c  newdir  p1.c	p2.c  pwd.c  rm.c  shell1.c  shell.c  thread1.c  thread.c  threadcreate.c  tst.c  wait.c
Anay's shell$ mkdir --version
>>mkdir (GNU coreutils) 8.32
  Written by Anay Chauhan
Anay's shell$ date 
Monday 31 October 2022 04:48:15 AM IST
Anay's shell$ date --gmt
>>Current world clock:
  London :  0:18
  New York  : 19:18
Anay's shell$ date --h
>>date command tells current date and time in current timezone
  use '--gmt' to get current time in NY and London
Anay's shell$ exit

/*End of Testcase */