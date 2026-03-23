/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_flush.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 18:12:57 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/11 18:12:58 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	gnl_flush(char **stock, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (stock[i])
		{
			free(stock[i]);
			stock[i] = NULL;
		}
		i++;
	}
}
