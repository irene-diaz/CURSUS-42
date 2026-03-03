#include "../includes/libft_arena.h"

char	*ft_strjoin_arena(t_arena *arena, char const *s1, char const *s2)
{
	size_t	buffer;
	size_t	i;
	char	*ptr;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	buffer = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = arena_alloc(arena, buffer);
	if (ptr == NULL)
		return (NULL);
	while (*s1)
		*(ptr + i++) = *s1++;
	while (*s2)
		*(ptr + i++) = *s2++;
	*(ptr + i) = '\0';
	return (ptr);
}
