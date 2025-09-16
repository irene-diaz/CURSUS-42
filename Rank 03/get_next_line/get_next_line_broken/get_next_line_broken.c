/*incluir las librerias*/
#include "get_next_line.h"
#include <stdlib.h>

/*
No comprueba '\0' y puede leer fuera de rango si el carácter no está en la cadena.
No comprueba si s == NULL.
*/
char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != c)
		i++;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}
/*
El bucle while (--n > 0) no copia el primer byte (cuando n == 1 no copia nada). Implementación errónea.
Debe copiar exactamente n bytes.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (--n > 0)
		((char *)dest)[n - 1] = ((char *)src)[n - 1];
	return (dest);
}
/*
OK en esencia,
pero falla si le pasas NULL. Mejor defensiva: si s == NULL devuelve 0.
*/
size_t	ft_strlen(char *s)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}
int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1;
	char	*tmp;

	size1 = ft_strlen(*s1);
	tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest > src)
		return (ft_memcpy(dest, src, n));
	else if (dest == src)
		return (dest);
	i = ft_strlen((char *)src) - 1;
	while (i >= 0)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i--;
	}
	return (dest);
}
char	*get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (!str_append_str(&ret, b))
			return (NULL);
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return (NULL);
		b[read_ret] = 0;
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}