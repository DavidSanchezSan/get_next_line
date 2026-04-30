/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:12:02 by egarcia2          #+#    #+#             */
/*   Updated: 2025/10/13 19:46:01 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_hex(unsigned long n, char flag)
{
	char	*str;
	int		i;

	if (flag == 'x')
		str = "0123456789abcdef";
	else if (flag == 'X')
		str = "0123456789ABCDEF";
	else
		return (0);
	i = 0;
	if (n > 15)
		i += ft_print_hex(n / 16, flag);
	write(1, &str[n % 16], 1);
	i++;
	return (i);
}
