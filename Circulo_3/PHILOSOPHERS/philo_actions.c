/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:58:43 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 19:18:12 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Filósofo piensa
/// @param philo Puntero al filósofo que está pensando
void	philo_think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

/// @brief Función duerme: imprime acción y duerme durante time_to_sleep
/// @param philo Puntero al filósofo que está durmiendo
void	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	precise_sleep(philo->table->time_to_sleep);
}
