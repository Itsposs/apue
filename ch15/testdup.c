#include "apue.h"
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int fd;
	if( (fd = open("test1.txt",O_CREAT | O_RDWR | O_TRUNC,S_IRUSR | S_IWUSR)) < 0)
	{
		err_sys("open error");
		exit(1);
	}
	
	int pfd = dup(fd);
	if(pfd < 0)
	{
		err_sys("dup error");
		exit(3);
	}
	close(fd);

	printf("fd: %d,pfd: %d\n",fd,pfd);
	char buffer[MAXLINE];
	int n = 0;
	while((n = read(STDIN_FILENO,buffer,MAXLINE)) > 0)
	{
		if(write(pfd,buffer,MAXLINE) != n )  // error
		{
			err_sys("write error"); 
			exit(4);
		}
	}
	if(n < 0)
	{
		err_sys("read error");
	}

	exit(0);
}
