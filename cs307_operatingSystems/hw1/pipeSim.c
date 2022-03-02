#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
	printf("I'm SHELL process, with PID: %d - Main command is: man cat|grep -A1 -w -e \"-n,\"\n", (int) getpid());
	int rv = fork();
	
	if (rv < 0)
	{
		printf("Error occured while fork operation!\n");	
	}
	else if (rv == 0)
	{	
		int pd[2];
		pipe(pd);
		int rv_2 = fork();
		
		if (rv_2 < 0)
		{
			printf("Error occured while fork operation!\n");
		}
		else if(rv_2 == 0)
		{
			printf("I'm GREP process, with PID: %d - My command is: grep -A1 -w -e \"-n,\"\n", (int) getpid());
			dup2(pd[0], 0);
			close(pd[1]);
			close(STDOUT_FILENO);
			open("./output.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
			execlp("grep", "grep", "-A1", "-w", "-e", "-n" ",", NULL);
		}
		else
		{
			printf("I'm MAN process, with PID: %d - My command is: man cat\n", (int) getpid());
			dup2(pd[1], 1);
			close(pd[0]);
			char *man_args[3];
			man_args[0] = strdup("man");
			man_args[1] = strdup("cat");
			man_args[2] = NULL;
			execvp(man_args[0], man_args);
		}
	}
	else
	{
		wait(NULL);
		printf("I am SHELL process, with PID: %d - execution is completed, you can find the results in output.txt\n", (int) getpid());
	}
}
