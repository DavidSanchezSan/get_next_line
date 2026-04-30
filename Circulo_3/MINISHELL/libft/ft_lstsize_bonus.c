/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:30:02 by egarcia2          #+#    #+#             */
/*   Updated: 2025/02/10 15:34:17 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/// @brief Counts the number of nodes in a list.
/// @param lst the beginning of the list.
/// @return The size of the list (number of element in the list).
int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
int	main(void)
{
	t_list	*first;
	t_list	*second;
	t_list	*third;
	int		i;

	first = ft_lstnew("Nodo 1");
	second = ft_lstnew("Nodo 2");
	third = ft_lstnew("Nodo 3");
	first->next = second;
	second->next = third;
	third->next = NULL;
	i = ft_lstsize(first);
	printf("Result: %d\n", i);
	free(first);
	free(second);
	free(third);
	return (0);
}
*/