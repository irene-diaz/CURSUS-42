//#include <stdio.h>
int	ft_strlen(char *str)
{
	int i = 0;
	while (*str)
	{
		str++;
		i++;
	}
    return i;
}

/*int main(void)
{
    printf("%i", ft_strlen("Hola me llamo Irene"));
}*/