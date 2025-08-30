/*strpbrk busca en la cadena s1 el primer carácter que también esté en s2.
👉 Si lo encuentra, devuelve un puntero a esa posición en s1; si no,
	devuelve NULL.*/
char	*ft_strpbrk(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		// reiniciamos pq cada iteracion de i se debe recorrer toda la cadena s2
		j = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j])
				/* devolvemos puntero a la primera coincidencia (haces un cast porque s1 es
				const char* y la función debe devolver char *)*/
				return ((char *)&s1[i]);
			j++;
		}
		i++;
	}
	// sino hay coincidencias
	return (0);
}

#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("%p\n", ft_strpbrk("ola mundo", "hola"));
	printf("%p\n", strpbrk("ola mundo", "hola"));
}