/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort_small.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:27:12 by dasanche          #+#    #+#             */
/*   Updated: 2025/06/13 13:07:10 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Función para dos elementos:

void	sort_2(t_stack *a)
{
	if (a->size != 2 || is_sorted(a))
		return ;
	if (a->top->index > a->top->next->index)
		sa(a);
}

// Función para tres elementos:

void	sort_3(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	if (a->size != 3 || is_sorted(a))
		return ;
	first = a->top->index;
	second = a->top->next->index;
	third = a->top->next->next->index;
	if (first < third && third < second)
	{
		sa(a);
		ra(a);
	}
	else if (second < first && first < third)
		sa(a);
	else if (third < first && first < second)
		rra(a);
	else if (second < third && third < first)
		ra(a);
	else if (third < second && second < first)
	{
		sa(a);
		rra(a);
	}
}

/*
Caso 1: 0 2 1 → sa + ra
Caso 2: 1 0 2 → sa
Caso 3: 1 2 0 → rra
Caso 4: 2 0 1 → ra
Caso 5: 2 1 0 → sa + rra
*/

// Función para cuatro elementos:

void	sort_4(t_stack *a, t_stack *b)
{
	t_node	*min;

	if (a->size != 4 || is_sorted(a))
		return ;
	min = find_min_node(a);
	move_node_to_top(a, min);
	pb(a, b);
	sort_3(a);
	pa(a, b);
}

// Función para cinco elementos:

void	sort_5(t_stack *a, t_stack *b)
{
	t_node	*min;

	if (a->size != 5 || is_sorted(a))
		return ;
	min = find_min_node(a);
	move_node_to_top(a, min);
	pb(a, b);
	min = find_min_node(a);
	move_node_to_top(a, min);
	pb(a, b);
	sort_3(a);
	if (b->top->index < b->top->next->index)
		sb(b);
	pa(a, b);
	pa(a, b);
}

/*
Sacar primer mínimo
Sacar segundo mínimo
Ordenar los 3 restantes
Ordenar stack B si hace falta (solo 2 elementos)
Volver a meter los dos mínimos
*/

// Función que unifica el ordenamiento de poco elementos:
void	sort_small(t_stack *a, t_stack *b)
{
	if (is_sorted(a))
		return ;
	if (a->size == 1)
		return ;
	if (a->size == 2)
		sort_2(a);
	else if (a->size == 3)
		sort_3(a);
	else if (a->size == 4)
		sort_4(a, b);
	else if (a->size == 5)
		sort_5(a, b);
}
