/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:53:37 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 13:07:19 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Build the variable key for expansion */
static char	*build_var_key(t_cmd *cmd, char *var, int dolar_pos, int *key_len)
{
	char	*key;

	*key_len = get_keylen(&var[dolar_pos + 1]);
	key = ft_substr_arena(cmd->arena, var, dolar_pos + 1, *key_len);
	return (get_env_value(cmd, key));
}

/* Expand a variable in a command */
char	*expand_var(t_cmd *cmd, char *var, int dolar_pos)
{
	int		key_len;
	char	*value;
	char	*first_part;
	char	*second_part;
	char	*join;

	value = build_var_key(cmd, var, dolar_pos, &key_len);
	first_part = ft_substr_arena(cmd->arena, var, 0, dolar_pos);
	second_part = ft_strdup_arena(cmd->arena, &var[dolar_pos + key_len + 1]);
	join = ft_strjoin_arena(cmd->arena, first_part, value);
	return (ft_strjoin_arena(cmd->arena, join, second_part));
}

/* Expand variables in the command */
void	expander(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		i = 0;
		if (cmd->cmd)
		{
			heredocs_expander_main(cmd);
			open_redirections(cmd);
			remove_redirect(cmd->cmd);
		}
		while (cmd->cmd && cmd->cmd[i])
		{
			expand_wildcards(cmd, i);
			get_next_dolar(cmd, i);
			remove_quotes(cmd->cmd[i]);
			i++;
		}
		cmd = cmd->next;
	}
}
