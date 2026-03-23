/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:40:53 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 13:15:03 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Get the length of the variable key */
int	get_keylen(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

/* Get the value of an environment variable */
char	*get_env_value(t_cmd *cmd, char *key)
{
	int	i;
	int	len_until_eq;

	if (!ft_strncmp(key, "?", 1))
		return (ft_itoa_arena(cmd->arena, *cmd->exitcode));
	i = 0;
	while ((*cmd->env_ptr)[i])
	{
		len_until_eq = 0;
		while ((*cmd->env_ptr)[i][len_until_eq] != '=')
			len_until_eq++;
		if (!ft_strncmp(key, (*cmd->env_ptr)[i], len_until_eq))
			return (ft_strdup_arena(cmd->arena, (*cmd->env_ptr)[i]
				+ len_until_eq + 1));
		i++;
	}
	return (ft_strdup_arena(cmd->arena, ""));
}

/* Get the next dollar sign in the command */
void	get_next_dolar(t_cmd *cmd, int word_index)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (cmd->cmd[word_index][i])
	{
		if (quote == cmd->cmd[word_index][i])
			quote = 0;
		else if (!quote && (cmd->cmd[word_index][i] == '"'
			|| cmd->cmd[word_index][i] == '\''))
			quote = cmd->cmd[word_index][i];
		else if (quote != '\'' && cmd->cmd[word_index][i] == '$'
			&& cmd->cmd[word_index][i + 1] != '\0'
			&& (ft_isalnum(cmd->cmd[word_index][i + 1])
			|| cmd->cmd[word_index][i + 1] == '?'))
		{
			cmd->cmd[word_index] = expand_var(cmd, cmd->cmd[word_index], i);
			continue ;
		}
		i++;
	}
}
