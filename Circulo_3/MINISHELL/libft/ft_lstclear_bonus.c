/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:30:36 by marvin            #+#    #+#             */
/*   Updated: 2025/02/10 15:56:53 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief  Deletes and free the memory of the element passed as parameter
/// and all the following elements using 'del' and free(3).
/// Finally, the initial pointer must be set to NULL.
/// @param lst pointer address to one element
/// @param del address of the function that can delete the element's content
/// @return none
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}
/*
int	main(void)
{
	t_list	*first;
	t_list	*second;
	t_list	*third;

	first = ft_lstnew("Nodo 1");
	second = ft_lstnew("Nodo 2");
	third = ft_lstnew("Nodo 3");
	first->next = second;
	second->next = third;
	third->next = NULL;
	printf("Result before clear:%s\n", (char *)first->content);
	printf("Result before clear:%s\n", (char *)second->content);
	printf("Result before clear:%s\n", (char *)third->content);
	ft_lstclear(&first, free);
	printf("Result after clear: %s\n", (char *)first->content);
	return (0);
}
*/