/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:51:58 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 13:07:09 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Wait for heredoc process to finish */
int	wait_heredoc(t_cmd *cmd, pid_t pid, int pipefd[2])
{
	int	status;

	waitpid(pid, &status, 0);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		*cmd->exitcode = 130;
		close(pipefd[0]);
		set_signals_interactive();
		return (0);
	}
	if (WIFEXITED(status))
		*cmd->exitcode = WEXITSTATUS(status);
	if (cmd->heredoc != STDIN_FILENO)
		close(cmd->heredoc);
	cmd->heredoc = pipefd[0];
	set_signals_interactive();
	return (1);
}

/* Handle heredoc forking */
static int	handle_heredoc_fork(t_cmd *cmd, char *eof, int pipefd[2],
		int leftover[2])
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (close(pipefd[0]), close(pipefd[1]), 0);
	if (pid == 0)
		write_heredoc_interactive(cmd, eof, pipefd, leftover);
	close(pipefd[1]);
	return (wait_heredoc(cmd, pid, pipefd));
}

/* Check for unclosed quotes("" or '') */
static int	handle_heredoc(t_cmd *cmd, int i, int leftover[2])
{
	int		pipefd[2];
	char	*eof;

	eof = cmd->cmd[i + 1];
	if (*eof == '"' || *eof == '\'')
	{
		cmd->heredoc_quoted = 1;
		remove_quotes(eof);
	}
	if (pipe(pipefd) == -1)
		return (0);
	if (has_pasted_content(cmd->cmd, i + 2, eof))
		return (handle_heredoc_pasted(cmd, eof, pipefd, i + 2));
	return (handle_heredoc_fork(cmd, eof, pipefd, leftover));
}

/* Check for unclosed quotes("" or '') */
int	parse_heredoc(t_cmd *cmd, int leftover[2])
{
	int	i;

	if (!cmd)
		return (1);
	while (cmd)
	{
		if (cmd->cmd)
		{
			i = 0;
			while (cmd->cmd[i])
			{
				if (!ft_strncmp(cmd->cmd[i], "<<", 2))
				{
					if (!handle_heredoc(cmd, i, leftover))
						return (0);
				}
				i++;
			}
		}
		cmd = cmd->next;
	}
	return (1);
}
