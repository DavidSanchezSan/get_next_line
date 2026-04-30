/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:07:39 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/07 15:54:32 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Create a new node using mallocc. The member variable ‘content’ is initialised
with the contents of parameter ‘content’. The variable ‘next’ with NULL.
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// int	main(void)
// {
// 	char *a;

// 	a = "   a  ";
// 	t_list *ejemplo;
// 	ejemplo = ft_lstnew((void *)a);
// 	printf("%s",(char *)ejemplo->content);
// }