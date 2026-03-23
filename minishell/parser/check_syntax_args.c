/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:24:28 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 10:59:34 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Check for left argument of a control operator */
int	check_left_arg(char **cmd, int index, int *exitcode)
{
	int	j;

	j = index - 1;
	while (j >= 0 && (cmd[j][0] == ')' || cmd[j][0] == '('))
		j--;
	if (j < 0)
		return (syntax_error(cmd[index], exitcode), 0);
	if (is_control_operator(cmd[j]))
		return (syntax_error(cmd[j], exitcode), 0);
	return (1);
}

/* Check for right argument of a control operator */
int	check_right_arg(char **cmd, int index, int *exitcode)
{
	int	j;

	j = index + 1;
	while (cmd[j] && (cmd[j][0] == '(' || cmd[j][0] == ')'))
		j++;
	if (cmd[j] == NULL)
		return (syntax_error(cmd[index], exitcode), 0);
	if (is_control_operator(cmd[j]))
		return (syntax_error(cmd[j], exitcode), 0);
	return (1);
}

/* Check for redirection operators */
int	check_redirect(char **cmd, int *exitcode)
{
	if (!is_redirect(*cmd))
		return (1);
	if (*(cmd + 1) == NULL || is_meta_char(cmd[1][0]))
	{
		syntax_error(cmd[1], exitcode);
		return (0);
	}
	return (1);
}

/* Check for unclosed quotes("" or '') */
int	check_quotes(const char *str)
{
	char	quote;

	while (*str)
	{
		while (*str && !is_quotation(*str))
			str++;
		if (*str == 0)
			return (1);
		quote = *str;
		str++;
		while (*str && *str != quote)
			str++;
		if (*str == 0)
			return (0);
		str++;
	}
	return (1);
}

/* Check for balanced parentheses */
int	check_parentheses(char **cmd, int *exitcode)
{
	int	count;

	count = 1;
	while (*cmd)
	{
		if (**cmd == '(' && cmd[1] && cmd[1][0] == ')')
		{
			syntax_error("empty parentheses", exitcode);
			return (0);
		}
		if (**cmd == '(')
			count++;
		if (**cmd == ')')
			count--;
		cmd++;
	}
	if (count != 1)
	{
		syntax_error("missing parenthesis", exitcode);
		return (0);
	}
	return (1);
}
