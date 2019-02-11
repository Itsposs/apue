#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc,char *argv[])
{
	int fd;
	pid_t pid;
	char buf[5];
	struct stat statbuf;

	if(argc != 2)
	{
		fprintf(stderr,"usage: %s filename\n",argv[0]);
		exit(1);
	}
	
	if((fd = open(argv[1],O_CREAT | O_TRUNC,FILE_MODE)) < 0)
	{
		err_sys("open error");
	}
	if(write(fd,"abcdef",6) != 6)
	{
		err_sys("write error");
	}

	if(fstat(fd,&statbuf) < 0)
	{
		err_sys("fstat error");
	}

	// turn on set-group-ID and turn off group-execute 
	if(fchmod(fd,(statbuf.st_mode & ~S_IXGID) | S_ISGID) < 0)
	{
		err_sys("fchmod error");
	}

	TELL_WAIT();

	if((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if(pid > 0)
	{
		// write lock entire file
		if(write_lock(fd,0,SEEK_SET,0) < 0)
		{
			err_sys("write_lock error");
		}

		TELL_CHILD(pid);

		if(waitpid(pid,NULL,0) < 0)
		{
			err_sys("waitpid error");
		}
	}
	else
	{

	}





	return 0;
}
