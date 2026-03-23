/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_chain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:13:17 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/16 16:55:28 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*function to negate the exit code*/
static void	negate_exitcode(int *exitcode)
{
	if (*exitcode == 0)
		*exitcode = 1;
	else
		*exitcode = 0;
}

/*function to check if a command is a state builtin*/
static int	is_state_builtin(char *name)
{
	return (ft_strncmp(name, "cd", 3) == 0 || ft_strncmp(name, "export", 7) == 0
		|| ft_strncmp(name, "unset", 6) == 0 || ft_strncmp(name, "exit",
			5) == 0);
}

/*function to process a command group*/
static int	process_group(t_cmd *group, int *exitcode)
{
	if (group->operator != PIPE && group->cmd && group->cmd[0]
		&& is_state_builtin(group->cmd[0]))
	{
		exec_builtin(group);
		*exitcode = *group->exitcode;
	}
	else
	{
		*exitcode = execute_cmd_list(group);
	}
	return (*exitcode);
}

/*function to execute a group of commands*/
static int	execute_groups(t_cmd *cmd)
{
	t_cmd		*group;
	t_operator	incoming_op;
	t_operator	outgoing_op;
	int			exitcode;

	group = cmd;
	incoming_op = NONE;
	exitcode = 0;
	while (group)
	{
		if (should_skip(incoming_op, exitcode))
		{
			group = next_group(group, &outgoing_op);
			incoming_op = outgoing_op;
			continue ;
		}
		process_group(group, &exitcode);
		group = next_group(group, &outgoing_op);
		incoming_op = outgoing_op;
	}
	return (exitcode);
}

/*function to execute a chain of commands*/
int	execute_chain(t_cmd *cmd)
{
	int	exitcode;
	int	negate;

	if (!cmd)
		return (-1);
	exitcode = 0;
	negate = 0;
	if (cmd->cmd && cmd->cmd[0] && ft_strncmp(cmd->cmd[0], "!", 2) == 0)
	{
		negate = 1;
		cmd->cmd = &cmd->cmd[1];
	}
	exitcode = execute_groups(cmd);
	if (negate)
		negate_exitcode(&exitcode);
	if (cmd->exitcode)
		*cmd->exitcode = exitcode;
	return (exitcode);
}
