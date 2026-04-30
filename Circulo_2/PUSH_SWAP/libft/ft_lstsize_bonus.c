/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:29:21 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/07 15:55:03 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Counts the number of nodes in a list.

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*temp;

	count = 0;
	temp = lst;
	if (!lst)
		return (0);
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}

// int	main(void)
// {
// 	t_list *lista;
// 	t_list *a;
// 	t_list *b;
// 	t_list *c;
// 	t_list *d;

// 	lista = ft_lstnew("Comienzo");
// 	a = ft_lstnew("a");
// 	b = ft_lstnew("b");
// 	c = ft_lstnew("c");
// 	d = ft_lstnew("d");

// 	ft_lstadd_front(&d, c);
// 	ft_lstadd_front(&c, b);
// 	ft_lstadd_front(&b, a);
// 	ft_lstadd_front(&a, lista);

// 	printf("%d",ft_lstsize(lista));

// return(0);
// }