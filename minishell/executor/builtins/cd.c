/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:20:39 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/09 17:35:42 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== CD ==================== */

/*
 * Get the HOME directory from the environment.
 * If HOME is not set, try to construct it from the USER variable.
 * If show_error is true and HOME is not set,
	print an error message and return NULL.
 */
static char	*get_home_or_null(t_cmd *cmd, int show_error)
{
	char	*home;
	char	*user;

	home = get_env_var(cmd, "HOME");
	if (!home)
	{
		if (show_error)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			if (cmd->exitcode)
				*cmd->exitcode = 1;
			return (NULL);
		}
		user = getenv("USER");
		if (user)
		{
			home = ft_strjoin("/home/", user);
		}
	}
	return (home);
}

/*
 * Get the target directory for the cd command.
 * If no argument is given, use the HOME directory.
 * If the argument starts with ~, replace it with the HOME directory.
 */
static char	*get_cd_dir(t_cmd *cmd)
{
	char	*home;

	if (!cmd->cmd[1] || cmd->cmd[1][0] == '\0')
		return (get_home_or_null(cmd, 1));
	if (cmd->cmd[1][0] == '~')
	{
		home = get_home_or_null(cmd, 0);
		if (!home)
			return (NULL);
		if (cmd->cmd[1][1] == '\0')
			return (home);
		return (ft_strjoin_arena(cmd->arena, home, &cmd->cmd[1][1]));
	}
	return (cmd->cmd[1]);
}

/*
 * Execute the cd command.
 */
void	exec_cd(t_cmd *cmd)
{
	char	*dir;

	dir = get_cd_dir(cmd);
	if (!dir)
		return ;
	if (chdir(dir) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		if (cmd->exitcode)
			*cmd->exitcode = 1;
	}
	else
	{
		if (cmd->exitcode)
			*cmd->exitcode = 0;
	}
}
