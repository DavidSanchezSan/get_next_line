/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:03:25 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/05 19:54:55 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
It takes as parameter a node ‘lst’ and frees the memory of the content using
the function ‘del’ given as parameter, in addition to freeing the node. The
memory of the ‘next’ must not be freed.
*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del && lst->content)
	{
		del(lst->content);
		free(lst);
		lst = NULL;
	}
}

// void	nada(void *ptr)
// {
// 	(void)ptr;
// }

// int	main(void)
// {
// 	char *a;

// 	a = "abc";
// 	t_list *ejemplo;
// 	ejemplo = ft_lstnew((void *)a);
// 	printf("%s\n",(char *)ejemplo->content);
// 	ft_lstdelone(ejemplo, nada);
// }