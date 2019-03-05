#include "apue.h"
#include <dirent.h>
#include <limits.h>

typedef int Myfunc(const char *,const struct stat *,int);

static Myfunc myfunc;
static int myftw(char *,Myfunc *);
static int dopath(Myfunc *);
static long nreg,ndir,nblk,nchr,nfifo,nslink,nsock,ntot;



int main(int argc,char *argv[])
{


	exit(0);
}

#define PTW_F 1        // file other than directory
#define FTW_D 2        // directory
#define FTW_DNR 3      // directory that can't be read
#define FTW_NS 4       // file that we can't stat

static char *fullpath;  // contains full pathname for every file
static size_t pathlen;

static int myftw(char *pathname,Myfunc *func)
{
	fullpath = path_alloc(&pathlen);  // malloc PATH_MAX+1 bytes

	if(pathlen <= strlen(pathname))
	{
		pathlen = strlen(pathname) * 2;
		if((fullpath = realloc(fullpath,pathlen)) == NULL)
			err_sys("realloc failed");
	}
	strcpy(fullpath,pathname);
	return (dopath(func));
}


static int dopath(Myfunc *func)
{
	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	int ret,n;
	
	if(lstat(fullpath,&statbuf) < 0)  // stat error
		return (func(fullpath,&statbuf,FTW_NS));
	if(S_ISDIR(statbuf.st_mode) == 0) // not a directory
		return (func(fullpath,&statbuf,FTW_F));

	if((ret = func(fullpath,&statbuf,FTW_D)) != 0)
		return (ret);
	n = strlen(fullpath);
	if(n + NAME_MAX + 2 > pathlen)  // expand path buffer
	{
		pathlen *= 2;
		if((fullpath = realloc(fullpath,pathlen)) == NULL)
			err_sys("realloc failed");
	}
	fullpath[n++] = '/';
	fullpath[n] = 0;
	if((dp = opendir(fullpath)) == NULL)  // can't read directory
		return (func(fullpath,&statbuf,FTW_DNR));
	while((dirp = readdir(dp)) != NULL)
	{
		if(strcmp(dirp -> d_name,".") == 0 || strcmp(dirp -> d_name,"..") == 0)
			continue;   // ignore dot and dot-dot
		strcpy(&fullpath[n],dirp -> d_name);  // append name after "/"
		if((ret = dopath(func)) != 0)    // recursive
			break;      // time to leave
	}
	fullpath[n-1] = 0;  // eraser everything from slash onward
	if(closedir(dp) < 0)
		err_ret("can't close directory %s",fullpath);
	return ret;
}

static int myfunc(const char *pathname,const struct stat *statptr,int type)
{
	switch(type)
	{
		case FTW_F:
			break;
		case FTW_D:
			ndir++;
			break;
		case FTW_DNR:
			err_ret("can't read directory %s",pathname);
			break;
		case FTW_NS:
			err_ret("stat error for %s",pathname);
			break;
		default:
			err_dump("unknown type %d of for pathname %s",type,pathname);
	}
	return 0;
}
