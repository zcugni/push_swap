/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 10:30:26 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/06 10:30:29 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_int(t_lst_inf *lst_inf, char lst_letter)
{
	if (lst_letter == 'a')
		return (*((int *)lst_inf->lst_a->content));
	else
		return (*((int *)lst_inf->lst_b->content));
}

int	get_int_lst(t_list *lst)
{
	return (*((int *)lst->content));
}

int	get_desired(t_tab_inf *tab_inf)
{
	return (tab_inf->sorted[tab_inf->next_index]);
}

int	get_next(int ascending, int nb, t_tab_inf *tab_inf)
{
	int i;

	i = 0;
	while (i < tab_inf->sorted_len)
	{
		if (nb == tab_inf->sorted[i])
		{
			if (ascending)
			{
				if (i == tab_inf->sorted_len - 1)
					return (tab_inf->sorted[i]);
				else
					return (tab_inf->sorted[i + 1]);
			}
			else
			{
				if (i == 0)
					return (tab_inf->sorted[0]);
				else
					return (tab_inf->sorted[i - 1]);
			}
		}
		i++;
	}
	return (0);
}

int	get_i_unsorted(t_list *lst, int asc)
{
	int		i;

	i = 0;
	while (lst->next)
	{
		if ((get_int_lst(lst) > get_int_lst(lst->next) && asc) ||
				(get_int_lst(lst) < get_int_lst(lst->next) && !asc))
			return (i);
		i++;
		lst = lst->next;
	}
	return (-1);
}
