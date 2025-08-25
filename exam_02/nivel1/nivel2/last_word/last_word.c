#include <unistd.h>

int is_space(char c)
{
    if(c==' ' || c=='\t')
    {
        return 1;
    }
    else{
        return 0;
    }
}
int ft_strlen(char *str)
{
    int i=0;
    while(*str)
    {
        str++;
        i++;
    }
    return i;
}
int main(int argc, char *argv[])
{
    if(argc==2)
    {
        int start;
        int end;
        int i=ft_strlen(argv[1]);
        while(is_space(argv[1][i]))
        {
            i--;
        }

        i=start;

        while(!is_space(argv[1][i]))
        {
            i--;
        }
        end=i;
        while(end>=start)
        {
            write(1, &argv[1][start], 1);
            start++;
        }
    }
    write(1., "\n", 1);
}