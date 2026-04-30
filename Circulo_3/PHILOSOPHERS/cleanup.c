/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:58:01 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 21:38:15 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Destruye mutexes de death_lock, meal_lock y los forks inicializados
/// @param table Estructura global
void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	if (table->death_lock_init)
		pthread_mutex_destroy(&table->death_lock);
	if (table->meal_lock_init)
		pthread_mutex_destroy(&table->meal_lock);
	if (table->forks && table->forks_init_count > 0)
	{
		while (i < table->forks_init_count)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
	}
}

/// @brief Función de cleanup: libera todos los recursos
/// @param table Estructura global
void	cleanup(t_table *table)
{
	if (!table)
		return ;
	destroy_mutexes(table);
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
	free(table);
}
