#include "apue.h"

int globvar = 6;   // external variable in initialized data
char buf[] = "a write to stdout\n";


int main(int argc,char *argv[])
{
	int var;  // automatic variable on the stack
	pid_t pid;

	var = 88;
	/*
	 * buffer: buf
	 * length is fixed.
	 */
	if(write(STDOUT_FILENO,buf,sizeof(buf) - 1) != sizeof(buf) - 1)
	{
		err_sys("write error");
	}
	printf("before fork\n");  // we don't flush stdout

	if((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if(pid == 0) // child
	{
		globvar++;
		var++;
	}
	else
	{
		printf("parent");
		sleep(2);    // parent
	}

	printf("pid = %ld,glob = %d,var = %d\n",(long)getpid(),globvar,var);

	exit(0);
}
