/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:56:34 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/04 14:40:08 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Using malloc, generate a string representing the integer value received as
// an argument. Negative numbers have to be handled.

static char	*negative_special_case(int *n)
{
	char	*c;

	if (*n == -2147483648)
	{
		c = ((char *)malloc(12));
		if (c == NULL)
			return (NULL);
		ft_strlcpy(c, "-2147483648", 12);
		return (c);
	}
	return (NULL);
}

static void	negative_sign(int *n, int *is_negative, int *len, int *temp)
{
	if (*n < 0)
	{
		*n = -*n;
		*temp = -*temp;
		*is_negative = 1;
		(*len)++;
	}
}

static void	calculate_len(int *n, int *len, int *temp)
{
	if (*n == 0)
	{
		*len = 1;
		return ;
	}
	while (*temp > 0)
	{
		*temp = *temp / 10;
		(*len)++;
	}
}

static char	*convert_number(int *n, int *len, char *c)
{
	if (*n == 0)
	{
		c[0] = '0';
		return (c);
	}
	while (*n > 0)
	{
		c[*len] = *n % 10 + '0';
		(*len)--;
		*n = *n / 10;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	char	*c;
	int		len;
	int		temp;
	int		is_negative;

	temp = n;
	len = 0;
	is_negative = 0;
	if (n == -2147483648)
		return (c = negative_special_case(&n));
	negative_sign(&n, &is_negative, &len, &temp);
	calculate_len(&n, &len, &temp);
	c = malloc((len + 1) * (sizeof(char)));
	if (c == NULL)
		return (NULL);
	c[len] = '\0';
	len--;
	c = convert_number(&n, &len, c);
	if (is_negative)
		c[0] = '-';
	return (c);
}

// int	main(void)
// {
// 	int		n;
// 	char	*c;

// 	n = 2147483647;
// 	c = ft_itoa(n);
// 	printf("%s\n", c);
// 	free(c);
// 	return (0);
// }
