/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:24:06 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/05 19:34:54 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Adds the new node to the end of the 'lst' list.

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

// int	main(void)
// {
// 	t_list *lista;
// 	t_list *a;
// 	t_list *b;
// 	t_list *c;
// 	t_list *d;

// 	lista = ft_lstnew("Final");
// 	a = ft_lstnew("a");
// 	b = ft_lstnew("b");
// 	c = ft_lstnew("c");
// 	d = ft_lstnew("d");

// 	ft_lstadd_front(&c, b);
// 	ft_lstadd_front(&b, a);
// 	ft_lstadd_front(&a, lista);

// 	t_list *last = ft_lstlast(lista);
// 	printf("%s\n", (char *)last->content);
// 	ft_lstadd_back(&lista, d);
// 	last = ft_lstlast(lista);
// 	printf("%s", (char *)last->content);
// 	return (0);
// }