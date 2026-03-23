/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:46:18 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 13:15:44 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Get the operator type from a string */
t_operator	get_operator(char *str)
{
	if (str == NULL)
		return (NONE);
	else if (!ft_strncmp(str, "||", 3))
		return (OR);
	else if (!ft_strncmp(str, "&&", 3))
		return (AND);
	else if (!ft_strncmp(str, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(str, "(", 2))
		return (OPEN_SUBSHELL);
	else if (!ft_strncmp(str, ")", 2))
		return (CLOSE_SUBSHELL);
	return (NONE);
}

/*
	else if (!ft_strncmp(str, ";", 2))
		return (SEMICOLON);
*/

/* Get the next operator in the command */
char	**get_next_operator(char **cmd)
{
	while (cmd && *cmd && get_operator(*cmd) == NONE)
		cmd++;
	return (cmd);
}

/* Get the command after a closing parenthesis */
char	**after_closing_parenth(char **cmd)
{
	int	counter;

	counter = 1;
	cmd++;
	while (*cmd && counter)
	{
		if (!ft_strncmp(*cmd, "(", 2))
			counter++;
		else if (!ft_strncmp(*cmd, ")", 2))
			counter--;
		cmd++;
	}
	return (cmd);
}

/* Get the next command in the chain */
char	**get_next_cmd(t_cmd *group, char **cmd)
{
	if (group->operator == NONE)
		return (get_next_operator(cmd));
	else if (group->operator == OPEN_SUBSHELL)
		return (after_closing_parenth(cmd));
	else if (group->operator == CLOSE_SUBSHELL)
		return (NULL);
	else
		return (&(cmd[1]));
}

/* Copy a tab until an operator is found */
char	**copy_tab_until_operator(t_arena *arena, char **tab)
{
	int		size;
	int		i;
	char	**ret;

	if (tab == NULL)
		return (NULL);
	size = 0;
	while (tab[size] && get_operator(tab[size]) == NONE)
		size++;
	ret = arena_alloc(arena, sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	ret[size] = NULL;
	i = 0;
	while (i < size)
	{
		ret[i] = tab[i];
		i++;
	}
	return (ret);
}
