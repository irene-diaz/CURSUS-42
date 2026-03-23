/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:52:18 by abrecio-          #+#    #+#             */
/*   Updated: 2025/04/24 16:52:20 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static char	*dup_word(const char *s, char c, int *i)
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
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	len = 0;
	while (start < *i)
		word[len++] = s[start++];
	word[len] = '\0';
	return (word);
}

static char	**free_iter(char **s, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		free(s[j]);
		j++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		idx;

	i = 0;
	idx = 0;
	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (!arr)
		return (NULL);
	while (s[i])
	{
		while (s[i] && is_sep(s[i], c))
			i++;
		if (s[i])
		{
			arr[idx] = dup_word(s, c, &i);
			if (!arr[idx++])
				return (free_iter(arr, idx));
		}
	}
	arr[idx] = NULL;
	return (arr);
}
