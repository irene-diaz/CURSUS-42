/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:55:25 by oem               #+#    #+#             */
/*   Updated: 2026/03/12 11:27:25 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	print_spielberg_1(void)
{
	ft_putstr_fd(YELLOW "███╗   ███╗██╗███╗   ██╗"
		"██╗███████╗██╗  ██╗"
		"███████╗██╗     ██╗\n", 2);
	ft_putstr_fd("████╗ ████║██║████╗  ██║"
		"██║██╔════╝██║  ██║"
		"██╔════╝██║     ██║ \n", 2);
	ft_putstr_fd("██╔████╔██║██║██╔██╗ ██║"
		"██║███████╗███████║"
		"█████╗  ██║     ██║ \n", 2);
}

static void	print_spielberg_2(void)
{
	ft_putstr_fd("██║╚██╔╝██║██║██║╚██╗██║"
		"██║╚════██║██╔══██║"
		"██╔══╝  ██║     ██║ \n", 2);
	ft_putstr_fd("██║ ╚═╝ ██║██║██║ ╚████║"
		"██║███████║██║  ██║"
		"███████╗███████╗███████╗ \n", 2);
	ft_putstr_fd("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝"
		"╚═╝╚══════╝╚═╝  ╚═╝"
		"╚══════╝╚══════╝╚══════╝ \n" RESET, 2);
	ft_putstr_fd("~ La minishell que emocionó a Steven Spielberg\n", 2);
}

void	print_spielberg(void)
{
	print_spielberg_1();
	print_spielberg_2();
}

/* Run a script line in non-interactive mode */
int	run_script_mode(char *line, char ***mini_env, int *exit_status)
{
	t_arena	*arena;
	char	**tokens;
	t_cmd	*cmd_list;
	int		leftover[2];

	arena = arena_init(1024);
	tokens = tokenizer(arena, line);
	if (!is_valid_syntax(tokens, exit_status))
		return (arena_destroy(arena), *exit_status);
	cmd_list = parser(arena, tokens, mini_env, exit_status);
	if (cmd_list)
	{
		parse_heredoc(cmd_list, leftover);
		expander(cmd_list);
		*exit_status = execute_chain(cmd_list);
	}
	arena_destroy(arena);
	free_env(*mini_env);
	return (*exit_status);
}

/* Run the minishell */
int	main(int argc, char *argv[], char *envp[])
{
	char	**mini_env;
	int		exit_status;
	int		leftover[2];

	mini_env = copy_env(envp);
	if (!mini_env)
		return (1);
	exit_status = 0;
	if (argc == 2)
		return (run_script_mode(argv[1], &mini_env, &exit_status));
	print_spielberg();
	set_signals_interactive();
	pipe(leftover);
	run_interactive_loop(&mini_env, &exit_status, leftover);
	free_env(mini_env);
	rl_clear_history();
	return (exit_status);
}
