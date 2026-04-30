/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_movements_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:07:52 by dasanche          #+#    #+#             */
/*   Updated: 2025/06/13 13:04:39 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Función swap general para llamar en sa, sb y ss:

static void	swap_nodes(t_stack *stack)
{
	t_node	*first;
	t_node	*second;
	int		tmp_val;
	int		tmp_idx;

	if (!stack || stack->size < 2)
		return ;
	first = stack->top;
	second = first->next;
	tmp_val = first->value;
	tmp_idx = first->index;
	first->value = second->value;
	first->index = second->index;
	second->value = tmp_val;
	second->index = tmp_idx;
}

/* Función swap a que intercambia los dos primeros
elementos del stack a y no hace nada si hay uno o
menos elementos: */

void	sa(t_stack *a)
{
	swap_nodes(a);
	write(1, "sa\n", 3);
}

/* Función swap b que intercambia los dos primeros
elementos del stack b y no hace nada si hay uno o
menos elementos: */

void	sb(t_stack *b)
{
	swap_nodes(b);
	write(1, "sb\n", 3);
}

/* Función swap a y b a la vez, intercambia los
dos primeros elementos del stack a y b no hace nada
si hay uno o menos elementos: */

void	ss(t_stack *a, t_stack *b)
{
	swap_nodes(a);
	swap_nodes(b);
	write(1, "ss\n", 3);
}

/* Función que realiza movimiento push a, toma el
primer elemento del stack b y lo pone el primero en el
stack a, no hace nada si b está vacío: */

void	pa(t_stack *a, t_stack *b)
{
	t_node	*tmp;

	if (!b || b->size == 0)
		return ;
	tmp = b->top;
	b->top = tmp->next;
	b->size--;
	tmp->next = a->top;
	a->top = tmp;
	a->size++;
	write(1, "pa\n", 3);
}
