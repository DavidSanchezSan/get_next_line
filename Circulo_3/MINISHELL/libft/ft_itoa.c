/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:45:04 by egarcia2          #+#    #+#             */
/*   Updated: 2025/02/03 18:45:05 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_len(int n)
{
	size_t	len;
	int		aux;

	len = 0;
	aux = n;
	if (n == 0)
		len++;
	if (n < 0)
	{
		len++;
		aux = -aux;
	}
	while (aux != 0)
	{
		aux = aux / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	long	num;

	num = n;
	len = ft_count_len(n);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
		num = -num;
	while (len > 0)
	{
		str[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
/*
int	main(void)
{
	int n;
	char *s;

	n = -90;
	s = ft_itoa(n);
	printf("%s\n", s);
}
*/