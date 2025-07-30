/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:18:47 by oem               #+#    #+#             */
/*   Updated: 2025/07/30 18:27:20 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
}					t_node;

// main
void				push_swap(t_node **a);

// parsing
t_node				*parse_args(int argc, char **argv);

// operations
void				sa(t_node **a);
void				sb(t_node **b);
void				ss(t_node **a, t_node **b);
void				pa(t_node **a, t_node **b);
void				pb(t_node **a, t_node **b);
void				ra(t_node **a);
void				rb(t_node **b);
void				rr(t_node **a, t_node **b);
void				rra(t_node **a);
void				rrb(t_node **b);
void				rrr(t_node **a, t_node **b);
void				swap(t_node **stack);
void				push(t_node **src, t_node **dest);
void				rotate(t_node **stack);
void				reverse_rotate(t_node **stack);
// sorting
void				sort_small(t_node **a, t_node **b);
void				ksort(t_node **a, t_node **b);

// utils
int					is_sorted(t_node *a);
int					stack_size(t_node *a);
void				free_stack(t_node **stack);
void				error_and_exit(void);
void				free_split(char **split);
void				assign_indexes(t_node *stack);
int					is_valid_number(const char *str);

// SPLIT
char				**ft_split(char const *s, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);

#endif