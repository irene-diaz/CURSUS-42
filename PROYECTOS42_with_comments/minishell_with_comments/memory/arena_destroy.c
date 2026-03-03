#include "arena.h"


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

void	arena_destroy(t_arena *arena)
{
	if (!arena)
		return ;
	arena_free_all(arena);
	free(arena);
}
