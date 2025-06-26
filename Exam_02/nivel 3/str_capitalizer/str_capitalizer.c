#include <unistd.h>

int is_space(char c)
{
    if(c==' ' || c=='\n')
    {
        return 1;
    }
    else{
        return 0;
    }
}

int is_letter(char c)
{
    if((c>='a' && c<='z') || (c>='A' && c<='Z'))
    {
        return 1;
    }
    else{
        return 0;
    }
}
int main(int argc, char *argv[])
{
    if(argc>=2)
    {
        int i=0;
        while(argv[1][i])
        {
            char c= argv[1][i];
            while(i==0 || is_space(argv[1][i-1]) && is_letter(c))
            {
                c= c-('a'-'A');
            }
        write(1, &c,1);
        i++;
        }
         
    }
    write(1, "\n", 1);
}