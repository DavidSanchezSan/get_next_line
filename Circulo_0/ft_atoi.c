/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:31:15 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/04 14:48:19 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function that converts the initial portion of
// the string pointed to by nptr to int.

static void	ft_advance_spaces(const char *nptr, int *i)
{
	while (nptr[*i] == ' ' || (nptr[*i] >= 9 && nptr[*i] <= 13))
		(*i)++;
}

static void	ft_check_sign(const char *nptr, int *i, int *s)
{
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			*s = -1;
		(*i)++;
	}
}

int	ft_atoi(const char *nptr)
{
	int	c;
	int	i;
	int	s;

	c = 0;
	s = 1;
	i = 0;
	ft_advance_spaces(nptr, &i);
	ft_check_sign(nptr, &i, &s);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (c > (2147483647 / 10) || (c == (2147483647 / 10)
				&& (nptr[i] - '0') > (2147483647 % 10)))
		{
			if (s == 1)
				return (2147483647);
			else
				return (-2147483648);
		}
		c = c * 10 + (nptr[i] - '0');
		i++;
	}
	return (c * s);
}

// int	main(void)
// {
// 	// char	*str1;
// 	// char	*str2;
// 	// char	*str3;
// 	// char	*str4;
// 	// char	*str5;
// 	// char	*str6;
// 	// char	*str7;
// 	// char	*str8;

// 	// str1 = "    42";
// 	// str2 = "   -42abc";
// 	// str3 = "2147483648";
// 	// str4 = "89 52";
// 	// str5 = "51.6";
// 	// str6 = "  +-39z";
// 	// str7 = "2147483647";
// 	// str8 = "-2147483648";
// 	// printf("ft_atoi(\"%s\") = %d\n", str1, ft_atoi(str1));
// 	// printf("ft_atoi(\"%s\") = %d\n", str2, ft_atoi(str2));
// 	// printf("ft_atoi(\"%s\") = %d\n", str3, ft_atoi(str3));
// 	// printf("ft_atoi(\"%s\") = %d\n", str4, ft_atoi(str4));
// 	// printf("ft_atoi(\"%s\") = %d\n", str5, ft_atoi(str5));
// 	// printf("ft_atoi(\"%s\") != %d\n", str6, ft_atoi(str6));
// 	// printf("ft_atoi(\"%s\") = %d\n", str7, ft_atoi(str7));
// 	// printf("ft_atoi(\"%s\") = %d\n", str8, ft_atoi(str8));
// 	// printf("\n");
// 	// printf("atoi(\"%s\") = %d\n", str1, atoi(str1));
// 	// printf("atoi(\"%s\") = %d\n", str2, atoi(str2));
// 	// printf("atoi(\"%s\") = %d\n", str3, atoi(str3));
// 	// printf("atoi(\"%s\") = %d\n", str4, atoi(str4));
// 	// printf("atoi(\"%s\") = %d\n", str5, atoi(str5));
// 	// printf("atoi(\"%s\") != %d\n", str6, atoi(str6));
// 	// printf("atoi(\"%s\") = %d\n", str7, atoi(str7));
// 	// printf("atoi(\"%s\") = %d\n", str8, atoi(str8));
// 	return (0);
// }