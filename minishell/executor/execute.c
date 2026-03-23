/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:22:11 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/09 17:10:33 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Prepare child's file descriptors: set signal handlers for child,
 * duplicate heredoc/infile/pipe into STDIN and outfile/pipe into STDOUT,
 * and close file descriptors the child will not use.
 */
static void	child_setup_io(t_cmd *cmd, int prev_fd, int fd[2])
{
	set_signals_child();
	if (cmd->heredoc != STDIN_FILENO)
		dup2(cmd->heredoc, STDIN_FILENO);
	else if (cmd->infile != STDIN_FILENO)
		dup2(cmd->infile, STDIN_FILENO);
	else if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (cmd->outfile != STDOUT_FILENO)
		dup2(cmd->outfile, STDOUT_FILENO);
	else if (cmd->next && cmd->operator == PIPE)
		dup2(fd[1], STDOUT_FILENO);
	if (cmd->heredoc != STDIN_FILENO)
		close(cmd->heredoc);
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
	if (cmd->next && cmd->operator == PIPE)
	{
		close(fd[0]);
		close(fd[1]);
	}
}

/*
 * Fork a new child for the given command and start its execution.
 * Returns 0 on success, -1 on fork/pipe error.
 */
static int	start_fork(t_cmd *cmd, int *prev_fd, int fd[2])
{
	pid_t	pid;

	if (cmd->next && cmd->operator == PIPE && pipe(fd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		child_setup_io(cmd, *prev_fd, fd);
		child_exec_cmd(cmd);
	}
	return (0);
}

/*
 * Parent-side cleanup after forking a child: close used fds,
 * preserve read end of the pipe in prev_fd if piping to next cmd.
 */
static void	parent_cleanup_after_child(t_cmd *cmd, int *prev_fd, int fd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
	if (cmd->heredoc != STDIN_FILENO)
	{
		close(cmd->heredoc);
		cmd->heredoc = STDIN_FILENO;
	}
	if (cmd->next && cmd->operator == PIPE)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	else
		*prev_fd = -1;
}

/*
 * Spawn processes for the pipeline starting at cmd.
 * Returns the last command node to inspect its exitcode later.
 */
static t_cmd	*spawn_pipeline(t_cmd *cmd)
{
	int		fd[2];
	int		prev_fd;
	t_cmd	*last;
	int		ret;

	prev_fd = -1;
	last = NULL;
	while (cmd)
	{
		ret = start_fork(cmd, &prev_fd, fd);
		if (ret < 0)
			return (NULL);
		parent_cleanup_after_child(cmd, &prev_fd, fd);
		last = cmd;
		if (cmd->operator != PIPE)
			break ;
		cmd = cmd->next;
	}
	return (last);
}

/*
 * Top-level executor: spawn pipeline, wait for children and
 * set the final exit code based on last process status.
 */
int	execute_cmd_list(t_cmd *cmd)
{
	int		status;
	t_cmd	*last;

	if (!cmd)
		return (-1);
	signal(SIGINT, SIG_IGN);
	last = spawn_pipeline(cmd);
	status = 0;
	while (wait(&status) > 0)
		;
	set_signals_interactive();
	if (last)
	{
		if (WIFEXITED(status))
			*(last->exitcode) = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			*(last->exitcode) = 128 + WTERMSIG(status);
		}
		return (*(last->exitcode));
	}
	return (-1);
}
