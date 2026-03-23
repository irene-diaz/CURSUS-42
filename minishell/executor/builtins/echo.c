/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:21:01 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/09 17:36:54 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== ECHO ==================== */

/* Check if the argument is the -n flag for echo */
static int	is_n_flag(char *s)
{
	int	i;

	i = 1;
	if (!s || s[0] != '-')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/* Handle the exit code for the echo command */
static int	handle_echo_exitcode(t_cmd *cmd)
{
	if (!cmd->cmd[1])
		return (0);
	if (ft_strncmp(cmd->cmd[1], "$?", 2) == 0)
	{
		if (cmd->exitcode)
			printf("%d\n", *cmd->exitcode);
		else
			printf("0\n");
		if (cmd->exitcode)
			*cmd->exitcode = 0;
		if (!cmd->cmd[2])
			return (1);
	}
	return (0);
}

/* Print the arguments for the echo command */
static void	print_echo_arguments(t_cmd *cmd, int i, int newline)
{
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], 1);
		if (cmd->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	if (cmd->exitcode)
		*cmd->exitcode = 0;
}

/* Execute the echo command. */
void	exec_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (handle_echo_exitcode(cmd))
		return ;
	while (cmd->cmd[i] && is_n_flag(cmd->cmd[i]))
	{
		newline = 0;
		i++;
	}
	print_echo_arguments(cmd, i, newline);
}
