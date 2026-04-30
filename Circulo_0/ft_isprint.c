/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:39:08 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 15:09:32 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function that checks if a character is printable

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

/*
int	main(void)
{
	printf("%d", ft_isprint('1'));
	return (0);
}
*/