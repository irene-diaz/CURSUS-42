/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:33:11 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/01/28 13:57:41 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_tokens(char **tokens)
{
	// Imprimir cada token en una línea (útil para depuración del tokenizer)
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
}

/*void	print_cmd_tree(t_cmd *cmd, int level)
{
	int	i;
	int	j;

	while (cmd)
	{
		i = -1;
		while (++i < level)
			printf("  ");
		printf("NODE:\n");
		i = -1;
		while (++i < level)
			printf("  ");
		printf("  cmd->cmd = ");
		if (cmd->cmd)
		{
			printf("[");
			j = 0;
			while (cmd->cmd[j])
			{
				printf("\"%s\"", cmd->cmd[j]);
				if (cmd->cmd[j + 1])
					printf(", ");
				j++;
			}
			printf("]\n");
		}
		else
			printf("NULL\n");
		i = -1;
		while (++i < level)
			printf("  ");
		printf("  cmd->operator = ");
		if (cmd->operator== NONE)
			printf("NONE\n");
		else if (cmd->operator== PIPE)
			printf("PIPE\n");
		else if (cmd->operator== AND)
			printf("AND\n");
		else if (cmd->operator== OR)
			printf("OR\n");
		else if (cmd->operator== OPEN_SUBSHELL)
			printf("OPEN_SUBSHELL\n");
		else if (cmd->operator== CLOSE_SUBSHELL)
			printf("CLOSE_SUBSHELL\n");
		i = -1;
		while (++i < level)
			printf("  ");
		printf("  cmd->subshell = ");
		if (cmd->subshell)
		{
			printf("{\n");
			print_cmd_tree(cmd->subshell, level + 2);
			i = -1;
			while (++i < level)
				printf("  ");
			printf("  }\n");
		}
		else
			printf("NULL\n");
		i = -1;
		while (++i < level)
			printf("  ");
		printf("  cmd->next = ");
		if (cmd->next)
			printf("→\n\n");
		else
			printf("NULL\n");
		cmd = cmd->next;
	}
}*/
/*int	parse_command(t_arena *arena, char *line, char *envp[])
{
	if (!ft_strncmp(line, "quit", 4))
		return (-1);
	else if (!ft_strncmp(line, "cd", 2))
		exec_cd(arena, line);
	return (1);
}*/
void	print_spielberg(void)
{
	// Mostrar un banner al iniciar el shell interactivo
	ft_putstr_fd(YELLOW "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗\n",
		2);
	ft_putstr_fd("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║ \n",
		2);
	ft_putstr_fd("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║ \n",
		2);
	ft_putstr_fd("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║ \n",
		2);
	ft_putstr_fd("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗ \n",
		2);
	ft_putstr_fd("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ \n" RESET,
		2);
	ft_putstr_fd("~ La minishell que emocionó a Steven Spielberg\n", 2);
}

// !line->Ctrl+D
int	main(int argc, char *argv[], char *envp[])
{
	t_arena	*arena;
	char	*line;
	char	**tokens;
	int		exit_status;
	t_cmd	*cmd_list;

	/*
		Variables principales:
		- arena: allocator local por comando para evitar fugas y facilitar liberar
		memoria en bloque al terminar cada iteración del bucle.
		- line: línea leída del usuario (readline a través de reader()).
		- tokens: array de strings devuelto por el tokenizer.
		- exit_status: código de salida que devolvemos al sistema al terminar.
		- cmd_list: estructura intermedia (árbol/lista) devuelta por el parser.
	*/
	exit_status = 0;
	// Modo "batch" si se pasa un argumento: ejecutar la línea y salir
	if (argc == 2)
	{
		arena = arena_init(1024);
		line = argv[1];
		// Tokenizar, validar sintaxis, parsear y ejecutar una sola línea
		tokens = tokenizer(arena, line);
		if (!is_valid_syntax(tokens, &exit_status))
		{
			arena_destroy(arena);
			return (exit_status);
		}
		cmd_list = parser(arena, tokens, &envp, &exit_status);
		if (cmd_list)
			// print_cmd_tree(cmd_list, 0);
			// Ejecutar la lista de comandos (puede contener pipelines)
			exit_status = execute_cmd_list(cmd_list);
		arena_destroy(arena);
		return (exit_status);
	}
	// Modo interactivo: mostrar banner y preparar manejo de señales
	print_spielberg();
	set_signals_interactive();
	while (1)
	{
		// Para cada iteración usamos un arena nuevo que se destruirá al final
		arena = arena_init(1024);
		// reader() encapsula readline y posibles expansiones; devuelve NULL en EOF (Ctrl-D)
		line = reader(arena, envp);
		if (!line)
		{
			arena_destroy(arena);
			break ;
		}
		// Tokenizar la línea y validar sintaxis antes de parsear
		tokens = tokenizer(arena, line);
		if (!is_valid_syntax(tokens, &exit_status))
		{
			arena_destroy(arena);
			continue ;
		}
		// Parsear tokens a una estructura de comandos ejecutable
		cmd_list = parser(arena, tokens, &envp, &exit_status);
		if (!cmd_list)
		{
			arena_destroy(arena);
			continue ;
		}
		// print_cmd_tree(cmd_list, 0);
		/*if (parse_command(arena, line, envp) == -1)
		{
			ft_putstr_fd("Pasta la vista!\n", 1);
			arena_destroy(arena);
			break ;
		}*/
		/*
			Ejecutar builtins que deben modificar el estado del shell (padre):
			Por ejemplo `cd`, `export`, `unset`, `exit`. Estos deben ejecutarse
			en el proceso padre porque cambian el entorno o el directorio actual.
			Si la lista contiene sólo un comando y es uno de esos,
				llamamos a exec_builtin
			en el padre y evitamos fork/exec.
		*/
		if (cmd_list->cmd && !cmd_list->next && (ft_strncmp(cmd_list->cmd[0],
					"cd", 3) == 0 || ft_strncmp(cmd_list->cmd[0], "export",
					7) == 0 || ft_strncmp(cmd_list->cmd[0], "unset", 6) == 0
				|| ft_strncmp(cmd_list->cmd[0], "exit", 5) == 0))
		{
			exec_builtin(cmd_list);
			arena_destroy(arena);
			continue ;
		}
		// Ejecutar pipelines o comandos normales (en hijos)
		exit_status = execute_cmd_list(cmd_list);
		arena_destroy(arena);
	}
	// Al salir del bucle interactivo limpiar el historial de readline
	rl_clear_history();
	return (exit_status);
}
