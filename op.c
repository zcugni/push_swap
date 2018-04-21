/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:58:30 by zcugni            #+#    #+#             */
/*   Updated: 2018/01/26 19:58:31 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_list *lst)
{
	int	tmp;

	if (lst && lst->next)
	{
		tmp = lst->next->nb;
		lst->next->nb = lst->nb;
		lst->nb = tmp;
	}
}

void	push(t_list **lst_x, t_list **lst_y)
{
	t_list *new;

	if (lst_y)
	{
		new = ft_pop(lst_y);
		ft_lstadd(lst_x, new);
	}
}

void	rotate(int up, t_list **lst)
{
	t_list *tmp;
	t_list *first;

	tmp = *lst;
	first = *lst;
	if (up)
	{
		*lst = (*lst)->next;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = first;
		first->next = NULL;
	}
	else
	{
		while (tmp->next->next)
			tmp = tmp->next;
		tmp->next->next = *lst;
		*lst = tmp->next;
		tmp->next = NULL;
	}
}
