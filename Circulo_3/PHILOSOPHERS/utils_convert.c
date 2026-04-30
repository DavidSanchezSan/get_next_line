/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:59:18 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 19:17:23 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Valor absoluto para long long
/// @param n Numero del cual se quiere obtener el valor absoluto
/// @return El valor absoluto de n
static long long	ft_llabs(long long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/// @brief Escribe digitos de un entero y los invierte
/// @param temp Valor absoluto del numero
/// @param str Buffer destino
/// @param is_negative 1 si negativo, 0 si positivo
/// @return Longitud del string escrito
static int	write_integer_digits(int temp, char *str, int is_negative)
{
	int	len;

	len = 0;
	if (is_negative)
		str[len++] = '-';
	if (temp == 0)
		str[len++] = '0';
	while (temp > 0)
	{
		str[len++] = (temp % 10) + '0';
		temp /= 10;
	}
	str[len] = '\0';
	if (is_negative)
		reverse_str_range(str, 1, len - 1);
	else
		reverse_str_range(str, 0, len - 1);
	return (len);
}

/// @brief Escribe digitos de un long long y los invierte
/// @param temp Valor absoluto del numero
/// @param str Buffer destino
/// @param is_negative 1 si negativo, 0 si positivo
/// @return Longitud del string escrito
static int	write_longlong_digits(long long temp, char *str, int is_negative)
{
	int	len;

	len = 0;
	if (is_negative)
		str[len++] = '-';
	if (temp == 0)
		str[len++] = '0';
	while (temp > 0)
	{
		str[len++] = (temp % 10) + '0';
		temp /= 10;
	}
	str[len] = '\0';
	if (is_negative)
		reverse_str_range(str, 1, len - 1);
	else
		reverse_str_range(str, 0, len - 1);
	return (len);
}

/// @brief Convierte un int a string. Maneja numeros negativos e INT_MIN
/// @param n Numero a convertir
/// @param str Buffer donde se guardara el string resultante
/// @return La longitud del string escrito (sin contar '\0')
int	ft_itoa(int n, char *str)
{
	long long	temp;

	if (!str)
		return (0);
	if (n == INT_MIN)
		return (ft_strcpy(str, "-2147483648"), 11);
	temp = ft_llabs((long long)n);
	return (write_integer_digits((int)temp, str, n < 0));
}

/// @brief Convierte un long long a string. Maneja negativos y LLONG_MIN
/// @param n Numero a convertir
/// @param str Buffer donde se guardara el string resultante
/// @return La longitud del string escrito (sin contar '\0')
int	ft_lltoa(long long n, char *str)
{
	long long	temp;

	if (!str)
		return (0);
	if (n == LLONG_MIN)
		return (ft_strcpy(str, "-9223372036854775808"), 20);
	temp = ft_llabs(n);
	return (write_longlong_digits(temp, str, n < 0));
}
