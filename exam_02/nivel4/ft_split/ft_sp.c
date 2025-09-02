#include <stdlib.h>

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	**ft_split(char *str)
{
	int		i;
	int		word;
	int		j;
	int		starts[100];
	int		ends[100];
	char	**result;
	int		len;

	i = 0;
	word = 0;
	// 1. Detectar palabras y guardar sus inicios y finales
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (str[i]) // hay palabra
		{
			starts[word] = i;
			while (str[i] && !is_space(str[i]))
				i++;
			ends[word] = i;
			word++;
		}
	}
	// 2. Reservar memoria para el array de punteros (+1 para NULL final)
	result = (char **)malloc(sizeof(char *) * (word + 1));
	if (!result)
		return (NULL);
	// 3. Copiar cada palabra en memoria nueva
	for (int w = 0; w < word; w++)
	{
		len = ends[w] - starts[w];
		// reservamos memoria para cada palabra
		result[w] = (char *)malloc(sizeof(char) * (len + 1));
		if (!result[w])
			return (NULL);
		// (nota: aquí faltaría liberar lo anterior en código "perfecto")
		j = 0;
		while (j < len)
		{
			result[w][j] = str[starts[w] + j];
			j++;
		}
		result[w][j] = '\0'; // terminador de string
	}
	// 4. Terminar el array con NULL
	result[word] = NULL;
	return (result);
}

#include <stdio.h>

int	main(void)
{
	char	**tab;
	int		i;

	tab = ft_split("Hola   que tal\tcomo\nestas");
	i = 0;
	while (tab[i])
	{
		printf("[%s]\n", tab[i]);
		i++;
	}
}
