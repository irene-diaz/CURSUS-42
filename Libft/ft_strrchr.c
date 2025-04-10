#include "libft.h"
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	lon;

	lon = ft_strlen(s);
	while (s[lon])
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		lon--;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

/*int	main(void)
{
	const char	*texto = "mola mundo";
	char		*ptr;
	const char	*texto2 = "Hola mundo";
	char		*ptr2;

	ptr = strrchr(texto, 'm');
	if (ptr != NULL)
		printf("Encontrado: %s\n", ptr); // Imprime "mundo"
	else
		printf("No se encontró el carácter\n");
	ptr2 = ft_strrchr(texto2, 'm');
	if (ptr2 != NULL)
		printf("Encontrado: %s\n", ptr2); // Imprime "mundo"
	else
		printf("No se encontró el carácter\n");
	return (0);
}*/
