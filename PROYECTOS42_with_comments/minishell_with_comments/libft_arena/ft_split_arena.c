#include "../includes/libft_arena.h"

static int	is_sep(char c, char sep)
{
	return (c == sep);
}

static int	word_counter(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_sep(s[i], c))
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && !is_sep(s[i], c))
				i++;
		}
	}
	return (count);
}

static char	*dup_word(const char *s, char c, int *i, struct s_arena *arena)
{
	int		start;
	int		len;
	char	*word;

	start = *i;
	len = 0;
	while (s[*i] && !is_sep(s[*i], c))
	{
		(*i)++;
		len++;
	}
	word = arena_alloc(arena, len + 1);
	if (!word)
		return (NULL);
	len = 0;
	while (start < *i)
		word[len++] = s[start++];
	word[len] = '\0';
	return (word);
}

char	**ft_split_arena(char const *s, char c, struct s_arena *arena)
{
	char	**arr;
	int		i;
	int		idx;

	i = 0;
	idx = 0;
	if (!s)
		return (NULL);
	arr = arena_alloc(arena, sizeof(char *) * (word_counter(s, c) + 2));
	if (!arr)
		return (NULL);
	//        arr[0] = NULL;
	while (s[i])
	{
		while (s[i] && is_sep(s[i], c))
			i++;
		if (s[i])
		{
			arr[idx] = dup_word(s, c, &i, arena);
			if (!arr[idx++])
				return (NULL);
		}
	}
	arr[idx] = NULL;
	return (arr);
}
