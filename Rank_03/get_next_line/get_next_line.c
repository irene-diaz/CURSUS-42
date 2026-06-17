#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

// calcula la longitud de un string
int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

// busca el carácter c en s, devuelve puntero si lo encuentra, NULL si no
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		// Si coincide → devolvemos la dirección donde está el carácter ((char *)s).
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		// Si no coincide → avanzamos s++ al siguiente carácter.
		s++;
	}
	// Si justo c es '\0', devolvemos un puntero a ese final de la cadena.
	if (*s == (char)c)
		return ((char *)s);
	// NULL lo devolvemos pq significa que ni en la cadena ni en el '\0' había coincidencia con c
	return (NULL);
}
// funcion principal
/*stash → lo que ya teníamos acumulado de lecturas anteriores.
  buf → lo que acabamos de leer con read.*/
char	*get_next_line(int fd)
{
	static char	*stash;
	int			len1;
	char		*tmp;
	int			len;

	// 📦 Memoria estática donde acumulamos datos leídos entre llamadas
	char buf[BUFFER_SIZE + 1]; // buffer temporal para leer del archivo
	char *line;                // la línea que vamos a devolver
	int i, j, r;               // índices y valor de read()
	// 🚫 caso de error en el descriptor o buffer inválido
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// 1️⃣ Leer hasta encontrar un \n o EOF
	/* Si todavía no tenemos stash(guarda lo queda de la llamada anterior) o no contiene un \n,
		seguimos leyendo.*/
	while (!stash || !ft_strchr(stash, '\n'))
	{
		/*read devuelve cuántos bytes se leyeron (r), o 0 en EOF, o
			-1 en error.*/
		// leer hasta BUFFER_SIZE bytes
		r = read(fd, buf, BUFFER_SIZE);
		// si hay erroes salimos del while
		if (r <= 0)
			break ;
		/*Hacemos buf[r] = '\0' para que buf sea un string válido en C.*/
		// terminamos el string leído
		buf[r] = '\0';
		// 2️⃣ Concatenar stash + buf
		/*si existe stash devolvemos su longitud, sino devolvemos 0*/
		len1 = stash ? ft_strlen(stash) : 0;
		/*creamos una variable temporal para guardar el espacio de las lineas leidas*/
		tmp = malloc(len1 + r + 1);
		if (!tmp)
			return (NULL);
		/*copiamos el stash en tmp y liberamos el stash
			antiguo(para eso usamos tmp, para no perder lo anterior)*/
		if (stash)
		{
			for (i = 0; i < len1; i++)
				tmp[i] = stash[i];
			free(stash);
		}
		/*juntamos toda la informacion leida antes y la de ahora en tmp*/
		for (j = 0; j < r; j++)
			tmp[len1 + j] = buf[j];
		// terminamos el string
		tmp[len1 + r] = '\0';
		// actualizamos el stash
		stash = tmp;
	}
	// 3️⃣ Si stash está vacío → no queda nada que devolver
	/*Si no hay datos (stash == NULL) o está vacío (*stash == '\0'),
	devolvemos NULL.
		Esto indica EOF alcanzado y no hay más líneas.*/
	if (!stash || *stash == '\0')
		return (free(stash), stash = NULL, NULL);
	// 4️⃣ Extraer la línea desde stash
	/*Aquí tomamos la primera línea completa de stash (incluido \n si existe) y la guardamos en line.*/
	i = 0;
	// avanzar hasta '\n' o fin de cadena
	while (stash[i] && stash[i] != '\n')
	{
		i++;
	}
	// incluir el salto de línea si lo hay
	if (stash[i] == '\n')
		i++;
	// reservar memoria para la línea
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	// copiar desde stash a line
	for (j = 0; j < i; j++)
		line[j] = stash[j];
	// terminamos la línea
	line[i] = '\0';
	// 5️⃣ Recortar stash (lo que sobra después de la línea)
	{
		// longitud del "resto"
		len = ft_strlen(stash + i);
		// reservar memoria si hay resto
		tmp = len ? malloc(len + 1) : NULL;
		// copiamos el resto
		if (tmp)
		{
			for (j = 0; stash[i]; j++, i++)
				tmp[j] = stash[i];
			tmp[j] = '\0';
		}
		// liberamos el stash antiguo
		free(stash);
		// actualizamos el stash
		stash = tmp;
	}
	// devolvemos la linea
	return (line);
}

/*#include <fcntl.h> // open
#include <stdio.h> // printf

int	main(void)
{
	int fd;
	char *line;

	// Abrimos un archivo para leer
	fd = open("archivo.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}

	// Leemos todas las líneas del archivo
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line); // ya incluye \n si existe
		free(line);         // liberamos la memoria devuelta
	}

	// Cerramos el archivo
	close(fd);
	return (0);
}*/