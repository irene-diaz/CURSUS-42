#include <unistd.h>

int main(int argc, char *argv[])
{
int i = 0;
char c;
int repeat;
if (argc==2)
{
    while(argv[1][i])
    {
        c=argv[1][i];
        //cambiamos las minusculas
        if (c >= 'a' && c <= 'z')
            //a es ASCCI es 97, entonces por ejemplo con la letra b seria 98-97=1(esto quiere decir que la b se repetira 2 veces)
			repeat = c - 'a' + 1;
        //cambiamos las mayusculas
        else if (c >= 'A' && c <= 'Z')
			repeat = c - 'A' + 1;
        //sino es una letra, repetimos solo una vez el caracter
        else{
            repeat=1;
        }
        //mientras esten esos caracteres en el str, muestralos tantas repeticiones como tengan
        while (repeat > 0)
        {
            write(1, &c, 1);
            repeat--;
        }
        i++;
    }
}
write(1, "\n", 1);
return 0;
}