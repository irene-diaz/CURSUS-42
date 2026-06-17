#include <stdlib.h>
#include <unistd.h>

void	ft_putstr_ln(char *str)
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

void	reverse(char *str, int start, int end)
{
	while (start < end)
	{
		swap(&str[start], &str[end]);
		start++;
		end--;
	}
}

int	next_permutation(char *str, int len)
{
	int	i;
	int	j;

	j = 0;
	i = len - 2;
	while (i >= 0 && str[i] >= str[i + 1])
	{
		i--;
	}
	if (i < 0)
		return (0);
	j = len - 1;
	while (str[j] <= str[i])
	{
		j--;
	}
	swap(&str[i], &str[j]);
	reverse(str, i + 1, len - 1);
	return (1);
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

	if (len == 0)
		return (0);

	sort_string(argv[1]);

	do
	{
		ft_putstr_ln(argv[1]);
	} while (next_permutation(argv[1], len));

	return (0);
}