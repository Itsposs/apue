#include "apue.h"
#include <sys/wait.h>


int main(void)
{
	pid_t pid;
	
	if((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if(pid == 0)  // first child
	{
		printf("group: %ld\n",(long)getpgrp());
		if((pid = fork()) < 0)
		{
			err_sys("fork error");
		}
		else if(pid > 0)
		{
			printf("group: %ld\n",(long)getpgrp());
			exit(0);  // parent from second fork == first child
		}
		
		/*
		 *
		 */

		printf("group: %ld\n",(long)getpgrp());
		sleep(2);
		printf("second child,parent pid = %ld\n",(long)getppid());
		exit(0);
	}
	
	/*
	if(waitpid(pid,NULL,0) != pid) // wait for first child
	{
		err_sys("waitpid error");
	}
	*/
	
	if(waitpid(pid,NULL,WNOHANG) != pid)  // nonblock 
	{
		err_sys("waitpid error");
	}
	/*
	 *
	 */

	exit(0);
}
