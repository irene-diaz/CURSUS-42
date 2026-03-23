/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:43:55 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 11:28:51 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Parse a simple command node (no subshell) */
static int	parse_cmd_node(t_cmd *cmd, char ***tokens, int *exitcode)
{
	cmd->cmd = copy_tab_until_operator(cmd->arena, *tokens);
	if (!cmd->cmd)
	{
		*exitcode = EXIT_GENERAL_ERROR;
		return (0);
	}
	while (**tokens && get_operator(**tokens) == NONE)
		(*tokens)++;
	if (**tokens)
		cmd->operator = get_operator(**tokens);
	return (1);
}

/* Check for subshells */
static int	parse_subshell(t_cmd *cmd, char **tokens, int *exitcode)
{
	cmd->operator = OPEN_SUBSHELL;
	cmd->subshell = parser(cmd->arena, &tokens[1], cmd->env_ptr, exitcode);
	if (!cmd->subshell && *exitcode != EXIT_SUCCESS)
		return (0);
	return (1);
}

/* Parse the next command in the chain */
static t_cmd	*parse_next(t_cmd *cmd, char **tokens, int *exitcode)
{
	tokens = get_next_cmd(cmd, tokens);
	if (!tokens || !*tokens || get_operator(*tokens) == CLOSE_SUBSHELL)
		return (cmd);
	cmd->next = parser(cmd->arena, tokens, cmd->env_ptr, exitcode);
	if (!cmd->next && *exitcode != EXIT_SUCCESS)
		return (NULL);
	if (cmd->next)
		cmd->next->previous = cmd;
	return (cmd);
}

/* Main parser function */
t_cmd	*parser(t_arena *arena, char **tokens, char ***env_ptr, int *exitcode)
{
	t_cmd	*cmd;

	if (!tokens || !*tokens)
		return (NULL);
	if (get_operator(*tokens) != NONE && get_operator(*tokens) != OPEN_SUBSHELL)
		tokens++;
	cmd = init_cmd(arena, env_ptr, exitcode);
	if (!cmd)
		return (NULL);
	if (get_operator(*tokens) == OPEN_SUBSHELL)
	{
		if (!parse_subshell(cmd, tokens, exitcode))
			return (NULL);
	}
	else
	{
		if (!parse_cmd_node(cmd, &tokens, exitcode))
			return (NULL);
	}
	return (parse_next(cmd, tokens, exitcode));
}
