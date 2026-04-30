/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:58:54 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 18:52:49 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Maneja el caso especial de 1 solo filosofo
/// @param philo Puntero al filosofo
/// @return NULL al finalizar
static void	*handle_single_philo(t_philo *philo)
{
	print_action(philo, "is thinking");
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	while (1)
	{
		pthread_mutex_lock(&philo->table->death_lock);
		if (philo->table->someone_died)
		{
			pthread_mutex_unlock(&philo->table->death_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->death_lock);
		usleep(1000);
	}
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

/// @brief Rutina principal de cada filosofo
/// @param arg Puntero a t_philo
/// @return NULL al finalizar
void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->num_philos == 1)
		return (handle_single_philo(philo));
	if (philo->id % 2 == 0)
		usleep(10000);
	while (1)
	{
		if (check_philosopher_death(philo))
			return (NULL);
		if (check_must_eat_limit(philo))
			return (NULL);
		philo_think(philo);
		take_forks(philo);
		philo_eat(philo);
		drop_forks(philo);
		philo_sleep(philo);
	}
}

/// @brief Tomar los tenedores en orden por dirección de memoria
/// @param philo Puntero al filósofo que tomará los forks
void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(second);
	print_action(philo, "has taken a fork");
}

/// @brief Suelta los tenedores
/// @param philo Puntero al filósofo que soltará los forks
void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

/// @brief Función para que el filósofo coma
/// @param philo Puntero al filósofo que está comiendo
void	philo_eat(t_philo *philo)
{
	long long	now;

	now = get_time_ms();
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->last_meal_time = now;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_lock);
	precise_sleep(philo->table->time_to_eat);
}
