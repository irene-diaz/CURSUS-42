/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:25:07 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 10:55:54 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Check the syntax of the command */
int	is_valid_syntax(char **cmd, int *exitcode)
{
	int	i;

	i = 0;
	if (!check_parentheses(cmd, exitcode))
		return (0);
	while (cmd[i])
	{
		if (!check_quotes(cmd[i]))
			return (syntax_error(cmd[i], exitcode), 0);
		if (is_control_operator(cmd[i]) && cmd[i][0] != '(' && cmd[i][0] != ')')
		{
			if (!check_left_arg(cmd, i, exitcode))
				return (0);
			if (!check_right_arg(cmd, i, exitcode))
				return (0);
		}
		if (cmd[i][0] == '(' && i > 0 && !is_control_operator(cmd[i - 1]))
			return (syntax_error(cmd[i], exitcode), 0);
		if (cmd[i][0] == ')' && cmd[i + 1] && !is_control_operator(cmd[i + 1]))
			return (syntax_error(cmd[i], exitcode), 0);
		if (!check_redirect(&cmd[i], exitcode))
			return (0);
		i++;
	}
	return (1);
}
