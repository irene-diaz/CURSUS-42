#include <unistd.h>

int is_letter(char c)
{
    if(c>='a' && c<='z' || c>='A' && c<='Z')
    {
        return 1;
    }
    else{
        return 0;
    }
}
char to_upper(char c)
{
    if(c>='a' && c<='z')
    {
        c= c-('a'-'A');
    }
    return c;
}
char to_lower(char c)
{
    if(c>='A' && c<='Z')
    {
        c= c+('a'-'A');
    }
    return c;
}

void rstr(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (is_letter(str[i]))
        {
            // buscamos si la siguiente letra NO es una letra => estamos en la última letra de la palabra
            if (!is_letter(str[i + 1]))
                str[i] = to_upper(str[i]);
            else
                str[i] = to_lower(str[i]);
        }
        write(1, &str[i], 1);
        i++;
    }
}
int main(int argc, char *argv[])
{
    if(argc==1)
    {
        write(1, "\n", 1);
    }
    else{
        int i=1; //lo inicializamos en 1, para que no empieze por el ejecutable
        //recorremos todos los argumentos y le aplicamos la funcion que creamos antes
        while(i<argc)
        {
            rstr(argv[i]);
            write(1, "\n", 1);
            i++;
        }
    }
}