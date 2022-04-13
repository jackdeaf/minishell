/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:00:35 by yang              #+#    #+#             */
/*   Updated: 2022/04/13 13:15:29 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_pos(t_list **lst, t_list *new, int pos)
{
	t_list	*temp;
	int		i;
	
	i = 0;
	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		if (pos == 1)
			ft_lstadd_front(lst, new);
		else
		{
			while (++i < pos - 1)
				temp = temp->next;
			new->next = temp->next;
			temp->next = new;
		}
	}
}