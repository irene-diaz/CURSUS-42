#include <fcntl.h>

int ft_popen(const char *file, const char *av[],  char type)
{
    if(!file || !av || (type!='r' || type!='w'))
        return -1;

    int fd[2];

    if(pipe(fd)<0)
        return -1;

    pid_t pid= fork();

    if(pid<0)
    {
        close(fd[0]);
        close(fd[1]);
        return -1;
    }

    if(pid==0)
    {
        if(type=='r')
        {
            
        }
    }
    
}
