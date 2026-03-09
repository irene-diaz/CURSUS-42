/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:26:25 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/09 18:03:37 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Check if the token is a redirection operator */
int	is_redirection(char *token)
{
	if (!ft_strncmp(token, ">>", 3))
		return (1);
	else if (!ft_strncmp(token, ">", 2))
		return (1);
	else if (!ft_strncmp(token, "<", 2) && ft_strncmp(token, "<<", 3))
		return (1);
	return (0);
}

/* Open the redirection files */
void	open_redirections(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd && cmd->cmd[i])
	{
		if (!ft_strncmp(cmd->cmd[i], ">>", 3))
			cmd->outfile = open(cmd->cmd[i + 1], O_CREAT | O_WRONLY | O_APPEND,
					0644);
		else if (!ft_strncmp(cmd->cmd[i], ">", 2))
			cmd->outfile = open(cmd->cmd[i + 1], O_CREAT | O_WRONLY | O_TRUNC,
					0644);
		else if (!ft_strncmp(cmd->cmd[i], "<", 2) && ft_strncmp(cmd->cmd[i],
				"<<", 3))
			cmd->infile = open(cmd->cmd[i + 1], O_RDONLY);
		i++;
	}
}

/* Apply the redirections */
void	apply_redirections(t_cmd *cmd)
{
	if (cmd->heredoc != STDIN_FILENO)
		dup2(cmd->heredoc, STDIN_FILENO);
	else if (cmd->infile != STDIN_FILENO)
		dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile != STDOUT_FILENO)
		dup2(cmd->outfile, STDOUT_FILENO);
}
