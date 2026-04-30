/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:33:31 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/07 14:31:50 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Iterate the list ‘lst’ and apply the function ‘f’
// on the content of each node.

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->next;
	}
}

// void	ft_plus(void *str)
// {
// 	char	*s;
// 	int		i;

// 	i = 0;
// 	s = (char *)str;
// 	while(s[i])
// 	{
// 		s[i]++;
// 		i++;
// 	}
// }

// int main(void)
// {
//     t_list *list = ft_lstnew(ft_strdup("AAA"));
// 	t_list *p;
// 	ft_lstadd_front(&list, ft_lstnew(ft_strdup("BBB")));
// 	ft_lstadd_front(&list, ft_lstnew(ft_strdup("CCC")));
//     ft_lstiter(list, ft_plus);
// 	p = list;
// 	while (p != NULL)
// 	{
// 		ft_putstr_fd((char *)p->content, 1);
// 		ft_putchar_fd('\n', 1);
// 		p = p->next;
// 	}
// 	ft_lstclear(&list, free);
//     return (0);
// }