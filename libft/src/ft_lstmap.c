/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:19:48 by wchoe             #+#    #+#             */
/*   Updated: 2024/11/04 17:25:50 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*current_node;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = ft_lstnew(NULL);
	if (!new_lst)
		return (NULL);
	new_lst->content = f(lst->content);
	lst = lst->next;
	current_node = new_lst;
	while (lst)
	{
		new_node = ft_lstnew(NULL);
		if (!new_node)
			return (ft_lstclear(&new_lst, del), NULL);
		new_node->content = f(lst->content);
		current_node->next = new_node;
		lst = lst->next;
		current_node = new_node;
	}
	return (new_lst);
}
