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

int	is_letter(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
char	to_upper(char c)
{
	if (c >= 'a' && c <= 'z')
	{
		c = c - ('a' - 'A');
	}
	return (c);
}
char	to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c = c + ('a' - 'A');
	}
	return (c);
}
void	str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_letter(str[i]))
		{
			if (i == 0 || is_space(str[i - 1]))
			{
				str[i] = to_upper(str[i]);
			}
			else
			{
				str[i] = to_lower(str[i]);
			}
		}
		write(1, &str[i], 1);
		i++;
	}
}
int	main(int argc, char *argv[])
{
	if (argc == 1)
	{
		write(1, "\n", 1);
	}
	else
	{
		int i = 1;
		while (i < argc)
		{
			str(argv[i]);
			write(1, "\n", 1);
			i++;
		}
	}
}