/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:14:27 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 10:52:21 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Count the number of tokens in the input string */
static int	count_tokens(const char *str)
{
	int	word_count;
	int	movements;

	word_count = 0;
	while (*str)
	{
		while (*str == ' ' || *str == '\t' || *str == '\n')
			str++;
		if (*str == '\0')
			break ;
		movements = token_len(str);
		word_count++;
		str += movements;
	}
	return (word_count);
}

/* Fill the token array with the current word */
static void	fill_token(t_arena *arena, char **tokens, const char *str,
		int wordlen)
{
	if (is_token(str))
		tokens[0] = get_token_string(str);
	else
	{
		tokens[0] = arena_alloc(arena, wordlen + 1);
		ft_strncpy(tokens[0], str, wordlen);
		tokens[0][wordlen] = '\0';
	}
}

/* Tokenize(split) the input string */
char	**tokenizer(t_arena *arena, const char *str)
{
	int		words;
	char	**tokens;
	int		i;
	int		wordlen;

	words = count_tokens(str);
	tokens = arena_alloc(arena, sizeof(char *) * (words + 1));
	i = 0;
	while (i < words)
	{
		while (*str == ' ' || *str == '\t' || *str == '\n')
			str++;
		wordlen = token_len(str);
		fill_token(arena, &tokens[i], str, wordlen);
		i++;
		str += wordlen;
	}
	tokens[i] = NULL;
	return (tokens);
}
