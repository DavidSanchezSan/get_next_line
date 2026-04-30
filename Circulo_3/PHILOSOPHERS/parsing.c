/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:58:36 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 19:18:16 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Convierte un string a entero con validación exhaustiva
/// @param str String a convertir
/// @return Entero convertido, o -1 si hay error
int	ft_atoi(const char *str)
{
	long long	result;
	int			i;

	if (!str || !*str)
		return (-1);
	i = 0;
	if (validate_and_skip_prefix(str, &i) != 0)
		return (-1);
	result = convert_digits(str, &i);
	if (result < 0)
		return (-1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (-1);
		i++;
	}
	return ((int)result);
}

/// @brief Helper para parsear y validar un parametro de tiempo
/// @param argv Array de argumentos
/// @param i Indice del argumento a parsear
/// @param error_msg Mensaje de error si falla
/// @return Valor parseado o -1 si error
static int	parse_time_param(char **argv, int i, char *error_msg)
{
	int	temp;

	temp = ft_atoi(argv[i]);
	if (temp < 1)
		return (print_error(error_msg), -1);
	return (temp);
}

/// @brief Parsea parametros requeridos
/// @param argv Array de argumentos
/// @param table Estructura a llenar
/// @return 0 si exito, -1 si error
static int	parse_required_params(char **argv, t_table *table)
{
	int	temp;

	temp = ft_atoi(argv[1]);
	if (temp < 1)
		return (print_error("Error: number of philosophers must be at least 1"),
			-1);
	table->num_philos = temp;
	temp = parse_time_param(argv, 2, "Error: time_to_die must be at least 1ms");
	if (temp < 0)
		return (-1);
	table->time_to_die = (long long)temp;
	temp = parse_time_param(argv, 3, "Error: time_to_eat must be at least 1ms");
	if (temp < 0)
		return (-1);
	table->time_to_eat = (long long)temp;
	temp = parse_time_param(argv, 4,
			"Error: time_to_sleep must be at least 1ms");
	if (temp < 0)
		return (-1);
	table->time_to_sleep = (long long)temp;
	return (0);
}

/// @brief Parsea parametro opcional must_eat_count
/// @param argc Cantidad de argumentos
/// @param argv Array de argumentos
/// @param table Estructura a llenar
/// @return 0 si exito, -1 si error
static int	parse_optional_must_eat(int argc, char **argv, t_table *table)
{
	int	temp;

	if (argc == 6)
	{
		temp = ft_atoi(argv[5]);
		if (temp < 1)
			return (print_error("Error: must_eat_count must be at least 1"),
				-1);
		table->must_eat_count = temp;
	}
	else
		table->must_eat_count = -1;
	return (0);
}

/// @brief Parsea y valida argumentos, retorna tabla global o NULL si error
/// @param argc Cantidad de argumentos
/// @param argv Array de strings con los argumentos
/// @return Puntero a t_table con los valores parseados, o NULL si error
t_table	*parse_arguments(int argc, char **argv)
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		return (print_error("Error: invalid number of arguments"),
			print_error("Usage: ./philo number_of_philosophers time_to_die "
				"time_to_eat time_to_sleep "
				"[number_of_times_each_philosopher_must_eat]"),
			NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (print_error("Error: malloc failed"), NULL);
	memset(table, 0, sizeof(t_table));
	if (parse_required_params(argv, table) != 0)
		return (free(table), NULL);
	if (parse_optional_must_eat(argc, argv, table) != 0)
		return (free(table), NULL);
	return (table);
}
