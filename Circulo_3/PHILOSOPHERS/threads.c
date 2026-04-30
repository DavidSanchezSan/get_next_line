/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:59:11 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 19:17:26 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Inicializa los timestamps last_meal_time de todos los filosofos
/// @param table Puntero a la estructura de la mesa
static void	init_philo_times(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].last_meal_time = table->start_time;
		i++;
	}
}

/// @brief Crea los threads de los filosofos
/// @param table Puntero a la estructura de la mesa
/// @return 0 si exito, o el fallo
static int	create_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				philosopher_routine, &table->philos[i]) != 0)
		{
			print_error("Error: pthread_create failed");
			pthread_mutex_lock(&table->death_lock);
			table->someone_died = 1;
			pthread_mutex_unlock(&table->death_lock);
			while (--i >= 0)
				pthread_join(table->philos[i].thread, NULL);
			return (-1);
		}
		i++;
	}
	return (0);
}

/// @brief Maneja el error de creacion del thread monitor
/// @param table Puntero a la estructura de la mesa
static void	handle_monitor_error(t_table *table)
{
	int	i;

	print_error("Error: pthread_create monitor failed");
	pthread_mutex_lock(&table->death_lock);
	table->someone_died = 1;
	pthread_mutex_unlock(&table->death_lock);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

/// @brief Hace join de todos los threads
/// @param table Puntero a la estructura de la mesa
static void	join_all_threads(t_table *table)
{
	int	i;

	pthread_join(table->monitor_thread, NULL);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

/// @brief Inicia la simulacion creando threads para cada filosofo y el monitor
/// @param table Puntero a la estructura de la mesa
/// @return 0 si exito, 1 si error
int	start_simulation(t_table *table)
{
	table->start_time = get_time_ms();
	init_philo_times(table);
	if (create_philo_threads(table) != 0)
		return (1);
	if (pthread_create(&table->monitor_thread, NULL,
			monitor_routine, table) != 0)
		handle_monitor_error(table);
	join_all_threads(table);
	return (0);
}
