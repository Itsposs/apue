#include "apue.h"

void pr_stdio(const char *,FILE *);
int is_unbuffered(FILE *);
int is_linebuffered(FILE *);
int buffer_size(FILE *);


int main(void)
{
	FILE *fp;

	fgets("enter any character\n",stdout);
	if(getchar() == EOF)
	{
		err_sys("getchar error");
	}
	fputs("one line to standard error\n",stderr);

	pr_stdio("stdin",stdin);
	pr_stdio("stdout",stdout);
	pr_stdio("stderr",stderr);
	
	
	exit(0);
}

void pr_stdio(const char *name,FILE *fp)
{
	printf("stream = %s, ", name);

	if(is_unbuffered(fp))
	{
		printf("unbuffered");
	}
	else if(is_linebuffered(fp))
	{
		printf("line buffered");
	}
	else  // if neither of above
	{
		printf("fully buffered");
	}
	printf(", buffer size = %d\n",buffer_size(fp));
}


