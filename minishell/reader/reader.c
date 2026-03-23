/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:35:20 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/12 09:47:58 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Build the shell prompt */
static char	*build_prompt(int continuation)
{
	char	path[1024];
	char	*hostname;
	char	*user;
	char	*prompt;
	char	*tmp;

	if (continuation)
		return (ft_strdup("> "));
	user = getenv("USER");
	if (!user)
		user = "user";
	hostname = "minishell";
	getcwd(path, sizeof(path));
	prompt = ft_strjoin(GREEN, user);
	tmp = ft_strjoin(prompt, "@");
	free(prompt);
	prompt = ft_strjoin(tmp, hostname);
	free(tmp);
	tmp = ft_strjoin(prompt, ": " RESET BLUE);
	free(prompt);
	prompt = ft_strjoin(tmp, path);
	free(tmp);
	tmp = ft_strjoin(prompt, RESET "$ ");
	free(prompt);
	return (tmp);
}

/* Handle leftover input from the previous line */
static char	*handle_leftover(t_arena *arena, int leftover[2])
{
	char	buf[4096];
	int		bytes;
	int		i;
	char	c;

	if (leftover[0] > 0)
	{
		ioctl(leftover[0], FIONREAD, &bytes);
		if (bytes > 0)
		{
			i = 0;
			while (read(leftover[0], &c, 1) > 0 && c != '\n')
				buf[i++] = c;
			buf[i] = '\0';
			return (ft_strdup_arena(arena, buf));
		}
	}
	return (NULL);
}

/* Read a line of input with a prompt */
static char	*read_line_with_prompt(int continuation, int leftover[2])
{
	char	*prompt;
	char	*tmp;
	char	*newline;

	prompt = build_prompt(continuation);
	tmp = readline(prompt);
	free(prompt);
	if (!tmp)
		return (NULL);
	newline = ft_strchr(tmp, '\n');
	if (newline)
	{
		*newline = '\0';
		write(leftover[1], newline + 1, ft_strlen(newline + 1));
		write(leftover[1], "\n", 1);
	}
	return (tmp);
}

/* Read and process lines of input */
static char	*read_and_process_lines(t_arena *arena, int leftover[2],
		int *open_double, int *open_single)
{
	char	*full_line;
	char	*tmp;

	full_line = NULL;
	while (1)
	{
		tmp = read_line_with_prompt(*open_double || *open_single, leftover);
		if (!tmp)
			return (NULL);
		update_quote_flags(tmp, open_double, open_single);
		append_line(arena, &full_line, tmp);
		free(tmp);
		if (!*open_double && !*open_single)
			break ;
	}
	return (full_line);
}

/* Read a line of input with a prompt */
char	*reader(t_arena *arena, char **envp, int leftover[2])
{
	char	*full_line;
	int		open_double;
	int		open_single;

	open_double = 0;
	open_single = 0;
	(void)envp;
	full_line = handle_leftover(arena, leftover);
	if (full_line)
		return (full_line);
	full_line = read_and_process_lines(arena, leftover, &open_double,
			&open_single);
	if (full_line && *full_line)
		add_history(full_line);
	return (full_line);
}
