/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:59:24 by dasanche          #+#    #+#             */
/*   Updated: 2026/03/17 19:17:24 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Calcula la longitud de un string (sin contar '\0')
/// @param str El string del cual se quiere obtener la longitud
/// @return La longitud del string (0 si str es NULL)
int	ft_strlen(const char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

/// @brief Copia un string de src a dest (incluyendo el '\0').
/// @param dest El buffer donde se copiara el string
/// @param src El string a copiar
/// @return Un puntero a dest, o NULL si dest o src es NULL
char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/// @brief Copia un string de src a dest con un offset
/// @param dest El buffer donde se copiara el string
/// @param src El string a copiar
/// @param offset La posicion en dest donde se comenzara a copiar
/// @return La cantidad de caracteres copiados (sin contar '\0')
int	ft_strcpy_offset(char *dest, const char *src, int offset)
{
	int	i;

	if (!dest || !src || offset < 0)
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		dest[offset + i] = src[i];
		i++;
	}
	dest[offset + i] = '\0';
	return (i);
}

/// @brief Invierte un string en un rango especifico
/// @param str String a invertir
/// @param start Indice de inicio
/// @param end Indice de fin
void	reverse_str_range(char *str, int start, int end)
{
	char	temp;

	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}
