/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_greedy_sort.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:36:22 by dasanche          #+#    #+#             */
/*   Updated: 2025/06/13 12:56:39 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Coordina las rotaciones necesarias para mover el elemento con el menor coste
// desde la pila B hacia su posición correcta en la pila A.
// Primero intenta con rotaciones normales (parte superior),
// luego con rotaciones inversas (parte inferior).

void	perform_rotations(t_stack *a, t_stack *b,
						int best_a_pos, int best_b_pos)
{
	perform_upper_half_rotations(a, b, best_a_pos, best_b_pos);
	perform_lower_half_rotations(a, b, best_a_pos, best_b_pos);
}

/*
Devuelve la posición objetivo para insertar un
elemento con índice b_index en la pila a.
Intenta encontrar el nodo con índice mayor
más cercano; si no, devuelve el mínimo índice
*/

int	get_target_pos(t_stack *a, int b_index)
{
	int	found;
	int	pos;

	pos = find_target_pos_greater(a, b_index, &found);
	if (!found)
		pos = find_min_index_pos(a);
	return (pos);
}

// Función que calcula cuántas operaciones costaría hacer
// a y b girar para colocar el nodo de b en la posición a_pos:

int	get_cost(int a_size, int a_pos, int b_size, int b_pos)
{
	int	cost_a;
	int	cost_b;

	if (a_pos <= a_size / 2)
		cost_a = a_pos;
	else
		cost_a = a_size - a_pos;
	if (b_pos <= b_size / 2)
		cost_b = b_pos;
	else
		cost_b = b_size - b_pos;
	return (cost_a + cost_b);
}

// Calcula todos los costes de movimientos y hace el más barato:

void	do_cheapest_move(t_stack *a, t_stack *b)
{
	int	best_a_pos;
	int	best_b_pos;

	find_best_positions(a, b, &best_a_pos, &best_b_pos);
	perform_rotations(a, b, best_a_pos, best_b_pos);
	pa(a, b);
}

// Algortimo completo para casos superiores a 5:

void	greedy_sort(t_stack *a, t_stack *b)
{
	t_node	*min;

	while (a->size > 3)
		pb(a, b);
	sort_3(a);
	while (b->size > 0)
		do_cheapest_move(a, b);
	min = find_min_node(a);
	move_node_to_top(a, min);
}

/*
Hace push b
Ordena los 3 que quedaron en A
Reinserta uno por uno
Finalmente rota A hasta que el más pequeño esté arriba
*/