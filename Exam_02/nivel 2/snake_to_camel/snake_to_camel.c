#include <unistd.h>

int is_underscore(char c)
{
    if(c=='_')
    {
        return 1;
    }
    else{
        return 0;
    }
}
int main(int argc, char *argv[])
{
    if(argc==2)
    {
        int i=0;
    while(argv[1][i])
    {
        if(is_underscore(argv[1][i]))
        {
            argv[1][i+1]= argv[1][i+1] - ('a'-'A');
        }
        if(is_underscore(argv[1][i]))
        {
            i++;
        }
        write(1, &argv[1][i], 1);
        i++;
    }
    }
    
    write(1, "\n", 1);

}
