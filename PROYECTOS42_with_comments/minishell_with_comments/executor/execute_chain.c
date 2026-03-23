/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_chain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:13:17 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/19 11:55:01 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Obtiene el siguiente grupo de comandos */
static t_cmd	*next_group(t_cmd *cmd, t_operator *out_op)
{
	// Avanza a través de la lista de comandos hasta encontrar un operador que no sea PIPE
	while (cmd && cmd->operator== PIPE)
		cmd = cmd->next;
	/** Si encontramos un comando válido,
		devolvemos su operador y el siguiente comando */
	if (cmd)
	{
		*out_op = cmd->operator;
		return (cmd->next);
	}
	/* Si no hay más comandos,
		establecemos el operador de salida a NONE y devolvemos NULL */
	*out_op = NONE;
	return (NULL);
}

/* Determina si se debe omitir un grupo de comandos */
static int	should_skip(t_operator incoming_op, int exitcode)
{
	/* Si el operador entrante es AND y el código de salida no es 0,
		se debe omitir el siguiente grupo */
	if (incoming_op == AND && exitcode != 0)
		return (1);
	/* Si el operador entrante es OR y el código de salida es 0,
		se debe omitir el siguiente grupo */
	if (incoming_op == OR && exitcode == 0)
		return (1);
	return (0);
}

/* Negar el código de salida para el siguiente grupo */
static void	negate_exitcode(int *exitcode)
{
	if (*exitcode == 0)
		*exitcode = 1;
	else
		*exitcode = 0;
}

/* Ejecutar grupos de comandos */
static int	execute_groups(t_cmd *cmd)
{
	t_cmd		*group;
	t_operator	incoming_op;
	t_operator	outgoing_op;

	// Puntero al grupo actual de comandos que se está ejecutando
	// Operador que determina la relación con el grupo anterior
	// Operador que determina la relación con el siguiente grupo
	int exitcode; // Código de salida del grupo actual
	group = cmd;
	incoming_op = NONE;
	exitcode = 0;
	// Itera a través de los grupos de comandos hasta que no haya más
	while (group)
	{
		// Verifica si se debe omitir el grupo actual según el operador entrante y el código de salida del grupo anterior
		if (should_skip(incoming_op, exitcode))
		{
			/** Si se debe omitir el grupo,
				se avanza al siguiente grupo sin ejecutarlo */
			group = next_group(group, &outgoing_op);
			// El operador entrante para el siguiente grupo será el operador de salida del grupo actual
			incoming_op = outgoing_op;
			continue ;
		}
		/** Si no se debe omitir el grupo,
			se ejecuta y se obtiene su código de salida */
		exitcode = execute_cmd_list(group);
		group = next_group(group, &outgoing_op);
		incoming_op = outgoing_op;
	}
	return (exitcode);
}

/* Ejecuta una cadena de comandos */
int	execute_chain(t_cmd *cmd)
{
	int	exitcode;
	int	negate;

	if (!cmd)
		return (-1);
	exitcode = 0;
	negate = 0;
	// Negar el código de salida si el primer comando es "!"
	if (cmd->cmd && cmd->cmd[0] && ft_strncmp(cmd->cmd[0], "!", 2) == 0)
	{
		negate = 1;
		cmd->cmd = &cmd->cmd[1];
	}
	// Eliminar el operador "!" de la cadena de comandos
	exitcode = execute_groups(cmd);
	// Negar el código de salida si se indicó que se debía negar
	if (negate)
		negate_exitcode(&exitcode);
	/* Si se proporcionó un puntero para el código de salida,
		se actualiza con el resultado final */
	if (cmd->exitcode)
		*cmd->exitcode = exitcode;
	return (exitcode);
}
