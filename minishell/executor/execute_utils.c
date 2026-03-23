/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:22:05 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/16 16:45:43 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Execute the command in the child process: try builtin first,
 * otherwise resolve path and execve. Exits the child on failure.
 */
void	child_exec_cmd(t_cmd *cmd)
{
	char	*path;

	if (cmd->redir_error)
		exit(1);
	if (cmd->subshell)
		exit(execute_chain(cmd->subshell));
	if (exec_builtin(cmd))
		exit(*cmd->exitcode);
	if (!cmd->cmd || !cmd->cmd[0])
		exit(0);
	path = resolve_path(cmd->arena, cmd->cmd[0], *(cmd->env_ptr));
	if (!path)
	{
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->cmd, *(cmd->env_ptr));
	perror("execve");
	exit(1);
}

/* Get the PATH environment variable */
static char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

/* Find the executable in the given paths */
static char	*find_executable_in_paths(t_arena *arena, char *cmd, char **paths)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_arena(arena, paths[i], "/");
		full_path = ft_strjoin_arena(arena, full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

/* Resolve the command path */
char	*resolve_path(t_arena *arena, char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split_arena(path_env, ':', arena);
	if (!paths)
		return (NULL);
	return (find_executable_in_paths(arena, cmd, paths));
}

/*function to determine if the command should be skipped based on the
operator and exit code*/
int	should_skip(t_operator incoming_op, int exitcode)
{
	if (incoming_op == AND && exitcode != 0)
		return (1);
	if (incoming_op == OR && exitcode == 0)
		return (1);
	return (0);
}
