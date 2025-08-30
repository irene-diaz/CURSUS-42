int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("%d\n", ft_strcmp("Hola", "adios")); // devuelve -25
	// printf("%d\n", strcmp("Hola", "adios"));    // devuelve -1
	printf("%d\n", ft_strcmp("Hola", "Hola")); // 0
	printf("%d\n", ft_strcmp("Hola", "Holb")); // negativo ('a' - 'b')
	printf("%d\n", ft_strcmp("Holb", "Hola")); // positivo ('b' - 'a')
	printf("%d\n", ft_strcmp("Hola", "Hol"));  // positivo ('a' - '\0')
	printf("%d\n", ft_strcmp("Hol", "Hola"));  // negativo ('\0' - 'a')
}*/