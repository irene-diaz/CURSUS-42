/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:51:07 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 13:16:14 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Handle heredoc interruption */
void	interrupt_heredoc(int sig)
{
	write(STDERR_FILENO, "\n", 1);
	exit(130);
	(void)sig;
}

/* Read a line from the heredoc */
char	*read_heredoc_line(int leftover[2])
{
	char	buf[4096];
	int		i;
	char	c;
	int		bytes;

	ioctl(leftover[0], FIONREAD, &bytes);
	if (bytes <= 0)
		return (readline("> "));
	i = 0;
	while (read(leftover[0], &c, 1) > 0 && c != '\n')
		buf[i++] = c;
	buf[i] = '\0';
	return (strdup(buf));
}

/* Write heredoc content interactively */
void	write_heredoc_interactive(t_cmd *cmd, char *eof, int pipefd[2],
		int leftover[2])
{
	char	*line;

	(void)cmd;
	close(pipefd[0]);
	signal(SIGINT, interrupt_heredoc);
	while (1)
	{
		line = read_heredoc_line(leftover);
		if (!line || !ft_strncmp(line, eof, ft_strlen(eof) + 1))
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	exit(0);
}

/* Write heredoc content interactively */
void	write_heredoc_pasted(char **tokens, char *eof, int pipefd[2], int *j)
{
	while (tokens[*j] && ft_strncmp(tokens[*j], eof, ft_strlen(eof) + 1))
	{
		write(pipefd[1], tokens[*j], ft_strlen(tokens[*j]));
		write(pipefd[1], "\n", 1);
		(*j)++;
	}
	if (tokens[*j])
		(*j)++;
}
