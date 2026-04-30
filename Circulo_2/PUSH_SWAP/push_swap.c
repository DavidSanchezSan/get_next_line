/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:51 by dasanche          #+#    #+#             */
/*   Updated: 2025/06/13 13:52:20 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	parse_args(int argc, char **argv,
						long long **nbr_tokens, char ***tokens)
{
	*nbr_tokens = error_control_parse(argc, argv);
	if (!*nbr_tokens)
		return (0);
	*tokens = ft_parse(argc, argv);
	if (!*tokens)
	{
		free(*nbr_tokens);
		return (0);
	}
	return (1);
}

static t_stack	*create_stack_a(long long *nbr_tokens,
								char **tokens, int *num_tokens)
{
	t_stack	*stack_a;

	*num_tokens = 0;
	while (tokens[*num_tokens])
		(*num_tokens)++;
	stack_a = init_stack_a(nbr_tokens, *num_tokens);
	if (!stack_a)
	{
		free(nbr_tokens);
		free_split(tokens);
		return (NULL);
	}
	return (stack_a);
}

static int	init_stacks(t_stack **stack_a, t_stack **stack_b,
						long long *nbr_tokens, char **tokens)
{
	*stack_b = init_stack_b();
	if (!*stack_a || !*stack_b)
	{
		write(2, "Error al crear stacks\n", 23);
		free(nbr_tokens);
		free_split(tokens);
		return (0);
	}
	return (1);
}

static void	sort_and_cleanup(t_stack *a, t_stack *b, long long *nbr_tokens)
{
	assign_indexes(a);
	if (a->size <= 5)
		sort_small(a, b);
	else
		greedy_sort(a, b);
	free_stack(a);
	free_stack(b);
	free(nbr_tokens);
}

int	main(int argc, char **argv)
{
	long long	*nbr_tokens;
	char		**tokens;
	t_stack		*stack_a;
	t_stack		*stack_b;
	int			num_tokens;

	if (argc < 2)
		return (0);
	if (!parse_args(argc, argv, &nbr_tokens, &tokens))
		return (1);
	stack_a = create_stack_a(nbr_tokens, tokens, &num_tokens);
	if (!stack_a)
		return (1);
	if (!init_stacks(&stack_a, &stack_b, nbr_tokens, tokens))
		return (1);
	sort_and_cleanup(stack_a, stack_b, nbr_tokens);
	if (argc == 2)
		free_split(tokens);
	return (0);
}

/*
	t_node *x = a->top;
	printf("----------------------");
	printf("\n%d\n", x->value);
	while(x->next != NULL)
	{
		x = x->next;
		printf("%d\n", x->value);
	}
	printf("----------------------");
*/