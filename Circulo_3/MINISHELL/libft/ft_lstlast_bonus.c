/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:24:59 by egarcia2          #+#    #+#             */
/*   Updated: 2025/02/10 15:35:09 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief  Returns the last element of the list.
/// @param lst the start of the list.
/// @return last element of the list.
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
/*
int	main(void)
{
	t_list	*first;
	t_list	*second;
	t_list	*third;
	t_list	*last;

	first = ft_lstnew("Nodo 1");
	second = ft_lstnew("Nodo 2");
	third = ft_lstnew("Nodo 3");
	first->next = second;
	second->next = third;
	third->next = NULL;
	last = ft_lstlast(first);
	printf("Result: %s\n", (char *)last->content);
	free(first);
	free(second);
	free(third);
	return (0);
}
*/