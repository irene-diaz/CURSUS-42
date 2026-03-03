#include "../includes/libft_arena.h"

char	*ft_strdup_arena(t_arena *arena, const char *s)
{
	size_t	len;
	char	*dup;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = arena_alloc(arena, len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len + 1);
	return (dup);
}
