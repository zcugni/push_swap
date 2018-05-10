/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 11:37:11 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/06 11:37:13 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	choose_op(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_split_status status,
	t_param param)
{
	if (get_int(lst_inf, 'b') == get_desired(tab_inf))
	{
		while (get_int(lst_inf, 'a') < get_desired(tab_inf) &&
		get_int(lst_inf, 'a') != tab_inf->sorted[0])
			rotate(lst_inf, "ra\n", param);
		push(lst_inf, "pa\n", param);
		status.do_ra = 1;
		tab_inf->next_index++;
	}
	else
		choose_rotate(lst_inf, tab_inf, 1, &status, param);
}

void	sort_batch(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_param param)
{
	t_split_status	status;

	status.do_ra = 0;
	status.i_rotated = 0;
	if (lst_inf->lst_b)
	{
		while (get_int(lst_inf, 'a') == get_desired(tab_inf) &&
		get_int(lst_inf, 'a') != tab_inf->sorted[0])
		{
			tab_inf->next_index++;
			rotate(lst_inf, "ra\n", param);
		}
		while (lst_inf->lst_b)
			choose_op(lst_inf, tab_inf, status, param);
		rotate(lst_inf, "ra\n", param);
	}
}
