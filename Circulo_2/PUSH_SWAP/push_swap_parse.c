/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:27:29 by dasanche          #+#    #+#             */
/*   Updated: 2025/06/13 13:47:24 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Función para dividir y tokenizar cada uno
de los elementos que se reciban como input: */

char	**ft_parse(int argc, char **argv)
{
	char	**tokens;

	tokens = NULL;
	if (argc == 2)
		tokens = ft_split(argv[1], ' ');
	else
		tokens = &argv[1];
	return (tokens);
}

/* Función para manejar errores en el parseo:
Libera memoria de nbr_tokens si está asignada,
y si argc==2 (se usó ft_split) libera también tokens.
Imprime "Error\n" por stderr y retorna NULL para señalizar fallo. */

static long long	*handle_parse_error(long long *nbr_tokens, char **tokens,
		int argc)
{
	if (nbr_tokens)
		free(nbr_tokens);
	if (argc == 2 && tokens)
		free_split(tokens);
	write(2, "Error\n", 6);
	return (NULL);
}

// Cuenta cuántos tokens (strings) hay en el array terminado en NULL

static int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

/* Valida tokens comprobando su formato, convierte
a long y almacena en nbr_tokens. También comprueba
que los números estén dentro de INT_MIN a INT_MAX
y que no haya duplicados. Devuelve 1 si todo es correcto,
0 si hay error */

static int	validate_tokens(char **tokens, long long *nbr_tokens,
		int num_tokens)
{
	int	j;

	j = 0;
	while (tokens[j])
	{
		if (!ft_check_valid_input_string(tokens[j]))
			return (0);
		nbr_tokens[j] = ft_atol(tokens[j]);
		if (nbr_tokens[j] > INT_MAX || nbr_tokens[j] < INT_MIN)
			return (0);
		j++;
	}
	if (!ft_check_duplicate(nbr_tokens, num_tokens))
		return (0);
	return (1);
}

/* Función que parsea argumentos, valida, convierte,
detecta errores, y libera memoria si falla.
Devuelve array de long con los números parseados si éxito,
NULL y mensaje de error si falla */

long long	*error_control_parse(int argc, char **argv)
{
	char		**tokens;
	long long	*nbr_tokens;
	int			num_tokens;

	tokens = ft_parse(argc, argv);
	num_tokens = count_tokens(tokens);
	if (num_tokens == 0)
		return (handle_parse_error(NULL, tokens, argc));
	nbr_tokens = malloc(num_tokens * sizeof(long long));
	if (!nbr_tokens)
		return (handle_parse_error(NULL, tokens, argc));
	if (!validate_tokens(tokens, nbr_tokens, num_tokens))
		return (handle_parse_error(nbr_tokens, tokens, argc));
	if (argc == 2)
		free_split(tokens);
	return (nbr_tokens);
}
