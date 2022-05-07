/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:44:13 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 17:44:14 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*start;
	t_list	*temp;

	if (!lst)
		return ;
	start = *lst;
	temp = NULL;
	while (start)
	{
		temp = start;
		start = start->next;
		del(temp->content);
		free(temp);
	}
	*lst = NULL;
}
