/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:58:50 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 19:20:24 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Verifica si un filosofo debe terminar por muerte detectada
/// @param philo El filosofo a verificar
/// @return 1 si alguien murio (debe terminar), 0 si no
int	check_philosopher_death(t_philo *philo)
{
	int	death_flag;

	pthread_mutex_lock(&philo->table->death_lock);
	death_flag = philo->table->someone_died;
	pthread_mutex_unlock(&philo->table->death_lock);
	return (death_flag);
}

/// @brief Verifica si el filosofo debe terminar por haber comido suficiente
/// @param philo El filosofo a verificar
/// @return 1 si debe terminar (comio suficiente), 0 si debe continuar
int	check_must_eat_limit(t_philo *philo)
{
	int	should_exit;

	if (philo->table->must_eat_count <= 0)
		return (0);
	pthread_mutex_lock(&philo->table->meal_lock);
	should_exit = (philo->meals_eaten >= philo->table->must_eat_count);
	pthread_mutex_unlock(&philo->table->meal_lock);
	return (should_exit);
}
