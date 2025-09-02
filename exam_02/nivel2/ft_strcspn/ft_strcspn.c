#include <stdlib.h>
/*ft_strcspn cuenta el número de caracteres al inicio de s que no aparecen en reject.
Devuelve la posición del primer carácter de s que coincide con alguno de reject,
	o la longitud de s si no hay coincidencias.*/
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}
size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
			{
				// devolvemos la posicion en la que esta el caracter s1 que esta en s2
				return (i);
			}
			j++;
		}
		i++;
	}
	/*!! en vez de utilizar esta funcion podriamos poner i,
		pq esta al final de s1 asi que seria la longitud de s1*/
	return (ft_strlen(s));
}
/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("%ld\n", ft_strcspn("Hola", "mundo")); // devuelve 1
	printf("%ld\n", strcspn("Hola", "mundo"));    // devuelve 1
}*/