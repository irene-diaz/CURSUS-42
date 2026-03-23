/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:34:51 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/11 19:40:29 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Update quote flags based on the input line */
void	update_quote_flags(const char *line, int *double_q, int *single_q)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '"' && *single_q == 0)
			*double_q = !(*double_q);
		else if (line[i] == '\'' && *double_q == 0)
			*single_q = !(*single_q);
	}
}

/* Append a line to the full line */
void	append_line(t_arena *arena, char **full_line, char *tmp)
{
	char	*tmp2;
	int		new_len;

	if (!*full_line)
	{
		*full_line = arena_alloc(arena, ft_strlen(tmp) + 1);
		ft_strcpy(*full_line, tmp);
		return ;
	}
	new_len = ft_strlen(*full_line) + 1 + ft_strlen(tmp) + 1;
	tmp2 = arena_alloc(arena, new_len);
	ft_strcpy(tmp2, *full_line);
	ft_strlcat(tmp2, "\n", new_len);
	ft_strlcat(tmp2, tmp, new_len);
	*full_line = tmp2;
}
