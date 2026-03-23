/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:19:30 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 11:31:34 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Print a syntax error message */
int	syntax_error(const char *token, int *exitcode)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, "syntax error near unexpected token '", 36);
	if (token && token[0] == '\n')
		write(STDERR_FILENO, "newline", 7);
	else if (token)
		write(STDERR_FILENO, token, ft_strlen(token));
	else
		write(STDERR_FILENO, "(NULL)", 6);
	write(STDERR_FILENO, "'\n", 2);
	*exitcode = 2;
	return (0);
}

/* Check for control operators */
int	is_control_operator(const char *token)
{
	if (token[0] == '|' && token[1] == '|')
		return (2);
	else if (token[0] == '|')
		return (1);
	else if (token[0] == '&' && token[1] == '&')
		return (2);
	else if (token[0] == '(')
		return (1);
	else if (token[0] == ')')
		return (1);
	return (0);
}

/*
	else if (token[0] == ';')
		return (1);
*/

/* Check for meta characters */
int	is_meta_char(const char c)
{
	if (c == ' ')
		return (1);
	else if (c == '\t')
		return (1);
	else if (c == '\n')
		return (1);
	else if (c == '|')
		return (1);
	else if (c == '&')
		return (1);
	else if (c == '(')
		return (1);
	else if (c == ')')
		return (1);
	else if (c == '<')
		return (1);
	else if (c == '>')
		return (1);
	return (0);
}

/* Check for redirection operators */
int	is_redirect(const char *cmd)
{
	if (!ft_strncmp(cmd, "<<", 3))
		return (1);
	else if (!ft_strncmp(cmd, ">>", 3))
		return (1);
	else if (!ft_strncmp(cmd, "<", 2))
		return (1);
	else if (!ft_strncmp(cmd, ">", 2))
		return (1);
	return (0);
}

/* Check for quotation marks */
int	is_quotation(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}
