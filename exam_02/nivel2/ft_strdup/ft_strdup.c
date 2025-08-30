#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
char	*ft_strdup(char *src)
{
	char	*str;
	int		i;

	str = malloc(ft_strlen(src) + 1);
	if (!str)
	{
		return (NULL);
	}
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*#include <unistd.h>

int	main(void)
{
	char *str = ft_strdup("Hola mundo");
	char *str2 = str;

	while (*str2)
	{
		write(1, str2, 1); // imprime el carácter actual
		str2++;
	}
	write(1, "\n", 1);
	free(str);
	return (0);
}*/