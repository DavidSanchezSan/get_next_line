/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_movements_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:45:03 by dasanche          #+#    #+#             */
/*   Updated: 2025/06/13 13:05:12 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Función que realiza movimiento push b, toma el
primer elemento del stack a y lo pone el primero en el
stack b, no hace nada si a está vacío: */

void	pb(t_stack *a, t_stack *b)
{
	t_node	*tmp;

	if (!a || a->size == 0)
		return ;
	tmp = a->top;
	a->top = tmp->next;
	a->size--;
	tmp->next = b->top;
	b->top = tmp;
	b->size++;
	write(1, "pb\n", 3);
}

// Función rotate general para llamar en ra, rb y rr:

static void	rotate_nodes(t_stack *stack)
{
	t_node	*first;
	t_node	*last;

	if (!stack || stack->size < 2 || !stack->top)
		return ;
	first = stack->top;
	stack->top = first->next;
	last = stack->top;
	while (last->next)
		last = last->next;
	last->next = first;
	first->next = NULL;
}

/* Función rotate a que desplaza hacia arriba todos
los elementos del stack a una posición, de forma
que el primer elemento se convierte en el último: */

void	ra(t_stack *a)
{
	rotate_nodes(a);
	write(1, "ra\n", 3);
}

/* Función rotate b que desplaza hacia arriba todos
los elementos del stack b una posición, de forma
que el primer elemento se convierte en el último: */

void	rb(t_stack *b)
{
	rotate_nodes(b);
	write(1, "rb\n", 3);
}

/* Función rotate a y b a la vez, desplaza hacia
arriba todos los elementos de los stacks una posición
conviertiendo el primer elemento en último: */

void	rr(t_stack *a, t_stack *b)
{
	rotate_nodes(a);
	rotate_nodes(b);
	write(1, "rr\n", 3);
}
