#include <unistd.h>

/* Imprime la cadena seguida de '\n' */
void	putstr_ln(char *s)
{
	int	i = 0;

	while (s[i])
		write(1, &s[i++], 1);
	write(1, "\n", 1);
}

/*
 * Cuenta cuántos '(' y ')' sobran
 */
void	count_removals(char *s, int *remOpen, int *remClose)
{
	int	open = 0;
	int	i = 0;

	*remOpen = 0;
	*remClose = 0;
	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open > 0)
				open--;
			else
				(*remClose)++;
		}
		i++;
	}
	*remOpen = open;
}

/*
 * DFS que genera todas las soluciones válidas
 */
void	dfs(char *s, int pos, int len,
			int remOpen, int remClose, int openCount)
{
	char	c;

	if (pos == len)
	{
		if (remOpen == 0 && remClose == 0 && openCount == 0)
			putstr_ln(s);
		return ;
	}

	c = s[pos];

	if (c == '(')
	{
		/* Opción 1: eliminar '(' */
		if (remOpen > 0)
		{
			s[pos] = ' ';
			dfs(s, pos + 1, len, remOpen - 1, remClose, openCount);
			s[pos] = '(';
		}
		/* Opción 2: mantener '(' */
		dfs(s, pos + 1, len, remOpen, remClose, openCount + 1);
	}
	else if (c == ')')
	{
		/* Opción 1: eliminar ')' */
		if (remClose > 0)
		{
			s[pos] = ' ';
			dfs(s, pos + 1, len, remOpen, remClose - 1, openCount);
			s[pos] = ')';
		}
		/* Opción 2: mantener ')' si hay '(' abierto */
		if (openCount > 0)
			dfs(s, pos + 1, len, remOpen, remClose, openCount - 1);
	}
}

/* Copia simple de string */
void	str_copy(char *dst, char *src)
{
	int	i = 0;

	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	main(int argc, char **argv)
{
	char	str[1024];
	int		len = 0;
	int		remOpen;
	int		remClose;

	if (argc != 2)
		return (0);

	str_copy(str, argv[1]);
	while (str[len])
		len++;

	count_removals(str, &remOpen, &remClose);
	dfs(str, 0, len, remOpen, remClose, 0);

	return (0);
}