/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_movements_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:15:32 by dasanche          #+#    #+#             */
/*   Updated: 2025/06/13 13:05:45 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Función reverse rotate general para llamar en rra, rrb y rrr:

static void	reverse_rotate_nodes(t_stack *stack)
{
	t_node	*prev;
	t_node	*last;

	if (!stack || stack->size < 2 || !stack->top)
		return ;
	prev = NULL;
	last = stack->top;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	if (prev)
		prev->next = NULL;
	last->next = stack->top;
	stack->top = last;
}

/* Función rotate a que desplaza hacia abajo todos
los elementos del stack a una posición, de forma
que el último elemento se convierte en el primero: */

void	rra(t_stack *a)
{
	reverse_rotate_nodes(a);
	write(1, "rra\n", 4);
}

/* Función reverse rotate b que desplaza hacia abajo todos
los elementos del stack b una posición, de forma
que el último elemento se convierte en el primero: */

void	rrb(t_stack *b)
{
	reverse_rotate_nodes(b);
	write(1, "rrb\n", 4);
}

/* Función reverse rotate a y b a la vez, desplaza
hacia abajo todos los elementos de los stacks una posición
conviertiendo el último elemento en primero: */

void	rrr(t_stack *a, t_stack *b)
{
	reverse_rotate_nodes(a);
	reverse_rotate_nodes(b);
	write(1, "rrr\n", 4);
}
