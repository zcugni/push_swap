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

t_list	*ft_lstnew(int nb)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list *));
	if (new == NULL)
		return (NULL);
	new->nb = nb;
	new->next = NULL;
	return (new);
}

void	ft_lstappend(t_list **alst, t_list *new)
{
	t_list *tmp;

	if (new)
	{
		if (*alst)
		{
			tmp = *alst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		else
			*alst = new;
	}
}

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (new)
	{
		if (*alst)
			new->next = *alst;
		*alst = new;
	}
}

t_list	*ft_pop(t_list **lst)
{
	t_list	*new;
	t_list	*tmp;

	new = ft_lstnew((*lst)->nb);
	tmp = *lst;
	*lst = (*lst)->next;
	free(tmp);
	return (new);
}

int		ft_lstfind_i(t_list *lst, int nb)
{
	t_list *tmp;
	int		i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		if (tmp->nb == nb)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (-1);
}

t_list	*ft_lstcpy(t_list *ori)
{
	t_list *new;
	t_list *first_elem;
	t_list *current;

	if (!ori)
		return (NULL);
	new = ft_lstnew(ori->nb);
	if (!new)
		return (NULL);
	first_elem = new;
	current = ori->next;
	while (current)
	{
		new->next = ft_lstnew(current->nb);
		if (!new->next)
			return (NULL);
		new = new->next;
		current = current->next;
	}
	return (first_elem);
}

int    lst_length(t_list *lst)
{
    t_list *tmp;
    int i;

    i = 0;
    tmp = lst;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    return (i);
}