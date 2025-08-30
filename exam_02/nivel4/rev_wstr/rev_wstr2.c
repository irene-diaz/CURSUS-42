#include <stdlib.h>
#include <unistd.h>

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

char	*copy_word(char *str, int start, int end)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc((end - start) + 1);
	while (start < end)
	{
		word[i++] = str[start++];
	}
	word[i] = '\0';
	return (word);
}

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		int i = 0;
		int start;
		while (argv[1][i])
		{
			while (is_space(argv[1][i]))
			{
				i++;
			}
			if (argv[1][i])
			{
				while (!is_space(argv[1][i]) && argv[1][i])
				{
					
				}
			}
		}
	}
	write(1, "\n", 1);
}