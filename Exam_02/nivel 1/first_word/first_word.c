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
int main(int argc, char * argv[])
{
    if(argc==2 )
    {
        int i=0;
        while(is_space(argv[1][i]) && argv[1][i])
        {
            i++;
        }
     
        while(!is_space(argv[1][i]) && argv[1][i])
        {
                write(1, &argv[1][i], 1);
            i++;
        }
    }
    write(1, "\n", 1);
}