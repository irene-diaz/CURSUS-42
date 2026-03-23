/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:25:01 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 10:52:54 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Check if the given string is a token */
int	is_token(const char *token)
{
	if (*token == '|' && *(token + 1) == '|')
		return (2);
	if (*token == '|')
		return (1);
	if (*token == '&' && *(token + 1) == '&')
		return (2);
	if (*token == '<' && *(token + 1) == '<')
		return (2);
	if (*token == '<')
		return (1);
	if (*token == '>' && *(token + 1) == '>')
		return (2);
	if (*token == '>')
		return (1);
	if (*token == '(')
		return (1);
	if (*token == ')')
		return (1);
	return (0);
}

/* Get the length of a quoted(specific length) token */
int	token_len_quote(const char *str, int len)
{
	char	quote;

	quote = str[len];
	len++;
	while (str[len] && str[len] != quote)
		len++;
	if (str[len] == quote)
		len++;
	return (len);
}

/* Get the length of a token */
int	token_len(const char *str)
{
	int	len;
	int	temp_len;

	len = 0;
	temp_len = is_token(str);
	if (temp_len > 0)
		return (temp_len);
	while (str[len])
	{
		if (str[len] == '\'' || str[len] == '"')
			len = token_len_quote(str, len);
		else
		{
			if (str[len] == ' ' || str[len] == '\t' || str[len] == '\n')
				break ;
			temp_len = is_token(&str[len]);
			if (temp_len > 0)
				break ;
			len++;
		}
	}
	return (len);
}

/* Get the string representation of a token */
char	*get_token_string(const char *str)
{
	if (*str == '|' && *(str + 1) == '|')
		return (TOKEN_OR);
	if (*str == '|')
		return (TOKEN_PIPE);
	if (*str == '&' && *(str + 1) == '&')
		return (TOKEN_AND);
	if (*str == '<' && *(str + 1) == '<')
		return (TOKEN_HEREDOC);
	if (*str == '<')
		return (TOKEN_REDIR_IN);
	if (*str == '>' && *(str + 1) == '>')
		return (TOKEN_APPEND);
	if (*str == '>')
		return (TOKEN_REDIR_OUT);
	if (*str == '(')
		return (TOKEN_OPEN_PAREN);
	if (*str == ')')
		return (TOKEN_CLOSE_PAREN);
	return (NULL);
}
