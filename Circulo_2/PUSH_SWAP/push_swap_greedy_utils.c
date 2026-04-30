/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_greedy_sort.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:22:46 by dasanche          #+#    #+#             */
/*   Updated: 2025/06/15 22:18:51 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Busca la posición del nodo con el índice más pequeño
//  que sea mayor que b_index. Si no encuentra ninguno, indica con *found = 0.

int	find_target_pos_greater(t_stack *a, int b_index, int *found)
{
	t_node	*current;
	int		pos;
	int		best_index;
	int		best_pos;

	current = a->top;
	pos = 0;
	best_index = __INT_MAX__;
	best_pos = 0;
	*found = 0;
	while (current)
	{
		if (current->index > b_index && current->index < best_index)
		{
			best_index = current->index;
			best_pos = pos;
			*found = 1;
		}
		pos++;
		current = current->next;
	}
	return (best_pos);
}

// Busca la posición del nodo con el índice mínimo en toda la pila.

int	find_min_index_pos(t_stack *a)
{
	t_node	*current;
	int		pos;
	int		best_index;
	int		best_pos;

	current = a->top;
	pos = 0;
	best_index = __INT_MAX__;
	best_pos = 0;
	while (current)
	{
		if (current->index < best_index)
		{
			best_index = current->index;
			best_pos = pos;
		}
		pos++;
		current = current->next;
	}
	return (best_pos);
}

void	find_best_positions(t_stack *a, t_stack *b, int *best_a_pos,
							int *best_b_pos)
{
	t_node	*current;
	int		best_cost;
	int		target_pos;
	int		cost;
	int		i;

	current = b->top;
	best_cost = __INT_MAX__;
	*best_a_pos = 0;
	*best_b_pos = 0;
	i = 0;
	while (current)
	{
		target_pos = get_target_pos(a, current->index);
		cost = get_cost(a->size, target_pos, b->size, i);
		if (cost < best_cost)
		{
			best_cost = cost;
			*best_a_pos = target_pos;
			*best_b_pos = i;
		}
		i++;
		current = current->next;
	}
}
// Realiza rotaciones cuando los elementos objetivo en ambas pilas
// están en la mitad superior de sus respectivas pilas.
// Usa rotaciones simultáneas (rr) mientras sea posible,
// luego completa con rotaciones individuales (ra y rb).

void	perform_upper_half_rotations(t_stack *a, t_stack *b,
									int best_a_pos, int best_b_pos)
{
	int	a_rot;
	int	b_rot;
	int	a_size;
	int	b_size;

	a_rot = best_a_pos;
	b_rot = best_b_pos;
	a_size = a->size;
	b_size = b->size;
	while (a_rot > 0 && b_rot > 0 && a_rot <= a_size / 2 && b_rot <= b_size / 2)
	{
		rr(a, b);
		a_rot--;
		b_rot--;
	}
	while (a_rot-- > 0 && best_a_pos <= a_size / 2)
		ra(a);
	while (b_rot-- > 0 && best_b_pos <= b_size / 2)
		rb(b);
}

// Realiza rotaciones cuando los elementos objetivo en ambas pilas
// están en la mitad inferior de sus respectivas pilas.
// Usa rotaciones inversas simultáneas (rrr) mientras sea posible,
// luego completa con rotaciones inversas individuales (rra y rrb).

void	perform_lower_half_rotations(t_stack *a, t_stack *b,
									int best_a_pos, int best_b_pos)
{
	int	a_size;
	int	b_size;
	int	a_rot;
	int	b_rot;

	a_size = a->size;
	b_size = b->size;
	a_rot = a_size - best_a_pos;
	b_rot = b_size - best_b_pos;
	while (a_rot > 0 && b_rot > 0 && best_a_pos
		> a_size / 2 && best_b_pos > b_size / 2)
	{
		rrr(a, b);
		a_rot--;
		b_rot--;
	}
	while (a_rot-- > 0 && best_a_pos > a_size / 2)
		rra(a);
	while (b_rot-- > 0 && best_b_pos > b_size / 2)
		rrb(b);
}
// Caso 1 (1 while): Ambos en mitad superior → usar rr
// Caso 2 (a_rot =): Ambos en mitad inferior → usar rrr