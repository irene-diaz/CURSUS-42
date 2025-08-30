/*La función strspn cuenta cuántos caracteres consecutivos desde el inicio de una cadena (s) pertenecen a un conjunto de caracteres dado (accept).
Devuelve el número de caracteres iniciales que coinciden,
	deteniéndose en el primer carácter que no esté en accept.*/

#include <stdlib.h>

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	j;
	size_t	i;

	// va a contar cuántos caracteres consecutivos del inicio de s pertenecen a accept
	i = 0;
	while (s[i])
	{
		j = 0;
		// recorremos la cadena accept en el caso de que sea distinta que s1(si es igual rompemos el bucle)
		while (accept[j] && (s[i] != accept[j]))
		{
			j++;
			// Si llegamos al final de accept (accept[j] == '\0') sin encontrar coincidencia,significa que s[i] no está en accept.
			if (!accept[j])
			{
				// Entonces devolvemos i,que es la cantidad de caracteres iniciales de s que sí están en accept
				return (i);
			}
		}
		i++;
	}
	// Si todos los caracteres iniciales de s están en accept,devolvemos i al final.
	return (i);
}
/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	size_t	i;
	size_t	j;
	int		found;

	printf("%ld\n", ft_strspn("Hola mundo cruel", "Hola mundo"));
	printf("%ld\n", strspn("Hola mundo cruel", "Hola mundo"));
}*/
/*OTRA FORMA DE HACERLO:
#include <stddef.h>
size_t	ft_strspn(const char *s, const char *accept)
{
	i = 0;
	while (s[i])
	{
		found = 0;
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (!found)
			break ;
		i++;
	}
	return (i);
}
*/