/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:47:32 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 11:06:49 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Initialize command file descriptors */
static void	init_cmd_fds(t_cmd *cmd)
{
	cmd->pid = -1;
	cmd->original_stdin = STDIN_FILENO;
	cmd->original_stdout = STDOUT_FILENO;
	cmd->leftover[0] = -1;
	cmd->leftover[1] = -1;
	cmd->heredoc = STDIN_FILENO;
	cmd->heredoc_quoted = 0;
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
}

/* Initialize command structure */
t_cmd	*init_cmd(t_arena *arena, char ***env_ptr, int *exitcode)
{
	t_cmd	*cmd;

	cmd = arena_alloc(arena, sizeof(t_cmd));
	if (cmd == NULL)
	{
		*exitcode = EXIT_GENERAL_ERROR;
		return (NULL);
	}
	cmd->arena = arena;
	cmd->cmd = NULL;
	cmd->env_ptr = env_ptr;
	cmd->operator = NONE;
	init_cmd_fds(cmd);
	cmd->exitcode = exitcode;
	cmd->subshell = NULL;
	cmd->redir_error = 0;
	cmd->previous = NULL;
	cmd->next = NULL;
	return (cmd);
}
