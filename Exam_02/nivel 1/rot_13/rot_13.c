#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc==2)
    {
        int i;
        char c;
        i=0;
        while(argv[1][i])
        {
            c=argv[1][i];
            //hasta la letra 13 del abecedario sumamos 13 letras mas
            if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
            c += 13;
            //depues de la letra 13 no podemos sumar 13, pq no hay mas que 26 letras en el abecedario, por eso restamos 13
            else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z'))
            c -= 13;
            write(1, &c, 1);
            i++;
        }
    }
    write(1, "\n", 1);
}