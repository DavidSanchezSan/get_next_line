/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:50:39 by egarcia2          #+#    #+#             */
/*   Updated: 2025/01/30 20:23:14 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	sign;
	char	c;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		sign = '-';
		write(fd, &sign, 1);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	if (n >= 0 && n <= 9)
	{
		c = n + '0';
		write(fd, &c, 1);
	}
}
/*
int	main(void)
{
	int	nb;

	nb = -2147483648;
	ft_putnbr_fd(nb, 1);
	return (0);
}
*/