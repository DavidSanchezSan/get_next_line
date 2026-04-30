/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:44 by dasanche          #+#    #+#             */
/*   Updated: 2025/06/03 13:08:37 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

//Nodo para los stacks (representación de valor en la lista):
typedef struct s_node
{
	int				value; //Numero original
	int				index; //Indice en el orden (algoritmo)
	struct s_node	*next; //Siguiente nodo en el stack
}	t_node;

//Lista enlazada para crear los stacks:
typedef struct s_stack
{
	t_node	*top; // Puntero al primer nodo de la pila
	int		size; // Tamaño o elementos
	char	name; // Nombre del stack 'A' o 'B'
}	t_stack;

// Funciones auxiliares para parseo y control de errores:
long long			*error_control_parse(int argc, char **argv);
char				**ft_parse(int argc, char **argv);
int					ft_check_valid_input_string(char *s);
char				**ft_split(char const *s, char c);
long long			ft_atol(const char *nptr);
void				free_split(char **split);
int					ft_check_duplicate(long long *nbrs, int num_tokens);
size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
// Funciones del stack:
t_stack				*init_stack_b(void);
void				print_stack(t_stack *stack);
t_node				*new_node(int value);
void				free_stack(t_stack *stack);
void				assign_indexes(t_stack *stack);
t_stack				*init_stack_a(long long *nbrs, int count);
// Funciones para los movimientos:
void				sa(t_stack *a);
void				sb(t_stack *b);
void				ss(t_stack *a, t_stack *b);
void				pa(t_stack *a, t_stack *b);
void				pb(t_stack *a, t_stack *b);
void				ra(t_stack *a);
void				rb(t_stack *b);
void				rr(t_stack *a, t_stack *b);
void				rra(t_stack *a);
void				rrb(t_stack *b);
void				rrr(t_stack *a, t_stack *b);
// Funciones para el algoritmo:
int					is_sorted(t_stack *stack);
t_node				*find_min_node(t_stack *stack);
void				move_node_to_top(t_stack *s, t_node *t);
void				sort_2(t_stack *a);
void				sort_3(t_stack *a);
void				sort_4(t_stack *a, t_stack *b);
void				sort_5(t_stack *a, t_stack *b);
void				sort_small(t_stack *a, t_stack *b);
void				perform_rotations(t_stack *a, t_stack *b,
						int best_a_pos, int best_b_pos);
int					get_target_pos(t_stack *a, int b_index);
int					get_cost(int a_size, int a_pos, int b_size, int b_pos);
void				do_cheapest_move(t_stack *a, t_stack *b);
void				greedy_sort(t_stack *a, t_stack *b);
int					find_target_pos_greater(t_stack *a,
						int b_index, int *found);
int					find_min_index_pos(t_stack *a);
void				find_best_positions(t_stack *a, t_stack *b,
						int *best_a_pos, int *best_b_pos);
void				perform_upper_half_rotations(t_stack *a, t_stack *b,
						int best_a_pos, int best_b_pos);
void				perform_lower_half_rotations(t_stack *a, t_stack *b,
						int best_a_pos, int best_b_pos);
// End of preprocessor directives / guards:
#endif // PUSH_SWAP_H