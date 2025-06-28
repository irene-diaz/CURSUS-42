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
    if (argc == 2)
    {
        int i = 0;
        int space_flag = 0;

        //saltamos los espacios iniciales
        while (is_space(argv[1][i]))
        {
            i++;
        }

        while (argv[1][i])
        {
            if (is_space(argv[1][i]))
            {
                if (!space_flag)
                {
                    // Solo imprimimos un espacio si no veníamos ya de uno
                    write(1, " ", 1);
                    space_flag = 1;
                }
            }
            else
            {
                write(1, &argv[1][i], 1);
                space_flag = 0;
            }
            i++;
        }
    }

    write(1, "\n", 1);
    return 0;
}