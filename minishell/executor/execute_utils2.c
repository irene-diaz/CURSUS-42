/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:52:33 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/16 16:55:03 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*function to get the next command group*/
t_cmd	*next_group(t_cmd *cmd, t_operator *out_op)
{
	while (cmd && cmd->operator == PIPE)
		cmd = cmd->next;
	if (cmd)
	{
		*out_op = cmd->operator;
		return (cmd->next);
	}
	*out_op = NONE;
	return (NULL);
}
