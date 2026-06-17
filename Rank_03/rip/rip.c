#include <stdio.h>
#include <unistd.h>

// Imprime un string seguido de '\n'
void	putstr_ln(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
	write(1, "\n", 1);
}

/*
 * Calcula cuántos paréntesis deben eliminarse para poder
 * generar una cadena válida.
 *
 * remOpen  → cantidad de '(' que sobran
 * remClose → cantidad de ')' que sobran
 */
void	count_removals(char *s, int *remOpen, int *remClose)
{
	int	i;

	i = 0;
	int open = 0;  // cuenta cuántos '(' están abiertos sin cerrar
	*remOpen = 0;  // es la cantidad de '(' que quedaron sin cerrar al final.
	*remClose = 0; // cuenta los ')' que sobran y no tienen pareja.
	while (s[i])
	{
		if (s[i] == '(')
			open++; // un '(' pendiente de cerrar
		else if (s[i] == ')')
		{
			if (open > 0)
				open--; // match con un '(' previo
			else
				(*remClose)++; // ')' que sobra porque no hay '(' disponible
		}
		i++;
	}
	*remOpen = open; // los '(' que quedaron sin cerrar al final
}

/*
 * DFS / Backtracking para generar todas las cadenas válidas.
 *
 * pos       → índice actual en la cadena original
 * len       → longitud de la cadena
 * remOpen   → '(' que aún podemos eliminar
 * remClose  → ')' que aún podemos eliminar
 * openCount → cuántos '(' tenemos abiertos actualmente en el path
 * path      → buffer temporal donde se construye la solución
 * depth     → posición actual dentro del path
 */
void	dfs(char *s, int pos, int len, int remOpen, int remClose, int openCount,
		char *path, int depth)
{
	char	c;

	// Si llegamos al final de la cadena (caso base)
	if (pos == len)
	{
		// Validamos: no deben quedar paréntesis por eliminar,
		// ni paréntesis abiertos sin cerrar
		if (remOpen == 0 && remClose == 0 && openCount == 0)
		{
			path[depth] = '\0'; // terminamos la cadena
			putstr_ln(path);    // imprimimos solución válida
		}
		return ;
	}
	c = s[pos];
	// Caso: '('
	if (c == '(')
	{
		// Opción 1: eliminar este '(' si todavía podemos
		if (remOpen > 0)
			dfs(s, pos + 1, len, remOpen - 1, remClose, openCount, path, depth);
		// Opción 2: mantenerlo
		path[depth] = '(';
		dfs(s, pos + 1, len, remOpen, remClose, openCount + 1, path, depth + 1);
	}
	// Caso: ')'
	else if (c == ')')
	{
		// Opción 1: eliminar este ')'
		if (remClose > 0)
			dfs(s, pos + 1, len, remOpen, remClose - 1, openCount, path, depth);
		// Opción 2: mantenerlo si existe un '(' abierto para emparejar
		if (openCount > 0)
		{
			path[depth] = ')';
			dfs(s, pos + 1, len, remOpen, remClose, openCount - 1, path, depth
				+ 1);
		}
	}
	// Cualquier otro carácter (no aplica aquí,pero queda genérico,lo copiamos al path)
	else
	{
		path[depth] = c;
		dfs(s, pos + 1, len, remOpen, remClose, openCount, path, depth + 1);
	}
}

int	main(int argc, char **argv)
{
	char	*s;
	int		len;
	char	path[1024];

	len = 0;
	// error si el numero de args es distinto a 0
	if (argc != 2)
		return (0);
	s = argv[1];
	int remOpen, remClose;
	count_removals(s, &remOpen, &remClose);
	// calculamos los paréntesis sobrantes a eliminar.
	// buffer donde construiremos soluciones
	while (s[len]) // obtenemos longitud de la cadena
		len++;
	dfs(s, 0, len, remOpen, remClose, 0, path, 0); // iniciamos DFS
	return (0);
}
