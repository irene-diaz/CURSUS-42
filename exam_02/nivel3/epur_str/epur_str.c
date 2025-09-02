#include <unistd.h>

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	main(int argc, char *argv[])
{
	int	i;
	int	space_flag;
	int	last;

	if (argc == 2)
	{
		space_flag = 0;
		// encontrar el último carácter no espacio/tab
		last = 0;
		i = 0;
		while (argv[1][i])
		{
			if (!is_space(argv[1][i]))
				last = i;
			i++;
		}
		i = 0;
		while (is_space(argv[1][i]))
		{
			i++;
		}
		while (i <= last)
		{
			if (is_space(argv[1][i]))
			{
				if (space_flag == 0)
				{
					// Solo imprimimos un espacio si no veníamos ya de uno
					write(1, " ", 1);
					space_flag = 1;
				}
			}
			else
			{
				write(1, &argv[1][i], 1);
				space_flag = 0;
			}
			i++;
		}
	}
	write(1, "\n", 1);
}
