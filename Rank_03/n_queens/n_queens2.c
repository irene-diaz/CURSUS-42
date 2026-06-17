#include <stdlib.h>
#include <unistd.h>

int	is_safe(int *queens, int col, int row)
{
	int	i;
	int	diff;

	i = 0;
	while (i < col)
	{
		diff = queens[i] - row;
		if (diff < 0)
			diff = -diff;
		if (queens[i] == row || diff == col - i)
			return (0);
		i++;
	}
	return (1);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n >= 10)
		ft_putnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

void	print_solution(int *queens, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_putnbr(queens[i]);
		if (i != n - 1)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	solve(int *queens, int col, int n)
{
	int	row;

	row = 0;
	if (col == n)
	{
		print_solution(queens, n);
		return ;
	}
	while (row < n)
	{
		if (is_safe(queens, col, row))
		{
			queens[col] = row;
			solve(queens, col + 1, n);
		}
		row++;
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);

	int queens[20];
	int n = atoi(argv[1]);

	if (n <= 0)
		return (0);

	solve(queens, 0, n);
	return (0);
}