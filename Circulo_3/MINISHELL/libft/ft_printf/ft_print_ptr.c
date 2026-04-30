/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:30:02 by egarcia2          #+#    #+#             */
/*   Updated: 2025/10/13 19:48:21 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_ptr(void *ptr)
{
	int				i;
	unsigned long	ptr_add;

	i = 0;
	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	i += 2;
	ptr_add = (unsigned long)ptr;
	i += ft_print_hex(ptr_add, 'x');
	return (i);
}
