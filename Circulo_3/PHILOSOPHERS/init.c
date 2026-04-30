/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:58:12 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 21:46:58 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Inicializa mutexes de death_lock y meal_lock
/// @param table Estructura global
/// @return 0 si éxito, 1 si pthread_mutex_init falla
int	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->death_lock, NULL) != 0)
	{
		print_error("Error: failed to initialize death_lock");
		return (1);
	}
	table->death_lock_init = 1;
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
	{
		print_error("Error: failed to initialize meal_lock");
		return (1);
	}
	table->meal_lock_init = 1;
	return (0);
}

/// @brief Aloca el array de mutexes para forks
/// @param table Estructura global
/// @return 0 si exito, 1 si malloc falla
static int	allocate_forks_array(t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
	{
		print_error("Error: malloc failed for forks array");
		return (1);
	}
	return (0);
}

/// @brief Inicializa cada mutex de fork, marcando forks_init_count
/// @param table Estructura global
/// @return 0 si exito, 1 si pthread_mutex_init falla
static int	initialize_fork_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			print_error("Error: failed to initialize fork mutex");
			return (1);
		}
		table->forks_init_count++;
		i++;
	}
	return (0);
}

/// @brief Aloca array de mutexes para forks e inicializa cada mutex
/// @param table Estructura global
/// @return 0 si éxito, 1 si malloc o pthread_mutex_init falla
int	init_forks(t_table *table)
{
	if (allocate_forks_array(table) != 0)
		return (1);
	if (initialize_fork_mutexes(table) != 0)
		return (1);
	return (0);
}

/// @brief Aloca e inicializa array de filósofos, asigna punteros a
///			forks y a la tabla global
/// @param table Estructura global
/// @return 0 si éxito, 1 si malloc falla
int	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
	{
		print_error("Error: malloc failed for philos array");
		return (1);
	}
	i = 0;
	while (i < table->num_philos)
	{
		memset(&table->philos[i], 0, sizeof(t_philo));
		table->philos[i].id = i + 1;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1)
			% table->num_philos];
		table->philos[i].table = table;
		i++;
	}
	return (0);
}
