#include <stdlib.h>

int	is_space(char c)
{
	if (c == '\t' || c == ' ')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
int	count_words(char *str)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (str[i])
	{
		if (!is_space(str[i]) && (is_space(str[i - 1]) || i == 0))
		{
			cont++;
		}
		i++;
	}
	return (cont);
}

char	*copy_words(char *str, int start, int end)
{
	char	*word;
	int		i;

	word = malloc((end - start) + 1);
	i = 0;
	while (start < end)
	{
		word[i++] = str[start++];
	}
	word[i] = '\0';
	return (word);
}
char	**ft_split(char *str)
{
	char	**split;
	int		i;
	int		w;
	int		start;
	int		words;

	i = 0;
	w = 0;
	words = count_words(str);
	split = malloc((words + 1) * sizeof(char *));
	while (str[i])
	{
		while (is_space(str[i]))
		{
			i++;
		}
		if (str[i])
		{
			start = i;
			while (!is_space(str[i]) && str[i])
			{
				i++;
			}
			split[w++] = copy_words(str, start, i);
		}
	}
	split[w] = NULL;
	return (split);
}

/*#include <stdio.h>

int	main(void)
{
	char **res = ft_split("    Hola   me llamo   Irene a  ");

	for (int i = 0; res[i]; i++)
	{
		printf("Palabra %d: %s\n", i + 1, res[i]);
		free(res[i]); // liberar cada string
	}
	free(res); // liberar el array
	return (0);
}*/