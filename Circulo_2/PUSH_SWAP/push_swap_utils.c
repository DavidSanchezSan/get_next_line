/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:09:31 by dasanche          #+#    #+#             */
/*   Updated: 2025/06/07 12:09:31 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Función atol que convierte en long long los arrays:

static void	ft_check_sign(const char *nptr, int *i, int *s)
{
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			*s = -1;
		(*i)++;
	}
}

long long	ft_atol(const char *nptr)
{
	long long	c;
	int			i;
	int			s;

	c = 0;
	s = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		(i)++;
	ft_check_sign(nptr, &i, &s);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		c = c * 10 + (nptr[i] - '0');
		i++;
	}
	return (c * s);
}

/* Función para validar el string controlando
que solo haya dígitos o un único sigo
+ dígitos: */

int	ft_check_valid_input_string(char *s)
{
	int	x;

	x = 0;
	while (s[x])
	{
		if ((s[x] == '-' || s[x] == '+')
			&& (!s[x + 1] || (s[x + 1] < '0' || s[x + 1] > '9')))
			return (0);
		else if ((s[x] < '0' || s[x] > '9') && s[x] != ' ' && s[x] != '-'
			&& s[x] != '+')
			return (0);
		x++;
	}
	return (1);
}

// Función que controla que no haya números repetidos:

int	ft_check_duplicate(long long *nbrs, int num_tokens)
{
	int	x;
	int	j;

	x = 0;
	while (x < num_tokens)
	{
		j = x + 1;
		while (j < num_tokens)
		{
			if (nbrs[x] == nbrs[j])
				return (0);
			j++;
		}
		x++;
	}
	return (1);
}

// Función para liberar array:

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}
