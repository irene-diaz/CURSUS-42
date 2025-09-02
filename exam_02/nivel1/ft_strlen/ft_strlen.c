int	ft_strlen(char *str)
{
    int i=0;
    while(*str)
    {
        str++;
        i++;
    }
    return i;
}
/*#include <stdio.h>
int main(void)
{
    printf("%d", ft_strlen("Hola mundo "));
}*/