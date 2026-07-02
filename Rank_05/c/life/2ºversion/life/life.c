#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// PINTA EL TABLERO
// recorre todo el laberinto y lo imprime en pantalla
void	print_maze(int height, int width, char **maze)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			putchar(maze[i][j]);
			j++;
		}
		putchar('\n');
		i++;
	}
}

// genera la siguiente generación del laberinto según las reglas del juego de la vida
char	**next_gen(int height, int width, char **maze)
{
	int		i;
	int		j;
	char	**next;
	int		row_offset;
	int		col_offset;
	int		neighbors;
	int		row_neighbors;
	int		col_neighbors;

	// Allocate and zero-initialize `next`
	i = 0;
	// reserva memoria para las filas del laberinto
	next = malloc(height * sizeof(char *));
	// INCIAMOS EL TABLERO
	while (i < height)
	{
		j = 0;
		// reserva memoria para las columnas del laberinto
		next[i] = malloc(width * sizeof(char));
		while (j < width)
		{
			// todas las celdas empiezan muertas
			next[i][j] = ' ';
			j++;
		}
		i++;
	}
	i = 0;
	// RECORRER TODO EL TABLERO(aplicar las reglas del juego de la vida)
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			row_offset = -1; // mirar fila de arriba primero
			neighbors = 0;
			// recorremos todas las filas vecinas de la celda actual (i,j)
			while (row_offset <= 1)
			{
				col_offset = -1; // mirar columna de la izquierda primero
				// recorremos todas las columnas vecinas de la celda actual (i,j)
				while (col_offset <= 1)
				{
					// no contar la celda actual como vecina
					if (!(row_offset == 0 && col_offset == 0))
					{
						// calcular la posición de la celda vecina
						row_neighbors = row_offset + i;
						col_neighbors = col_offset + j;
						// verificar que la celda vecina esté dentro de los límites del laberinto
						if (row_neighbors >= 0 && row_neighbors < height
							&& col_neighbors >= 0 && col_neighbors < width)
						{
							// si el vecino está vivo,incrementamos el contador de vecinos
							if (maze[row_neighbors][col_neighbors] == '0')
								neighbors++;
						}
					}
					col_offset++;
				}
				row_offset++;
			}
			// REGLAS DEL JUEGO
			// Si la casilla esta viva y tiene 2 o 3 vecinos,sigue viva en la siguiente generación
			if (maze[i][j] == '0' && (neighbors == 2 || neighbors == 3))
				next[i][j] = '0';
			// Si la casilla esta muerta y tiene exactamente 3 vecinos,revive en la siguiente generación
			else if (maze[i][j] == ' ' && neighbors == 3)
				next[i][j] = '0';
			j++;
		}
		i++;
	}
	return (next);
}

int	main(int argc, char **argv)
{
	// si el número de argumentos no es 4, se devuelve un error
	if (argc != 4)
		return (1);

	// convertimos el primer argumento a un entero para obtener el ancho del laberinto
	int width = atoi(argv[1]);
	// convertimos el segundo argumento a un entero para obtener la altura del laberinto
	int height = atoi(argv[2]);
	// convertimos el tercer argumento a un entero para obtener el número de generaciones a simular
	int N = atoi(argv[3]);

	// reservamos memoria para el laberinto y lo inicializamos con espacios en blanco
	char **maze = malloc(height * sizeof(char *));
	int i = 0;
	while (i < height)
	{
		maze[i] = malloc(width * sizeof(char));
		int j = 0;
		while (j < width)
		{
			maze[i][j] = ' ';
			j++;
		}
		i++;
	}

	// inciamos las variables para la posición del cursor y el estado de dibujo
	/*px -> position x(empieza en la columna 0),
		py-> position y(empieza en la fila 0),
		drawing(el lapiz esta levantado, todavia no pinta)-> state of drawing */
	int px = 0, py = 0, drawing = 0;
	// leemos los comandos del usuario para mover el cursor y dibujar en el laberinto
	char cmd;
	// vamos leyendo los comandos del usuario hasta que se acaben
	while (read(0, &cmd, 1) == 1)
	{
		// si el comando es 'x',cambiamos el estado de dibujo (si estaba levantado,lo bajamos y viceversa)
		if (cmd == 'x')
			drawing = !drawing;
		// si el comando es 'w',movemos el cursor hacia arriba (si no estamos en la primera fila)
		else if (cmd == 'w' && py > 0)
			py--;
		// si el comando es 's',movemos el cursor hacia abajo (si no estamos en la última fila)
		else if (cmd == 's' && py < height - 1)
			py++;
		// si el comando es 'a',movemos el cursor hacia la izquierda (si no estamos en la primera columna)
		else if (cmd == 'a' && px > 0)
			px--;
		// si el comando es 'd',movemos el cursor hacia la derecha (si no estamos en la última columna)
		else if (cmd == 'd' && px < width - 1)
			px++;
		// si el estado de dibujo está activado,pintamos la celda actual del laberinto como viva ('0')
		if (drawing)
			maze[py][px] = '0';
	}

	i = 0;

	// simulamos N generaciones del juego de la vida
	while (i < N)
	{
		// generamos la siguiente generación del laberinto según las reglas del juego de la vida
		char **next = next_gen(height, width, maze);
		int j = 0;
		// recorremos todas las filas del laberinto y liberamos la memoria reservada para cada fila
		while (j < height)
		{
			free(maze[j]);
			j++;
		}
		// liberamos la memoria reservada para el laberinto original
		free(maze);
		// actualizamos el puntero del laberinto para que apunte a la siguiente generación
		maze = next;
		i++;
	}

	// imprimimos el laberinto final después de N generaciones
	print_maze(height, width, maze);

	// fix: same correct pattern for final cleanup
	i = 0;
	// recorremos todas las filas del laberinto y liberamos la memoria reservada para cada fila
	while (i < height)
	{
		free(maze[i]);
		i++;
	}
	// liberamos la memoria reservada para el laberinto final
	free(maze);

	return (0);
}