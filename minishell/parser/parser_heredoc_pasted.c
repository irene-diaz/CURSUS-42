/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_pasted.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:58:03 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 11:04:57 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Check for pasted content in the heredoc */
int	has_pasted_content(char **tokens, int j, char *eof)
{
	while (tokens[j])
	{
		if (!ft_strncmp(tokens[j], eof, ft_strlen(eof) + 1))
			return (1);
		j++;
	}
	return (0);
}

/* Handle pasted content in the heredoc */
int	handle_heredoc_pasted(t_cmd *cmd, char *eof, int pipefd[2], int j)
{
	int	k;

	k = j;
	write_heredoc_pasted(cmd->cmd, eof, pipefd, &j);
	while (cmd->cmd[j])
		cmd->cmd[k++] = cmd->cmd[j++];
	cmd->cmd[k] = NULL;
	close(pipefd[1]);
	if (cmd->heredoc != STDIN_FILENO)
		close(cmd->heredoc);
	cmd->heredoc = pipefd[0];
	return (1);
}
