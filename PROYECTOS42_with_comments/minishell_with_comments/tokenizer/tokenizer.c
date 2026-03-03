#include "../includes/minishell.h"

int	is_token(const char *token)
{
	if (*token == '|' && *(token + 1) == '|')
		return (2);
	else if (*token == '|')
		return (1);
	else if (*token == '&' && *(token + 1) == '&')
		return (2);
	else if (*token == '<' && *(token + 1) == '<')
		return (2);
	else if (*token == '<')
		return (1);
	else if (*token == '>' && *(token + 1) == '>')
		return (2);
	else if (*token == '>')
		return (1);
	else if (*token == '(')
		return (1);
	else if (*token == ')')
		return (1);
	return (0);
}

static int	token_len(const char *str)
{
	int		len;
	int		temp_len;
	char	quote;

	len = 0;
	temp_len = is_token(str);
	if (temp_len > 0)
		return (temp_len);
	while (str[len])
	{
		if (str[len] == '\'' || str[len] == '"')
		{
			quote = str[len];
			len++;
			while (str[len] && str[len] != quote)
				len++;
			if (str[len] == quote)
				len++;
		}
		else
		{
			if (str[len] == ' ' || str[len] == '\t')
				break ;
			temp_len = is_token(&str[len]);
			if (temp_len > 0)
				break ;
			len++;
		}
	}
	return (len);
}

static int	count_words(const char *str)
{
	int	word_count;
	int	movements;

	word_count = 0;
	while (*str)
	{
		while (*str == ' ' || *str == '\t')
			str++;
		if (*str == '\0')
			break ;
		movements = token_len(str);
		word_count++;
		str += movements;
	}
	return (word_count);
}

static char	*get_token_string(const char *str)
{
	if (*str == '|' && *(str + 1) == '|')
		return (TOKEN_OR);
	else if (*str == '|')
		return (TOKEN_PIPE);
	else if (*str == '&' && *(str + 1) == '&')
		return (TOKEN_AND);
	else if (*str == '<' && *(str + 1) == '<')
		return (TOKEN_HEREDOC);
	else if (*str == '<')
		return (TOKEN_REDIR_IN);
	else if (*str == '>' && *(str + 1) == '>')
		return (TOKEN_APPEND);
	else if (*str == '>')
		return (TOKEN_REDIR_OUT);
	else if (*str == '(')
		return (TOKEN_OPEN_PAREN);
	else if (*str == ')')
		return (TOKEN_CLOSE_PAREN);
	return (NULL);
}

char	**tokenizer(t_arena *arena, const char *str)
{
	int		words;
	char	**tokens;
	int		i;
	int		wordlen;

	words = count_words(str);
	tokens = arena_alloc(arena, sizeof(char *) * (words + 1));
	i = 0;
	while (i < words)
	{
		while (*str == ' ' || *str == '\t')
			str++;
		wordlen = token_len(str);
		if (is_token(str))
			tokens[i] = get_token_string(str);
		else
		{
			tokens[i] = arena_alloc(arena, wordlen + 1);
			ft_strncpy(tokens[i], str, wordlen);
			tokens[i][wordlen] = '\0';
		}
		i++;
		str += wordlen;
	}
	tokens[i] = NULL;
	return (tokens);
}

/*
char	**tokenizer(t_arena *arena, const char *str)
{
	int		words;
	char	**tokens;
	int		i;
	int		wordlen;

	words = count_words(str);
	tokens = arena_alloc(arena, sizeof(char *) * (words + 1));
	i = 0;
	while (i < words)
	{
		while (*str == ' ' || *str == '\t')
			str++;
		wordlen = token_len(str);
		tokens[i] = arena_alloc(arena, wordlen + 1);
		ft_strncpy(tokens[i], str, wordlen);
		tokens[i][wordlen] = '\0';
		i++;
		str += wordlen;
	}
	tokens[i] = NULL;
	return (tokens);
}
*/
