void	print_maze(int height, int width, char **maze)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			putchar(maze[i][j]);
			j++;
		}
		putchar('\n');
		i++;
	}
}

char	**next_gen(int height, int width, char **maze)
{
	int		i;
	int		j;
	char	**next;
	int		row_offset;
	int		col_offset;
	int		neighbors;
	int		row_neighbors;
	int		col_neighbors;

	i = 0;
	next = malloc(height * sizeof(char *));
	while (i < height)
	{
		j = 0;
		next[i] = malloc(width * sizeof(char));
		while (j < width)
		{
			next[i][j] = ' ';
			j++;
		}
		i++;
	}
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			row_offset = -1;
			neighbors = 0;
			while (row_offset <= 1)
			{
				col_offset = -1;
				while (col_offset <= 1)
				{
					if (!(row_offset == 0 && col_offset == 0))
					{
						row_neighbors = row_offset + i;
						col_neighbors = col_offset + j;
						if (row_neighbors >= 0 && row_neighbors < height
							&& col_neighbors >= 0 && col_neighbors < width)
						{
							if (maze[row_neighbors][col_neighbors] == '0')
								neighbors++;
						}
					}
					col_offset++;
				}
				row_offset++;
			}
			if (maze[i][j] == '0' && (neighbors == 2 || neighbors == 3))
				next[i][j] = '0';
			else if (maze[i][j] == ' ' && neighbors == 3)
				next[i][j] = '0';
			j++;
		}
		i++;
	}
	return (next);
}

int	main(int argc, char **argv)
{
	if (argc != 4)
		return (1);

	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int N = atoi(argv[3]);

	char **maze;

	int i;
	int j;

	maze = malloc(height * sizeof(char *));
	i = 0;

	while (i < height)
	{
		j = 0;
		maze[i] = malloc(width * sizeof(char));
		while (j < width)
		{
			maze[i][j] = ' ';
			j++;
		}
		i++;
	}

	int py = 0, px = 0, drawing = 0;
	char cmd;

	while (read(0, &cmd, 1) == 1)
	{
		if (cmd == 'x')
			drawing = !drawing;
		else if (cmd == 'w' && py > 0)
			py--;
		else if (cmd == 's' && py < height - 1)
			py++;
		else if (cmd == 'a' && px > 0)
			px--;
		else if (cmd == 'd' && px < width - 1)
			px++;
		if (drawing)
			maze[py][px] = '0';
	}

	i = 0;
	while (i < N)
	{
		char **next = next_gen(height, width, maze);
		j = 0;
		while (j < height)
		{
			free(maze[j]);
			j++;
		}
		free(maze);
		maze = next;
		i++;
	}

	print_maze(height, width, maze);
	i = 0;
	while (i < height)
	{
		free(maze[i]);
		i++;
	}
	free(maze);

	return (0);
}