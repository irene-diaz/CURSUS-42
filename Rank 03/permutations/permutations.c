#include <unistd.h>

// función para imprimir un string + '\n' usando write
void	putstr_ln(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

// función para intercambiar dos caracteres
void	swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// ordena la cadena en orden alfabético (simple bubble sort)
void	sort_string(char *s)
{
	char	tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (s[i])
	{
		j = i + 1;
		while (s[j])
		{
			if (s[j] < s[i])
			{
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

// backtracking para generar permutaciones
/*int start= inicio de la cadena(indice)
int end=final de la cadena(indice)*/
void	reverse(char *s, int start, int end)
{
	while (start < end)
	{
		swap(&s[start], &s[end]);
		start++;
		end--;
	}
}

// Nueva función: Generar la siguiente permutación en orden lexicográfico
// Retorna 1 si hay siguiente, 0 si no
int	next_permutation(char *s, int len)
{
	int	i;
	int	j;

	// Paso 1: Encontrar el mayor i donde s[i] < s[i+1]
	i = len - 2;
	while (i >= 0 && s[i] >= s[i + 1])
		i--;
	if (i < 0)
		return (0); // No hay más permutaciones
	// Paso 2: Encontrar el mayor j > i donde s[i] < s[j]
	j = len - 1;
	while (s[j] <= s[i])
		j--;
	// Paso 3: Swap s[i] y s[j]
	swap(&s[i], &s[j]);
	// Paso 4: Invertir desde i+1 hasta el final
	reverse(s, i + 1, len - 1);
	return (1);
}

int	main(int argc, char *argv[])
{
	int len;

	if (argc != 2)
		return (1);
	len = ft_strlen(argv[1]);
	if (len == 0)
		return (0); // Caso borde: cadena vacía

	// Ordenar la cadena para empezar con la primera permutación
	sort_string(argv[1]);

	// Imprimir todas las permutaciones en orden
	do
	{
		putstr_ln(argv[1]);
	} while (next_permutation(argv[1], len));

	return (0);
}