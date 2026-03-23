/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 14:14:31 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/12 13:05:22 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Check if a string has a wildcard character */
int	wildcard_match(const char *pattern, const char *name)
{
	while (*pattern == *name || *pattern == '*')
	{
		if (*pattern == '\0')
			return (1);
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			while (*name && !wildcard_match(pattern, name))
				name++;
			if (*name == '\0' && *pattern != '\0')
				return (0);
		}
		else
		{
			pattern++;
			name++;
		}
	}
	return (0);
}

/* Count the number of words in a command */
int	count_words(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

/* Insert a word into a command */
void	insert_word(t_cmd *cmd, char *new_word, int index)
{
	int		size;
	char	**new_list;
	int		i;

	size = count_words(cmd->cmd);
	new_list = arena_alloc(cmd->arena, sizeof(char *) * (size + 2));
	new_list[size + 1] = NULL;
	i = 0;
	while (i < index)
	{
		new_list[i] = cmd->cmd[i];
		i++;
	}
	new_list[index] = ft_strdup_arena(cmd->arena, new_word);
	while (cmd->cmd[index])
	{
		new_list[index + 1] = cmd->cmd[index];
		index++;
	}
	cmd->cmd = new_list;
}

/* Expand wildcards in a command */
void	expand_wildcards(t_cmd *cmd, int word_index)
{
	DIR				*dir;
	struct dirent	*entry;
	int				match_found;

	if (!has_wildcard(cmd->cmd[word_index]))
		return ;
	dir = opendir(".");
	if (!dir)
		return ;
	match_found = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (wildcard_match(cmd->cmd[word_index], entry->d_name)
			&& entry->d_name[0] != '.')
		{
			insert_word(cmd, entry->d_name, word_index + 1);
			match_found = 1;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (match_found)
		remove_word(&cmd->cmd[word_index]);
}
