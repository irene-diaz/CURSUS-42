#include "libft.h"
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

/*int	main(void)
{
	const char	*texto = "Hola mundo";
	char		*ptr;
	const char	*texto2 = "Hola mundo";
	char		*ptr2;

	ptr = strchr(texto, 'm');
	if (ptr != NULL)
		printf("Encontrado: %s\n", ptr); // Imprime "mundo"
	else
		printf("No se encontró el carácter\n");
	ptr2 = ft_strchr(texto2, 'm');
	if (ptr2 != NULL)
		printf("Encontrado: %s\n", ptr2); // Imprime "mundo"
	else
		printf("No se encontró el carácter\n");
	return (0);
}*/
