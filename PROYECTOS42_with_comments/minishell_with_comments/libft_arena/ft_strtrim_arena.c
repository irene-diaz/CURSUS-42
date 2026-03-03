#include "../includes/libft_arena.h"

static int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static size_t	trim_start(const char *s, const char *set)
{
	size_t	i;

	i = 0;
	while (s[i] && is_in_set(s[i], set))
		i++;
	return (i);
}

static size_t	trim_end(const char *s, const char *set)
{
	size_t	len;

	len = ft_strlen(s);
	if (len == 0)
		return (0);
	len--;
	while (len > 0 && is_in_set(s[len], set))
		len--;
	return (len + 1);
}

char	*ft_strtrim_arena(t_arena *arena, char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	start = trim_start(s1, set);
	end = trim_end(s1, set);
	if (start >= end)
		return (ft_strdup_arena(arena, ""));
	res = arena_alloc(arena, end - start + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1 + start, end - start);
	res[end - start] = '\0';
	return (res);
}
