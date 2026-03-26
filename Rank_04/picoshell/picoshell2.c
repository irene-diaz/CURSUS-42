#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int    picoshell(char **cmds[])
{
    int fd[2];
    int i=0;
    int last_fd = -1;
    pid_t pid;

    while(cmds[i])
    {
        if(cmd[i + 1] && pipe(fd) == -1)
            return 1;
        
        pid = fork();

        if(pid == -1)
        {
            if(cmd[i + 1])
            {
                close(fd[0]);
                close(fd[1]);
            }
            return 1;
        }

        if(pid == 0)
        {
            if(last_fd != -1)
            {
                dup2(last_fd, 0);
                close(last_fd);
            }

            if (cmd[i + 1])
            {
                dup2(fd[1], 1);
                close(fd[1]);
            }

            execvp(cmds[i][0], cmd[i]);
            exit(1);
        }

        if(last_fd != -1)
            close(last_fd);
    }
}