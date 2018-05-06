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