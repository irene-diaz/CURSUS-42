/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:34:30 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/10 13:38:32 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Free the environment variables */
void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

/* Check if the string is a valid identifier for an environment variable */
static int	is_valid_identifier(char *s)
{
	int	i;

	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* Handle invalid identifier for export command */
int	handle_invalid_identifier(t_cmd *cmd, char *identifier)
{
	if (!is_valid_identifier(identifier))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(identifier, 2);
		ft_putstr_fd("' : not a valid identifier\n", 2);
		if (cmd->exitcode)
			*cmd->exitcode = 1;
		return (1);
	}
	return (0);
}

/* Copy the environment variables */
char	**copy_env(char **envp)
{
	int		i;
	char	**new;

	i = 0;
	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i])
			return (NULL);
		i++;
	}
	new[i] = NULL;
	return (new);
}

/* Get the value of an environment variable */
char	*get_env_var(t_cmd *cmd, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while ((*cmd->env_ptr)[i])
	{
		if (!ft_strncmp((*cmd->env_ptr)[i], key, len)
			&& (*cmd->env_ptr)[i][len] == '=')
			return ((*cmd->env_ptr)[i] + len + 1);
		i++;
	}
	return (NULL);
}
