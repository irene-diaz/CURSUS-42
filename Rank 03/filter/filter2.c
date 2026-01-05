#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	if (argc != 2 || argv[1][0] == '\0')
		return (1);

	char c;
	char *pat = argv[1];
	size_t plen = strlen(pat);
	size_t i = 0;
	ssize_t r;

	while ((r = read(0, &c, 1)) > 0)
	{
		if (c == pat[i])
		{
			i++;
			if (i == plen)
			{
				size_t j = 0;
				while (j < plen)
				{
					printf("*");
					j++;
				}
				i = 0;
			}
		}

		else
		{
			if (i > 0)
			{
				printf("%.*s", (int)i, pat);
				i = 0;
				if (c == pat[0])
				{
					i = 1;
					continue ;
				}
			}
			printf("%c", c);
		}
	}

	if (r < 0)
	{
		perror("Error: ");
		return (1);
	}

	if (i > 0)
	{
		printf("%.*s", (int)i, pat);
	}

	return (0);
}