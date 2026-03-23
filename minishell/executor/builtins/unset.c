/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:21:43 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/09 17:55:53 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== UNSET ==================== */

/* Count the number of environment variables */
static int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

/* Copy the environment variables */
static void	copy_env_vars(char **old_env, char **new_env, char *key, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old_env[i])
	{
		if (!(ft_strncmp(old_env[i], key, len) == 0 && old_env[i][len] == '='))
			new_env[j++] = old_env[i];
		else
			free(old_env[i]);
		i++;
	}
	new_env[j] = NULL;
}

/* Remove an environment variable */
static void	remove_env(t_cmd *cmd, char *key)
{
	int		len;
	char	**old_env;
	char	**new_env;
	int		count;

	old_env = *cmd->env_ptr;
	len = ft_strlen(key);
	count = count_env_vars(old_env);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return ;
	copy_env_vars(old_env, new_env, key, len);
	free(old_env);
	*cmd->env_ptr = new_env;
}

/* Execute the unset command */
void	exec_unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd[i])
	{
		remove_env(cmd, cmd->cmd[i]);
		i++;
	}
	*cmd->exitcode = 0;
}
