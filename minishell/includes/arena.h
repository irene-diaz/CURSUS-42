/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:59:18 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/11 17:59:19 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <stddef.h>
# include <stdlib.h>

typedef struct s_arena_node
{
	void				*data;
	size_t				size;
	size_t				used;
	struct s_arena_node	*next;
}						t_arena_node;

typedef struct s_arena
{
	t_arena_node		*head;
	size_t				chunk_size;
}						t_arena;

t_arena					*arena_init(size_t chunk_size);
void					*arena_alloc(t_arena *arena, size_t size);
void					arena_free_all(t_arena *arena);
void					arena_destroy(t_arena *arena);

#endif
