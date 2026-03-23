/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 09:02:42 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 11:14:39 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Check if a command is a single built-in command */
int	is_single_builtin(t_cmd *cmd)
{
	if (!cmd->cmd || !cmd->cmd[0] || cmd->next)
		return (0);
	return (!ft_strncmp(cmd->cmd[0], "cd", 3) || !ft_strncmp(cmd->cmd[0],
			"export", 7) || !ft_strncmp(cmd->cmd[0], "unset", 6)
		|| !ft_strncmp(cmd->cmd[0], "exit", 5));
}

/* Execute a single built-in command */
void	exec_single_builtin(t_cmd *cmd, int *exit_status)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (cmd->infile != STDIN_FILENO)
		dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile != STDOUT_FILENO)
		dup2(cmd->outfile, STDOUT_FILENO);
	exec_builtin(cmd);
	*exit_status = *(cmd->exitcode);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	if (cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
}

/* Run a command */
static void	run_cmd(t_cmd *cmd_list, int *exit_status)
{
	int	result;

	if (is_single_builtin(cmd_list))
		exec_single_builtin(cmd_list, exit_status);
	else
	{
		result = execute_chain(cmd_list);
		if (result != -1)
			*exit_status = result;
		set_signals_interactive();
	}
}

/* Run a single iteration of the interactive loop: read input, tokenize, parse,
 */
static int	run_loop_iteration(char ***mini_env, int *exit_status, int lft[2])
{
	t_arena	*arena;
	char	**tokens;
	t_cmd	*cmd_list;
	char	*line;

	arena = arena_init(1024);
	line = reader(arena, *mini_env, lft);
	if (g_signal == 130)
	{
		*exit_status = 130;
		g_signal = 0;
	}
	if (!line)
		return (arena_destroy(arena), 0);
	tokens = tokenizer(arena, line);
	if (!is_valid_syntax(tokens, exit_status))
		return (arena_destroy(arena), 1);
	cmd_list = parser(arena, tokens, mini_env, exit_status);
	if (!cmd_list)
		return (arena_destroy(arena), 1);
	if (!parse_heredoc(cmd_list, lft))
		return (arena_destroy(arena), 1);
	expander(cmd_list);
	run_cmd(cmd_list, exit_status);
	return (arena_destroy(arena), 1);
}

/* Run the interactive loop: read input, tokenize, parse,
	expand and execute commands until EOF or exit */
void	run_interactive_loop(char ***mini_env, int *exit_status, int lft[2])
{
	while (run_loop_iteration(mini_env, exit_status, lft))
		;
}
