#include "../includes/libft_arena.h"

t_list	*ft_lstnew_arena(t_arena *arena, void *content)
{
	t_list	*node;

	node = arena_alloc(arena, sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
