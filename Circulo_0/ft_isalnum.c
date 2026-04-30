/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:19:15 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 15:09:20 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function that checks if a character is alphanumeric

int	ft_isalnum(int c)
{
	return (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) || (c >= 48
			&& c <= 57));
}
/*
int	main(void)
{
	printf("%d", ft_isalnum('A'));
	return (0);
}
*/