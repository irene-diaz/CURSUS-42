/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:18:19 by oem               #+#    #+#             */
/*   Updated: 2025/07/30 18:26:35 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

// es como un atoi pero funciona con numeros long tambn
static long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

// validacion para ver si un numero se repite o no
static int	has_duplicates(t_node *stack, int value)
{
	while (stack)
	{
		if (stack->value == value)
			return (1);
		stack = stack->next;
	}
	return (0);
}

// Crea y devuelve un nuevo nodo (t_node) con el valor dado.
static t_node	*new_node(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = -1;
	node->next = NULL;
	return (node);
}

// Añade un nodo new al final de la lista enlazada stack
static void	add_back(t_node **stack, t_node *new)
{
	t_node	*tmp;

	if (!*stack)
		*stack = new;
	else
	{
		tmp = *stack;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/* Recoge todos los argumentos,
los convierte a enteros seguros y los mete en la pila a
como una lista enlazada.*/

/*Soporta argumentos con o sin comillas.

Valida que cada número sea único, válido y dentro de rango.

Construye la pila a como lista enlazada dinámica (t_node).*/
t_node	*parse_args(int argc, char **argv)
{
	t_node	*stack;
	char	**args;
	int		i;
	long	num;

	stack = NULL;
	i = 0;
	if (argc == 2)
		args = ft_split(argv[1], ' ');
	else
		args = &argv[1];
	while (args[i])
	{
		num = ft_atol(args[i]);
		if (num < -2147483648 || num > 2147483647 || !*args[i]
			|| !is_valid_number(args[i]))
			error_and_exit();
		if (has_duplicates(stack, (int)num))
			error_and_exit();
		add_back(&stack, new_node((int)num));
		i++;
	}
	if (argc == 2)
		free_split(args);
	return (stack);
}
