/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:58:25 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 19:20:44 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Verifica si un filosofo especifico murio y marca someone_died si sí
/// @param index Indice del filosofo a verificar
/// @param now Timestamp actual en milisegundos
/// @param table Estructura con todos los datos de la simulacion
/// @return 1 si el filosofo murio, 0 si no
static int	check_philosopher_lifespan(int index, long long now, t_table *table)
{
	long long	last_meal;

	last_meal = table->philos[index].last_meal_time;
	if (now - last_meal > table->time_to_die)
	{
		print_death(&table->philos[index]);
		pthread_mutex_lock(&table->death_lock);
		table->someone_died = 1;
		pthread_mutex_unlock(&table->death_lock);
		return (1);
	}
	return (0);
}

/// @brief Verifica si algun filosofo murio y marca someone_died si es asi
/// @param table Estructura con todos los datos de la simulacion
/// @return 1 si algun filosofo murio, 0 si no
int	check_deaths(t_table *table)
{
	int			i;
	long long	now;

	i = 0;
	now = get_time_ms();
	pthread_mutex_lock(&table->meal_lock);
	while (i < table->num_philos)
	{
		if (check_philosopher_lifespan(i, now, table))
		{
			pthread_mutex_unlock(&table->meal_lock);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&table->meal_lock);
	return (0);
}

/// @brief Verifica si todos los filosofos comieron suficiente y retorna 1 si sí
/// @param table Estructura con todos los datos de la simulacion
/// @return 1 si todos comieron suficiente, 0 si no o si must_eat_count <= 0
int	check_all_ate(t_table *table)
{
	int	i;
	int	all_ate;

	if (table->must_eat_count <= 0)
		return (0);
	i = 0;
	all_ate = 1;
	pthread_mutex_lock(&table->meal_lock);
	while (i < table->num_philos)
	{
		if (table->philos[i].meals_eaten < table->must_eat_count)
		{
			all_ate = 0;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&table->meal_lock);
	return (all_ate);
}

/// @brief Rutina del monitor: verifica periodicamente si algun filosofo
///		   murio o si todos comieron suficiente, y marca someone_died
///		   para terminar simulacion
/// @param arg Puntero a t_table
/// @return NULL al finalizar
void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		usleep(1000);
		if (check_all_ate(table))
			return (NULL);
		if (check_deaths(table))
			return (NULL);
	}
	return (NULL);
}
