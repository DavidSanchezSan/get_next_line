/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:27:48 by dasanche          #+#    #+#             */
/*   Updated: 2025/06/13 12:55:12 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Función que controla si el stack está ordenado:

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || !stack->top)
		return (1);
	current = stack->top;
	while (current && current->next)
	{
		if (current->index > current->next->index)
			return (0);
		current = current->next;
	}
	return (1);
}

// Función que devuelve el nodo con el número más pequeño:

t_node	*find_min_node(t_stack *stack)
{
	t_node	*min;
	t_node	*current;

	if (!stack || !stack->top)
		return (NULL);
	min = stack->top;
	current = stack->top;
	while (current)
	{
		if (current->index < min->index)
			min = current;
		current = current->next;
	}
	return (min);
}

// Función para mover nodo a la primera posición:

void	move_node_to_top(t_stack *s, t_node *t)
{
	int		pos;
	t_node	*current;

	pos = 0;
	current = s->top;
	while (current && current != t)
	{
		pos++;
		current = current->next;
	}
	if (pos <= s->size / 2)
	{
		while (s->top != t)
			ra(s);
	}
	else
	{
		while (s->top != t)
			rra(s);
	}
}
