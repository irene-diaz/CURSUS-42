
typedef struct  s_point
{
  int           x;
  int           y;
}               t_point;

// Función recursiva para realizar el "flood fill"
void fill(char **tab, t_point size, int x, int y, char target)
{
    // Verificamos si estamos fuera de los límites de la matriz
    if (x < 0 || x >= size.x || y < 0 || y >= size.y)
        return; // Si estamos fuera, no hacemos nada

    // Si el carácter actual no es igual al carácter original a reemplazar, salimos
    if (tab[y][x] != target)
        return;

    // Reemplazamos el carácter actual por 'F'
    tab[y][x] = 'F';

    // Llamadas recursivas a las 4 direcciones adyacentes (no diagonales)
    /*Dirección	Movimiento en coordenadas	Código
        Derecha	    (x + 1, y)	            x + 1
        Izquierda	(x - 1, y)	            x - 1
        Abajo	    (x, y + 1)	            y + 1
        Arriba	    (x, y - 1)	            y - 1*/
    fill(tab, size, x + 1, y, target); // derecha
    fill(tab, size, x - 1, y, target); // izquierda
    fill(tab, size, x, y + 1, target); // abajo
    fill(tab, size, x, y - 1, target); // arriba
}

// Función principal que inicia el algoritmo de "flood fill"
void	flood_fill(char **tab, t_point size, t_point begin)
{
	// Obtenemos el carácter inicial desde la posición de inicio (begin.x, begin.y)
	// Este será el carácter que vamos a reemplazar por 'F' en toda la zona conectada
	char target = tab[begin.y][begin.x];

	// Llamamos a la función recursiva 'fill' para comenzar a llenar desde la posición dada
	fill(tab, size, begin.x, begin.y, target);
}
/*#include <stdlib.h>
#include <stdio.h>

char** make_area(char** zone, t_point size)
{
	char** new;

	new = malloc(sizeof(char*) * size.y);
	for (int i = 0; i < size.y; ++i)
	{
		new[i] = malloc(size.x + 1);
		for (int j = 0; j < size.x; ++j)
			new[i][j] = zone[i][j];
		new[i][size.x] = '\0';
	}

	return new;
}

int main(void)
{
	t_point size = {8, 5};
	char *zone[] = {
		"11111111",
		"10001001",
		"10010001",
		"10110001",
		"11100001",
	};

	char**  area = make_area(zone, size);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	printf("\n");

	t_point begin = {7, 4};
	flood_fill(area, size, begin);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	return (0);
}*/