#include "apue.h"


int globvar = 6;   // external variable in initialized data
char buf[] = "a write to stdout\n";


int main(int argc,char *argv[])
{
	int var;  // automatic variable on the stack
	pid_t pid;

	var = 88;
	
	printf("before vfork\n");  // we don't flush stdout

	if((pid = vfork()) < 0)
	{
		err_sys("vfork error");
	}
	else if(pid == 0) // child
	{
		globvar++;
		var++;
		_exit(0);  // child terminates
	}
	else
	{
		int ret = printf("parent\n");
		if(ret == -1)
		{
			printf("ok");
		}
	}

	printf("pid = %ld,glob = %d,var = %d\n",(long)getpid(),globvar,var);

	exit(0);
}
