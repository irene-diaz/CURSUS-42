#ifndef LIBFT_ARENA_H
# define LIBFT_ARENA_H

# include <stddef.h>
# include "arena.h"
# include "libft.h"

char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t n);
char	*ft_strjoin_arena(t_arena *arena, char const *s1, char const *s2);
char	**ft_split_arena(char const *s, char c, t_arena *arena);
char	*ft_strdup_arena(t_arena *arena, const char *s);
char	*ft_substr_arena(t_arena *arena, char const *s, unsigned int start,
			size_t len);
char	*ft_strtrim_arena(t_arena *arena, char const *s1, char const *set);
char	*ft_itoa_arena(t_arena *arena, int n);
char	*ft_strmapi_arena(t_arena *arena, char const *s,
			char (*f)(unsigned int, char));
void	*ft_calloc_arena(t_arena *arena, size_t nmemb, size_t size);
t_list	*ft_lstnew_arena(t_arena *arena, void *content);

#endif
