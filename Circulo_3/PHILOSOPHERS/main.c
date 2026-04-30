/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:58:19 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 19:21:05 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Función de cleanup
/// @param table Estructura global
/// @param code Código de retorno que se desea retornar después de cleanup
/// @return El código de retorno especificado
static int	cleanup_and_exit(t_table *table, int code)
{
	cleanup(table);
	return (code);
}

/// @brief Punto de entrada del programa Philosophers
/// @param argc Número de argumentos
/// @param argv Array args
/// @return 0 si éxito, 1 si error
int	main(int argc, char **argv)
{
	t_table	*table;

	table = parse_arguments(argc, argv);
	if (!table)
		return (1);
	if (init_mutexes(table) != 0)
		return (cleanup_and_exit(table, 1));
	if (init_forks(table) != 0)
		return (cleanup_and_exit(table, 1));
	if (init_philos(table) != 0)
		return (cleanup_and_exit(table, 1));
	if (start_simulation(table) != 0)
		return (cleanup_and_exit(table, 1));
	cleanup(table);
	return (0);
}
