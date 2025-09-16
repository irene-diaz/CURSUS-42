/* get_next_line_fixed.c */
#include "get_next_line.h" /* Debe definir BUFFER_SIZE y el prototipo */
#include <stddef.h>        /* size_t */
#include <stdlib.h>        /* malloc, free */
#include <unistd.h>        /* read */

/* Busca la primera aparición del carácter c en la cadena s.
 Devuelve un puntero a esa posición o NULL si no se encuentra. Si c == '\0' devuelve puntero al terminador.*/
char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if (c == '\0')
		return (s);
	return (NULL);
}

/*Copia exactamente n bytes desde src hacia dest (hacia delante).
No gestiona solapamiento (para eso está memmove).*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/* Longitud segura (0 si s == NULL) */
size_t	ft_strlen(char *s)
{
	size_t	ret;

	ret = 0;
	if (!s)
		return (0);
	while (s[ret])
		ret++;
	return (ret);
}

/*concatena size2 bytes de s2 al final de la cadena *s1.
 Si *s1 es NULL crea una nueva cadena con los bytes de s2. Devuelve 1 si OK,
	0 si falla malloc*/
int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1;
	char	*tmp;

	// si existe s1, guardamos su longitud sino guardamos 0(error)
	size1 = *s1 ? ft_strlen(*s1) : 0;
	// reserva espacio para la vieja cadena + nuevos bytes + '\0'
	tmp = malloc(size1 + size2 + 1);
	if (!tmp)
		return (0);
	/* copia lo que había en s1 en tmp */
	if (*s1)
	{
		ft_memcpy(tmp, *s1, size1);
		free(*s1);
	}
	/* copia los bytes de s2 (si hay) en tmp */
	if (s2 && size2)
		ft_memcpy(tmp + size1, s2, size2);
	// añade el final de linea
	tmp[size1 + size2] = '\0';
	// s1 pasa a tener lo que tenga tmp
	*s1 = tmp;
	// devolvemos 1 en caso de exito
	return (1);
}

/* Añade cadena terminada en '\0' */
/*La mayoría de las veces quieres añadir una cadena completa terminada en \0,
	no un número arbitrario de bytes.
Con esta función no tienes que pasar la longitud manualmente:*/
int	str_append_str(char **s1, char *s2)
{
	if (!s2)
		return (1); /* nada que añadir */
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

/* Memmove seguro: maneja solapamiento y copia exactamente n bytes */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)src;
	size_t				i;

	d = (unsigned char *)dest;
	if (d == s || n == 0)
		return (dest);
	if (d < s) /* copiar hacia delante */
	{
		for (i = 0; i < n; i++)
			d[i] = s[i];
	}
	else /* d > s: copiar hacia atrás para no sobrescribir */
	{
		i = n;
		while (i-- > 0)
			d[i] = s[i];
	}
	return (dest);
}

/* Implementación de get_next_line usando el buffer estático b */
char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1];
	char		*ret;
	char		*nl;
	ssize_t		r;

	// es un buffer estatico, es decir, mantiene su contenido entre llamadas
	// acomula la linea que vamos a devolver
	ret = NULL;
	// Validamos que el descriptor sea válido y que el tamaño del buffer tenga sentido
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// bucle infinito el cual cortaremos o con un return o con un brake cuando sea necesario
	while (1)
	{
		// nl apunta al primer \n en el buffer b, o es NULL si no hay ninguno.
		nl = ft_strchr(b, '\n');
		// si lo encontramos
		if (nl)
		{
			/* Añadimos al resultado ret todo lo que había en b hasta el \n incluido */
			if (!str_append_mem(&ret, b, (size_t)(nl - b) + 1))
				return (free(ret), NULL);
			/* Añadimos al resultado ret todo lo que había en b hasta el \n incluido
			Esto lo que hace es recortar el buffer para que la proxima llamada empiece desde el resto de la linea*/
			ft_memmove(b, nl + 1, ft_strlen(nl + 1) + 1);
			// Devolvemos ret porque ya tenemos una línea completa(salimos del bucle)
			return (ret);
		}
		/*Si b tenía algo (pero sin \n), lo concatenamos a ret.
		Después vaciamos b para llenarlo con lo que venga en el próximo read.*/
		if (b[0] != '\0')
		{
			if (!str_append_str(&ret, b))
				return (free(ret), NULL);
			b[0] = '\0';
		}
		/*Llamamos a read para llenar el buffer b*/
		r = read(fd, b, BUFFER_SIZE);
		/*liberamos y devolvemos NULL*/
		if (r < 0)
			return (free(ret), NULL);
		/*si ret tiene algo acumulado, lo devolvemos (última línea sin \n),
			si no, devolvemos NULL.*/
		if (r == 0) /* EOF */
			return (ret && ret[0] ? ret : (free(ret), NULL));
		// Si hay datos, los terminamos con \0
		b[r] = '\0';
	}
}
#include <fcntl.h> // open
#include <stdio.h> // printf, perror

int	main(int argc, char **argv)
{
	int fd;
	char *line;

	if (argc != 2)
	{
		printf("Uso: %s <archivo>\n", argv[0]);
		return (1);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error abriendo archivo");
		return (1);
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("LINEA: %s", line);
		free(line);
	}

	close(fd);
	return (0);
}