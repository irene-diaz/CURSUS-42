/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 14:13:05 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 13:04:38 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Remove the first character from a string */
void	remove_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = str[i + 1];
		i++;
	}
}

/* Remove quotes from a string */
void	remove_quotes(char *cmd)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			quote = cmd[i];
			remove_char(&cmd[i]);
			while (cmd[i] && cmd[i] != quote)
				i++;
			if (cmd[i] == quote)
				remove_char(&cmd[i]);
		}
		else
			i++;
	}
}

/* Remove a word from a string */
void	remove_word(char **cmd)
{
	while (*cmd)
	{
		*cmd = *(cmd + 1);
		cmd++;
	}
}

/* Remove redirect symbols from a command */
void	remove_redirect(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (is_redirect(cmd[i]))
		{
			remove_word(&cmd[i]);
			remove_word(&cmd[i]);
		}
		else
			i++;
	}
}

/* Check if a string has a wildcard character */
int	has_wildcard(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '*')
			return (1);
		i++;
	}
	return (0);
}
