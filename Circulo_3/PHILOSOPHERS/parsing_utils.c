/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:58:32 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 18:50:29 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Validar si un carácter es un dígito
/// @param c Carácter a validar
/// @return 1 si es dígito, 0 si no
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/// @brief Validar si un carácter es un espacio en blanco
/// @param c Carácter a validar
/// @return 1 si es espacio, 0 si no
int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

/// @brief Valida y salta espacios iniciales, signo y primer digito
/// @param str String a procesar
/// @param i Puntero al indice
/// @return 0 si exito, -1 si error
int	validate_and_skip_prefix(const char *str, int *i)
{
	while (ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] == '+')
		(*i)++;
	else if (str[*i] == '-')
		return (-1);
	if (!ft_isdigit(str[*i]))
		return (-1);
	return (0);
}

/// @brief Convierte digitos a long long con overflow check
/// @param str String a convertir
/// @param i Puntero al indice
/// @return Valor convertido, o -1 si overflow
long long	convert_digits(const char *str, int *i)
{
	long long	result;

	result = 0;
	while (ft_isdigit(str[*i]))
	{
		result = result * 10 + (str[*i] - '0');
		if (result > INT_MAX)
			return (-1);
		(*i)++;
	}
	return (result);
}
