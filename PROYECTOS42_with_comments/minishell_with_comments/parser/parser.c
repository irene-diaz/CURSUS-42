#include "../includes/minishell.h"

static t_cmd	*init_cmd(t_arena *arena, char ***env_ptr, int *exitcode)
{
	t_cmd	*cmd;

	cmd = arena_alloc(arena, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->arena = arena;
	cmd->cmd = NULL;
	cmd->env_ptr = env_ptr;
	cmd->operator= NONE;
	cmd->pid = -1;
	cmd->original_stdin = STDIN_FILENO;
	cmd->original_stdout = STDOUT_FILENO;
	cmd->heredoc = STDIN_FILENO;
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->exitcode = exitcode;
	cmd->subshell = NULL;
	cmd->previous = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*parser(t_arena *arena, char **tokens, char ***env_ptr, int *exitcode)
{
	t_cmd	*cmd;

	if (!tokens || !*tokens)
		return (NULL);
	if (get_operator(*tokens) != NONE && get_operator(*tokens) != OPEN_SUBSHELL)
		tokens++;
	cmd = init_cmd(arena, env_ptr, exitcode);
	if (!cmd)
		return (NULL);
	if (get_operator(*tokens) == OPEN_SUBSHELL)
	{
		cmd->operator= OPEN_SUBSHELL;
		cmd->subshell = parser(arena, &tokens[1], env_ptr, exitcode);
		if (!cmd->subshell)
			return (NULL);
	}
	else
	{
		cmd->cmd = copy_tab_until_operator(arena, tokens);
		if (!cmd->cmd)
			return (NULL);
		while (*tokens && get_operator(*tokens) == NONE)
			tokens++;
		if (*tokens)
			cmd->operator= get_operator(*tokens);
	}
	tokens = get_next_cmd(cmd, tokens);
	if (!tokens || !*tokens || get_operator(*tokens) == CLOSE_SUBSHELL)
		return (cmd);
	cmd->next = parser(arena, tokens, env_ptr, exitcode);
	if (!cmd->next)
		return (NULL);
	cmd->next->previous = cmd;
	return (cmd);
}
