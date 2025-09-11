#include <stdio.h>
#include <unistd.h>

// escribir string con '\n'
void	putstr_ln(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
	write(1, "\n", 1);
}

// calcular cuantos '(' y ')' sobran
void	count_removals(char *s, int *remOpen, int *remClose)
{
	int	i;
	int	open;

	i = 0, open = 0;
	*remOpen = 0;
	*remClose = 0;
	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open > 0)
				open--; // match con un '(' previo
			else
				(*remClose)++; // este ')' sobra
		}
		i++;
	}
	*remOpen = open; // los '(' que quedaron sin cerrar
}

// backtracking
void	dfs(char *s, int pos, int len, int remOpen, int remClose, int openCount,
		char *path, int depth)
{
	char	c;

	if (pos == len)
	{
		if (remOpen == 0 && remClose == 0 && openCount == 0)
		{
			path[depth] = '\0';
			putstr_ln(path);
		}
		return ;
	}
	c = s[pos];
	if (c == '(')
	{
		// opción 1: eliminar
		if (remOpen > 0)
			dfs(s, pos + 1, len, remOpen - 1, remClose, openCount, path, depth);
		// opción 2: mantener
		path[depth] = '(';
		dfs(s, pos + 1, len, remOpen, remClose, openCount + 1, path, depth + 1);
	}
	else if (c == ')')
	{
		// opción 1: eliminar
		if (remClose > 0)
			dfs(s, pos + 1, len, remOpen, remClose - 1, openCount, path, depth);
		// opción 2: mantener, si hay un '(' abierto
		if (openCount > 0)
		{
			path[depth] = ')';
			dfs(s, pos + 1, len, remOpen, remClose, openCount - 1, path, depth
				+ 1);
		}
	}
	else
	{
		// solo copiamos (no aplica aquí pero lo dejo genérico)
		path[depth] = c;
		dfs(s, pos + 1, len, remOpen, remClose, openCount, path, depth + 1);
	}
}

int	main(int argc, char **argv)
{
	char	*s;
	int		len;

	if (argc != 2)
		return (0);
	s = argv[1];
	int remOpen, remClose;
	count_removals(s, &remOpen, &remClose);
	char path[1024]; // buffer suficiente
	len = 0;
	while (s[len])
		len++;
	dfs(s, 0, len, remOpen, remClose, 0, path, 0);
	return (0);
}
