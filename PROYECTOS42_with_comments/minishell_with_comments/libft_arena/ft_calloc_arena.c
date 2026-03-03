#include "../includes/libft_arena.h"

void	*ft_calloc_arena(t_arena *arena, size_t nmemb, size_t size)
{
	size_t	total;
	void	*ptr;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	total = nmemb * size;
	ptr = arena_alloc(arena, total);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, '\0', total);
	return (ptr);
}
