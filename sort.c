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

void	sort_batch(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_param param)
{
	int do_ra;

	do_ra = 0;
	if (lst_inf->lst_b)
	{
		while (get_int(lst_inf, 'a') == get_desired(tab_inf) && get_int(lst_inf, 'a') != tab_inf->sorted[0])
		{
			tab_inf->next_index++;
			rotate(1, lst_inf, "ra\n", param);
		}
		while (lst_inf->lst_b)
		{
			if (get_int(lst_inf, 'b') == get_desired(tab_inf))
			{
				while (get_int(lst_inf, 'a') < get_desired(tab_inf) && get_int(lst_inf, 'a') != tab_inf->sorted[0])
					rotate(1, lst_inf, "ra\n", param);
				push(lst_inf, "pa\n", param);
				do_ra = 1;
				tab_inf->next_index++;
			}
			else
				choose_rotate(lst_inf, tab_inf, 1, &do_ra, NULL, param);
		}
		rotate(1, lst_inf, "ra\n", param);
	}
}
