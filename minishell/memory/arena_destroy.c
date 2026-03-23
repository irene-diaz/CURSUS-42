/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:56:49 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 11:32:45 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

/* Free all memory allocated in the arena */
void	arena_free_all(t_arena *arena)
{
	t_arena_node	*current;
	t_arena_node	*next;

	if (!arena)
		return ;
	current = arena->head;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	arena->head = NULL;
}

/* Destroy the memory arena,
	free all allocated nodes and the arena structure itself */
void	arena_destroy(t_arena *arena)
{
	if (!arena)
		return ;
	arena_free_all(arena);
	free(arena);
}
