/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:53:41 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 11:07:55 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Expand a single line in the heredoc */
char	*expand_heredoc_line(t_cmd *cmd, char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$' && line[i + 1] != '\0' && (ft_isalnum(line[i + 1])
				|| line[i + 1] == '?'))
		{
			line = expand_var(cmd, line, i);
			continue ;
		}
		i++;
	}
	return (line);
}

/* Expand heredoc content and write it to a pipe */
void	expand_heredoc(t_cmd *cmd)
{
	int		pipefd[2];
	char	*line;
	char	*expanded;

	if (pipe(pipefd) == -1)
		return ;
	while (1)
	{
		line = get_next_line(cmd->heredoc);
		if (!line)
			break ;
		expanded = expand_heredoc_line(cmd, line);
		write(pipefd[1], expanded, ft_strlen(expanded));
		free(line);
	}
	get_next_line(-1);
	close(pipefd[1]);
	close(cmd->heredoc);
	cmd->heredoc = pipefd[0];
}

/* Expand heredoc */
void	heredocs_expander_main(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (!ft_strncmp(cmd->cmd[i], "<<", 2) && !cmd->heredoc_quoted)
			expand_heredoc(cmd);
		i++;
	}
}
