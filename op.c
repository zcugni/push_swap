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

void	swap(t_list *lst, char *to_print)
{
	int	tmp;

	if (lst && lst->next)
	{
		tmp = *(int *)lst->next->content;
		*((int *)lst->next->content) = *((int *)lst->content);
		*((int *)lst->content) = tmp;
	}
	//printf("%s", to_print);
	to_print = "n"; //je suis obligee de faire un truc avec to_print pour le compilateur
}

void	push(t_list **lst_receiver, t_list **lst_giver, char *to_print)
{
	t_list *new;

	if (lst_giver)
	{
		new = ft_pop(lst_giver);
		ft_lstadd(lst_receiver, new);
	}
	//printf("%s", to_print);
	to_print = "n"; //je suis obligee de faire un truc avec to_print pour le compilateur
}

void	rotate(int up, t_list **lst, char *to_print)
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
	//if (ft_strcmp(to_print, "no"))
		//printf("%s", to_print);
	to_print = "n"; //je suis obligee de faire un truc avec to_print pour le compilateur
}

void	rotate_both(int up, t_list **lst_a, t_list **lst_b, char *to_print)
{
	rotate(up, lst_a, "no");
	rotate(up, lst_b, "no");
	//printf("%s", to_print);
	to_print = "n"; //je suis obligee de faire un truc avec to_print pour le compilateur
}
