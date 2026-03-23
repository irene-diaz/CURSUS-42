#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int ft_popen(const char *file, const char *av[], char type)
{
    if (!file || !av || (type != 'r' && type != 'w'))
        return -1;

    int fd[2];
    if (pipe(fd) < 0)
        return -1;

    pid_t pid = fork();
    if (pid < 0)
    {
        close(fd[0]);
        close(fd[1]);
        return -1;
    }

    // PROCESO HIJO
    if (pid == 0)
    {
        if (type == 'r')
        {
            close(fd[0]);
            //lo redirijimos para que sea la salida estandar
            if (dup2(fd[1], STDOUT_FILENO) < 0)
                exit(1);
            close(fd[1]);
        }
        else
        {
            close(fd[1]);
            if (dup2(fd[0], STDIN_FILENO) < 0)
                exit(1);
            close(fd[0]);
        }

        execvp(file, av);
        exit(1);
    }

    // PROCESO PADRE
    if (type == 'r')
    {
        close(fd[1]);
        return fd[0];
    }
    else
    {
        close(fd[0]);
        return fd[1];
    }
}