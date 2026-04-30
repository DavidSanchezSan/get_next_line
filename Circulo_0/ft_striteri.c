/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:21:29 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 15:16:16 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// To each character in the string ‘s’, apply the function ‘f’ giving as
// parameters the index of each character within ‘s’ and the address of the
// character itself, which may be modified if necessary.

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	x;

	x = 0;
	while (s[x] != '\0')
	{
		f(x, &s[x]);
		x++;
	}
}

// void	ft_toupper_test(unsigned int c, char *ch)
// {
// 	if (c % 2 == 0 && *ch >= 'a' && *ch <= 'z')
// 	{
// 		*ch = *ch - 32;
// 	}
// }

// int	main(void)
// {
// 	char str[] = "hola mundo";
// 	ft_striteri(str, ft_toupper_test);
// 	printf("%s", str);
// 	return (0);
// }