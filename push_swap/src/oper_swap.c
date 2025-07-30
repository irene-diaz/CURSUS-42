/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:19:40 by oem               #+#    #+#             */
/*   Updated: 2025/07/28 14:30:48 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Intercambia los dos primeros elementos del stack a.
void	sa(t_node **a)
{
	swap(a);
	write(1, "sa\n", 3);
}

// Intercambia los dos primeros elementos del stack b.
void	sb(t_node **b)
{
	swap(b);
	write(1, "sb\n", 3);
}

// Hace sa y sb a la vez
void	ss(t_node **a, t_node **b)
{
	swap(a);
	swap(b);
	write(1, "ss\n", 3);
}
