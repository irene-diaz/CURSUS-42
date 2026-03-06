/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:56:32 by oem               #+#    #+#             */
/*   Updated: 2026/03/06 17:36:11 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== CD ==================== */

/* Obtiene el directorio HOME o NULL si no está definido */
static char	*get_home_or_null(t_cmd *cmd, int show_error)
{
	char	*home;
	char	*user;

	home = get_env_var(cmd, "HOME"); // Obtener el directorio HOME
	/* Si no se encuentra el directorio HOME, se muestra un mensaje de error */
	if (!home)
	{
		/* Si no se encuentra el directorio HOME,
			se muestra un mensaje de error */
		if (show_error)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			if (cmd->exitcode)
				*cmd->exitcode = 1;
			return (NULL);
		}
		user = getenv("USER");
		/* Si no se encuentra el directorio HOME,
			se intenta construir uno a partir del nombre de usuario */
		if (user)
		{
			home = ft_strjoin("/home/", user);
		}
	}
	return (home);
}

/* Obtiene el directorio a cambiar (HOME o el especificado) */
static char	*get_cd_dir(t_cmd *cmd)
{
	char	*home;

	// Obtener el directorio a cambiar
	if (!cmd->cmd[1] || cmd->cmd[1][0] == '\0')
		return (get_home_or_null(cmd, 1));
	// Si el directorio comienza con ~, se expande a HOME
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

/* Ejecuta el comando cd */
void	exec_cd(t_cmd *cmd)
{
	char	*dir;

	// Obtener el directorio a cambiar
	dir = get_cd_dir(cmd);
	if (!dir)
		return ;
	// Si el directorio es inválido, se muestra un mensaje de error
	if (chdir(dir) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		if (cmd->exitcode)
			*cmd->exitcode = 1;
	}
	// Si el directorio es válido, se actualiza el directorio actual
	else
	{
		if (cmd->exitcode)
			*cmd->exitcode = 0;
	}
}
