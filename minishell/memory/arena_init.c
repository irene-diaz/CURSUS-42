/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:57:22 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 11:33:10 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

/* Create a new arena node */
static t_arena_node	*create_new_arena_node(size_t size)
{
	t_arena_node	*node;

	node = malloc(sizeof(t_arena_node));
	if (!node)
		return (NULL);
	node->data = malloc(size);
	if (!node->data)
	{
		free(node);
		return (NULL);
	}
	node->size = size;
	node->used = 0;
	node->next = NULL;
	return (node);
}

/* Initialize the memory arena */
t_arena	*arena_init(size_t chunk_size)
{
	t_arena	*arena;

	arena = malloc(sizeof(t_arena));
	if (!arena)
		return (NULL);
	arena->head = NULL;
	arena->chunk_size = chunk_size;
	return (arena);
}

/* Find an available node in the arena */
static t_arena_node	*find_available_node(t_arena *arena, size_t size)
{
	t_arena_node	*current;

	current = arena->head;
	while (current && current->used + size > current->size)
		current = current->next;
	return (current);
}

/* Allocate memory from the arena */
void	*arena_alloc(t_arena *arena, size_t size)
{
	t_arena_node	*current;
	size_t			alloc_size;
	void			*ptr;

	if (!arena || size == 0)
		return (NULL);
	current = find_available_node(arena, size);
	if (!current)
	{
		if (size > arena->chunk_size)
			alloc_size = size;
		else
			alloc_size = arena->chunk_size;
		current = create_new_arena_node(alloc_size);
		if (!current)
			return (NULL);
		current->next = arena->head;
		arena->head = current;
	}
	ptr = (char *)current->data + current->used;
	current->used += size;
	return (ptr);
}
