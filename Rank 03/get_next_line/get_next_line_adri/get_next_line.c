#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	bytes_read;
	int			index;
	char		*line;
	static int	index_buffer;

	/*🔹 Variables estáticas
	buffer: espacio donde se guarda lo que read() devuelve.
	bytes_read: cuántos bytes válidos hay actualmente en buffer.
	index_buffer: posición dentro del buffer desde donde se va leyendo.
	Estas variables son static,
		así que mantienen su valor entre llamadas a get_next_line(). Esa es la clave para que las siguientes líneas se lean correctamente.
	🔹 Variables locales
	index: posición dentro del string line que estás construyendo.
	line: una nueva cadena (malloc) donde se irá copiando la línea resultante.*/
	// Valida que el fd no sea inválido y que el tamaño del buffer sea positivo.
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	index = 0;
	// Reservas una cadena fija de 10000 bytes para almacenar cada linea
	line = malloc(10000);
	/*si ya consumiste todo lo leído (o nunca leíste nada),
		llama a read() y rellena buffer*/
	while (1)
	{
		if (bytes_read <= index_buffer)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			/*Si read() devuelve:
				0: fin de archivo
				<0: error
			entonces se hace break y se sale del bucle.*/
			if (bytes_read <= 0)
				break ;
			// si hemos leido algo reiniciamos el indice para seguir con la siguiente linea
			index_buffer = 0;
		}
		// vamos copiando los caracteres del buffer a la linea
		line[index++] = buffer[index_buffer++];
		// Si el carácter copiado es un salto de línea,detiene la lectura de esta línea.
		if (line[index - 1] == '\n')
			break ;
	}
	/*Si index == 0, significa que:
	No se leyó nada,
	O se llegó al EOF sin conseguir ningún carácter.
	Entonces libera line y devuelve NULL.*/
	if (index == 0)
	{
		free(line);
		return (NULL);
	}
	// Coloca '\0' al final para crear un string válido.
	line[index] = '\0';
	// devolvemos la linea
	return (line);
}

/*int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Uso: %s <arquivo_para_ler>\n", argv[0]);
		return (1);
	}

	// Abrimos argv[1]
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0) // Cubrimos que sea negativo
	{
		perror("Error: no se puede abrir el archivo");
		return (1);
	}

	char *line;
	int count = 0;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Linea %d: %s", count + 1, line);
		free(line); // Podemos liberar directamente despues de generarla,
			aunque no se entrega main
		count++;
	}

	close(fd);
	return (0);
}*/
