/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:59:29 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 21:48:22 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Obtiene el timestamp actual en milisegundos desde el Epoch (1/1/1970)
/// @return El timestamp actual en milisegundos, o -1 si ocurre un error
long long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

/// @brief Calcula tiempo desde el inicio de la simulacion hasta momento actual.
/// @param table Puntero a la estructura de datos
/// @return El tiempo transcurrido en milisegundos desde el inicio de simulacion
long long	elapsed_time(t_table *table)
{
	long long	current;

	if (!table || table->start_time == 0)
		return (0);
	current = get_time_ms();
	if (current < 0)
		return (0);
	return (current - table->start_time);
}

/// @brief Duerme durante la cantidad de milisegundos especificada.
/// @param ms La cantidad de milisegundos que se desea dormir
void	precise_sleep(long long ms)
{
	long long	start;

	if (ms <= 0)
		return ;
	start = get_time_ms();
	while (get_time_ms() - start < ms)
		usleep(100);
}

/// @brief Imprime un mensaje de error, seguido de un salto de linea.
/// @param message El mensaje de error a imprimir
void	print_error(char *message)
{
	if (!message)
		return ;
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}
