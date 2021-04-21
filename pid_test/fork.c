#include <sys/types.h>
#include <sys/unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int n = 0;

int main(void)
{
	pid_t result;
	result = fork();
	printf("Start : &n = %d, n = %d\n", &n, n++);
	n++;
	
	if (result == -1)
	{
		printf("Fork error");
	}
	else if (result == 0)
	{
		printf("The returned value is %d\n In chaild process!!\nMy PID is %d\n",
			result, getpid());
		printf("chaild : &n = %d, n = %d\n", &n, n);
	}
	else 
	{
		printf("The returned value is %d\n In father process!!\nMy PID is %d\n",
			result, getpid());
		printf("father : &n = %d, n = %d\n", &n, n);
	}
	//while (1);
	return result;
}