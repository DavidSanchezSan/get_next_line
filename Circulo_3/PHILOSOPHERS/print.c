/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:59:04 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 19:17:27 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Construye el mensaje de accion
/// @param time_str String del timestamp
/// @param id_str String del id del filosofo
/// @param action String de la accion
/// @param buffer Buffer donde se construira el mensaje
/// @return Longitud del mensaje construido
static int	format_action_message(const char *time_str, const char *id_str,
		const char *action, char *buffer)
{
	int	len;

	len = 0;
	len += ft_strcpy_offset(buffer, time_str, len);
	buffer[len++] = ' ';
	len += ft_strcpy_offset(buffer, id_str, len);
	buffer[len++] = ' ';
	len += ft_strcpy_offset(buffer, action, len);
	buffer[len++] = '\n';
	buffer[len] = '\0';
	return (len);
}

/// @brief Verifica someone_died, construye mensaje y lo escribe bajo lock
/// @param philo El filosofo que realiza la accion
/// @param action La accion a imprimir
static void	write_action_under_lock(t_philo *philo, const char *action)
{
	char		buffer[256];
	char		time_str[32];
	char		id_str[16];
	int			len;
	long long	timestamp;

	pthread_mutex_lock(&philo->table->death_lock);
	if (philo->table->someone_died)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		return ;
	}
	timestamp = elapsed_time(philo->table);
	ft_lltoa(timestamp, time_str);
	ft_itoa(philo->id, id_str);
	len = format_action_message(time_str, id_str, action, buffer);
	write(1, buffer, len);
	pthread_mutex_unlock(&philo->table->death_lock);
}

/// @brief Imprime el mensaje de acción de un filósofo si no ha detectado muerte
/// @param philo El filósofo que realiza la acción
/// @param action La acción a imprimir
void	print_action(t_philo *philo, const char *action)
{
	if (!philo || !action)
		return ;
	write_action_under_lock(philo, action);
}

/// @brief Imprime el mensaje de muerte de un filósofo
/// @param philo El filósofo que murió
void	print_death(t_philo *philo)
{
	char		buffer[256];
	char		time_str[32];
	char		id_str[16];
	int			len;
	long long	timestamp;

	if (!philo)
		return ;
	timestamp = elapsed_time(philo->table);
	ft_lltoa(timestamp, time_str);
	ft_itoa(philo->id, id_str);
	len = 0;
	len += ft_strcpy_offset(buffer, time_str, len);
	buffer[len++] = ' ';
	len += ft_strcpy_offset(buffer, id_str, len);
	buffer[len++] = ' ';
	len += ft_strcpy_offset(buffer, "died", len);
	buffer[len++] = '\n';
	buffer[len] = '\0';
	write(1, buffer, len);
}
