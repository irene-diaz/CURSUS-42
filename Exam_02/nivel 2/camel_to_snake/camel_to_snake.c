#include <unistd.h>

int capitalize(char c)
{
    if(c>='A' && c<='Z')
    {
        return 1;
    }
    else{
        return 0;
    }
}

char lower(char c)
{
    if(c>='A' && c<='Z')
    {
        c= c + ('a'-'A');
    }
    return c;
}
int main(int argc, char *argv[])
{
    if(argc==2)
    {
        int i=0;
        while(argv[1][i])
        {
            if(capitalize(argv[1][i]))
            {
                write(1, "_", 1);
                argv[1][i]=lower(argv[1][i]);
            }
            write(1, &argv[1][i], 1);
            i++;
        }
    } 
    write(1, "\n", 1) ;
}