#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main(void)
{
	cout << "main start ------- \n";
	
	pid_t res = fork();
	cout << "res == " << res << endl;

	if (res < 0)
	{
		cout << "fork error " << endl;
		return -1;
	}
	else if (res == 0)
	{
		cout << "child here " << endl;
	}
	else
	{
		cout << "parents here " << endl;
	}

	cout << "main end " << endl;
	return 0;
}
