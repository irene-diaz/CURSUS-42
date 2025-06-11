#include <unistd.h>


void ft_rotone(char *letters)
{
    char c;
    int i;
    i=0;
    while(letters[i])
    {
        c = letters[i];
        if ((c >= 'a' && c <= 'y') || (c >= 'A' && c <= 'Y'))
            c += 1;
        else if (c == 'z')
            c = 'a';
        else if (c == 'Z')
            c = 'A';
        write(1, &c, 1);
        i++;
    }
}

int main(int argc, char * argv[])
{
    if(argc==2)
    {
        ft_rotone(argv[1]);
    }

    write(1, "\n", 1);
    return 0;
}