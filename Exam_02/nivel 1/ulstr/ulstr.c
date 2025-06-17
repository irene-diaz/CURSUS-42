#include <unistd.h>

int main(int argc, char *argv[])
{
char c;
int i;
i=0;
if (argc==2)
{
    while(argv[1][i])
    {
        c=argv[1][i];
        if(c>='a' && c<='z')
        {
            c = c - ('a' - 'A'); // minúscula a mayúscula
        }
        else if(c>='A' && c<='Z')
        {
            c = c + ('a' - 'A'); // mayúscula a minúscula
        }
        else{
            c+=0;
        }
        write(1, &c, 1);
        i++;
    }
}
write(1, "\n", 1);
}