/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:47:19 by egarcia2          #+#    #+#             */
/*   Updated: 2025/02/03 18:45:06 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] != '\0') && (nptr[i] == ' ' || (nptr[i] >= 9
				&& nptr[i] <= 13)))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}
/*
int	main(void)
{
	const char	nptr1[] = "  +-1234abc";
	const char	nptr2[] = "  ---12a4abc";
	const char	nptr3[] = "  2a4abc";
	const char	nptr4[] = "  -24abc";

	printf("atoi: %d\n", atoi(nptr1));
	printf("ft_atoi: %d\n", ft_atoi(nptr1));
	printf("atoi: %d\n", atoi(nptr2));
	printf("ft_atoi: %d\n", ft_atoi(nptr2));
	printf("atoi: %d\n", atoi(nptr3));
	printf("ft_atoi: %d\n", ft_atoi(nptr3));
	printf("atoi: %d\n", atoi(nptr4));
	printf("ft_atoi: %d\n", ft_atoi(nptr4));
	return (0);
}
*/
