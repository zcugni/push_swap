/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:54:44 by zcugni            #+#    #+#             */
/*   Updated: 2018/01/26 19:54:45 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*ft_pop(t_list **lst)
{
	t_list	*new;
	t_list	*tmp;

	new = ft_lstnew((*lst)->content, (*lst)->content_size);
	tmp = *lst;
	*lst = (*lst)->next;
	free(tmp);
	return (new);
}

int		ft_pop_value(t_list **lst)
{
	t_list	*tmp;
	int		value;

	value = *((int *)(*lst)->content);
	tmp = *lst;
	*lst = (*lst)->next;
	free(tmp);
	return (value);
}

int		ft_lstfind_i(t_list *lst, int nb)
{
	t_list *tmp;
	int		i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		if (*((int *)tmp->content) == nb)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (-1);
}
