/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:06:01 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 15:17:03 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function that compares only the first (at most) n bytes of s1 and s2.

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	x;

	x = 0;
	while (x < n)
	{
		if ((unsigned char)s1[x] != (unsigned char)s2[x])
			return ((unsigned char)s1[x] - (unsigned char)s2[x]);
		if (s1[x] == '\0' || s2[x] == '\0')
			break ;
		x++;
	}
	return (0);
}
/*
int	main (void)
{
	char s1[50] = "test\200";
	char s2[50] = "test\0";

	printf("%d\n",ft_strncmp(s1, s2, 6));
	printf("%d",strncmp(s1, s2, 6));
	return (0);
}
*/
