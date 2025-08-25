#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc==3)
    {
        int i=0;
        int j=0;
        while(argv[2][j])
        {
            if(argv[1][i]==argv[2][j])
            {
                write(1, &argv[2][j], 1);
                i++;
            }
            j++;
        }
    }
    write(1, "\n", 1);
}