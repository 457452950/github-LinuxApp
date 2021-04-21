#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t pc, pr;
	
	pc = fork();
	if (pc < 0)
	{
		printf("Error fork\n");
	}
	else if (pc == 0)
	{
		sleep(5);
		exit(0);
	}
	else
	{
		do
		{
			pr = waitpid(pc, NULL, WNOHANG);
			
			if(pr == 0)
			{
				printf("The child process has not exited\n");
				sleep(1);
			}
		}while(pr == 0);
		
		if(pr == pc)
		{
			printf("Get child exit Code: %d\n",pr);
		}
		else
			printf("Some error occured.\n");
	}
	return 0;
}
	