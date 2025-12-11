#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// comprobar si la reina en (row, col) es segura
/*La función revisa si esta posición no es atacada por ninguna
 reina que ya hayamos colocado en columnas anteriores (0..col-1).*/
int	is_safe(int *queens, int col, int row)
{
	int	diff;
	int	i;

	// diferencia de filas entre una reina ya colocada y la que queremos situar.
	//índice para recorrer columnas anteriores.
	i = 0;
	// recorremos todas las columnas anteriores
	while (i < col)
	{
		/* diferencia de filas(restamos la posicion de columan de la reina
			- la fila)*/
		diff = queens[i] - row;
		/*(distancia vertical absoluta entre la reina ya colocada y la que queremos colocar).*/
		// valor absoluto de la diferencia(le ponemos negativo pq -x- es +)
		if (diff < 0)
			diff = -diff;
		// comprobamos ataques: misma fila o misma diagonal(la diferencia de filas igual a la diferencia de columnas indica diagonal.)
		if (queens[i] == row || diff == col - i)
			return (0); // no es seguro(la reina es atacada)
		i++;
	}
	return (1); // es seguro(la reina no es atacada)
}
// pasar de nº a string(para poder imprimirlo con write)
void	putnbr(int n)
{
	char	c;

	if (n >= 10)
	{
		putnbr(n / 10);
	}
	c = n % 10 + '0';
	write(1, &c, 1);
}
// imprimir la solución usando write
void	print_solution(int *queens, int n)
{
	int	i;

	i = 0;
	// recorremos todas las soluciones
	while (i < n)
	{
		putnbr(queens[i]); // imprimir la fila de la reina
		// ponemos un espacio entre los numero hasta n-1(pq en el ultimo numero no hace falta)
		if (i != n - 1)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

// función recursiva de backtracking
void	solve(int *queens, int col, int n)
{
	int	row;

	row = 0;
	/*Caso base:si hemos colocado reinas en todas las columnas. exito*/
	if (col == n)
	{
		print_solution(queens, n);
		return ;
	}
	// mientras la fila sea menor que el numero de reinas que queremos colocar
	while (row < n)
	{
		/* si es seguro,
			guardamos la reina en la fila y columna correspondiente,
			y miramos la siguiente columna*/
		if (is_safe(queens, col, row))
		{
			queens[col] = row;
			solve(queens, col + 1, n);
		}
		// si no es segura, miramos la siguiente fila
		row++;
	}
}

int	main(int argc, char **argv)
{
	int n;
	int *queens;

	// control de numero de argumentos
	if (argc != 2)
	{
		//generamos un mensaje de error 
		fprintf(stderr, "Usage: %s n\n", argv[0]);
		return (1);
	}

	// conversion de string a numero del nº de reinas que queremos colocar
	n = atoi(argv[1]);

	// lanzamos un error si el nº de reinas es negativo
	if (n <= 0)
		return (1);

	// reservamos memoria para el nº de reinas
	queens = malloc(sizeof(int) * n);
	// comprobacion del malloc
	if (!queens)
		return (1);

	// llamamos recursivamente a la funcion para ir llenando el tablero
	solve(queens, 0, n);

	// liberamos la memoria
	free(queens);
	return (0);
}