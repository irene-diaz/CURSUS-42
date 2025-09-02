char    *ft_strcpy(char *s1, char *s2)
{
    int i=0;
    while(s2[i]!='\0')
    {
        s1[i]=s2[i];
        i++;
    }
    s1[i]='\0';
    return s1;
}
/*#include <unistd.h>
 #include <string.h>
int main(void)
{
    char s2[] = "Hola mundo";
    char s1[100];
    char s3[100] = "Hola mundo";
    char s4[] = "Nuevo mensaje";

    ft_strcpy(s1, s2);
    int i = 0;
    while (s1[i])
    {
        write(1, &s1[i], 1);
        i++;
    }
    write(1, "\n", 1);

    strcpy(s3, s4);
    i = 0;
    while (s3[i])
    {
        write(1, &s3[i], 1);
        i++;
    }
    write(1, "\n", 1);

    return 0;
}*/


