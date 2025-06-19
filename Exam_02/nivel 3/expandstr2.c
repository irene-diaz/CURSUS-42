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

int main(int argc, char *argv[])
{
    int flag;

    flag = 0;
    if(argc==2)
    {
        int i=0;
        while(argv[1][i])
        {
            char c= argv[1][i];
            if(is_space(c) && !is_space(argv[1][i+1]) && flag == 1)
            {
                write(1, "   ",3);
            }
            if(!is_space(c))
            {
                //con esta flag me salto los espacios inicales
                flag = 1;
                write(1, &c, 1);
            }
            i++;
        }
    }
    write(1, "\n", 1);
}