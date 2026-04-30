/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:15:28 by egarcia2          #+#    #+#             */
/*   Updated: 2025/10/13 19:45:45 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_read_conversion(va_list args, char c, int count)
{
	if (c == '%')
		count = ft_print_char('%');
	else if (c == 'c')
		count = ft_print_char(va_arg(args, int));
	else if (c == 's')
		count = ft_print_str(va_arg(args, char *));
	else if (c == 'd')
		count = ft_print_nbr(va_arg(args, int));
	else if (c == 'i')
		count = ft_print_nbr(va_arg(args, int));
	else if (c == 'u')
		count = ft_print_unsigned_nbr(va_arg(args, unsigned int));
	else if (c == 'x')
		count = ft_print_hex(va_arg(args, unsigned int), c);
	else if (c == 'X')
		count = ft_print_hex(va_arg(args, unsigned int), c);
	else if (c == 'p')
		count = ft_print_ptr(va_arg(args, void *));
	return (count);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				return (-1);
			i++;
			count += ft_read_conversion(args, str[i], count);
		}
		else
			count += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
