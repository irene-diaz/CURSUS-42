#include <stdlib.h>
#include <unistd.h>

void	ft_strlen_ln(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

void	swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_string(char *s)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = 0;
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

void	permutate(char *str, int start, int end)
{
	int	i;

	i = 0;
	if (start == end)
	{
		ft_strlen_ln(str);
		return ;
	}
	i = start;
	while (i <= end)
	{
		swap(&str[start], &str[i]);
		permutate(str, start + 1, end);
		swap(&str[start], &str[i]);
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
int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);

	int len = ft_strlen(argv[1]);
	sort_string(argv[1]);
	permutate(argv[1], 0, len - 1);

	return (0);
}