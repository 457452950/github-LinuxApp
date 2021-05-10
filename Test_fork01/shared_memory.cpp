#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
using namespace std;
int main(void)
{
	int shmid;

	if ((shmid = shmget((key_t)0x5005, 1024, 0640|IPC_CREAT)) == -1)
	{
		printf("shmat(0x5005) failed \n");
		return -1;
	}

	char* ptext = 0;

	ptext = (char*) shmat(shmid, 0, 0);

	printf("写入前：%s\n", ptext);
	sprintf(ptext, "本程序的进程号是: %d", getpid());
	printf("写入后：%s\n", ptext);

	shmdt(ptext);

	/*
	if (shmctl(shmid, IPC_RMID, 0) == 1)
	{
		printf("shmctl(0x5005) failed \n");
		return -1;
	}
	*/	

	vector<int> st;
	st.push_back(9);
	st.pop_back();
		
	sleep(10);

	return 0;
}	
