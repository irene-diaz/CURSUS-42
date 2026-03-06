/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:32:52 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/06 16:46:28 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_cmd_list(t_cmd *cmd)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	int		status;
	char	*path;
	t_cmd	*last_cmd;

	if (!cmd)
		return (-1);
	/* 🔥 IGNORAR SIGINT EN EL PADRE MIENTRAS EJECUTA */
	signal(SIGINT, SIG_IGN);
	prev_fd = -1;
	// Encontramos el último comando de la lista
	last_cmd = cmd;
	while (last_cmd->next)
		last_cmd = last_cmd->next;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		/*==============HIJO==============*/
		if (pid == 0)
		{
			set_signals_child();
			/* STDIN: heredoc > infile > prev_fd*/
			if (cmd->heredoc != STDIN_FILENO)
				dup2(cmd->heredoc, STDIN_FILENO); // heredoc tiene prioridad
			else if (cmd->infile != STDIN_FILENO)
				dup2(cmd->infile, STDIN_FILENO);
			else if (prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO);
			/* STDOUT: outfile > pipe */
			if (cmd->outfile != STDOUT_FILENO)
				dup2(cmd->outfile, STDOUT_FILENO);
			else if (cmd->next)
				dup2(fd[1], STDOUT_FILENO);
			// cerrar fds heredoc
			if (cmd->heredoc != STDIN_FILENO)
				close(cmd->heredoc);
			/* cerrar fds innecesarios */
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->infile != STDIN_FILENO)
				close(cmd->infile);
			if (cmd->outfile != STDOUT_FILENO)
				close(cmd->outfile);
			if (cmd->heredoc != STDIN_FILENO)
				close(cmd->heredoc);
			if (cmd->next)
			{
				close(fd[0]);
				close(fd[1]);
			}
			/* builtins que SÍ pueden ir en hijo */
			if (exec_builtin(cmd))
				exit(*cmd->exitcode);
			if (!cmd->cmd || !cmd->cmd[0])
				exit(0);
			/* Ejecutar binario externo */
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
		/*=============PADRE=============*/
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->infile != STDIN_FILENO)
			close(cmd->infile);
		if (cmd->outfile != STDOUT_FILENO)
			close(cmd->outfile);
		if (cmd->heredoc != STDIN_FILENO)
		{
			close(cmd->heredoc);
			cmd->heredoc = STDIN_FILENO;
		}
		if (cmd->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		cmd = cmd->next;
	}
	// Esperar a todos los hijos
	status = 0;
	while (wait(&status) > 0)
		;
	/* Restaurar señales interactivas 🔥 */
	set_signals_interactive();
	// Actualizar exitcode del último comando
	if (last_cmd)
	{
		if (WIFEXITED(status))
			*(last_cmd->exitcode) = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			*(last_cmd->exitcode) = 128 + WTERMSIG(status);
		}
	}
	// Retornar exitcode si hay comandos, sino -1
	return (last_cmd ? *(last_cmd->exitcode) : -1);
}
