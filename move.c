/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 22:35:25 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/03 22:35:26 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	send_in_a(t_split_status status, t_lst_inf *lst_inf,
	t_tab_inf *tab_inf, t_param param)
{
	while (status.i_sent < status.nb_to_send)
		if (get_int(lst_inf, 'b') >= tab_inf->sorted[status.pivot_min] ||
							get_int(lst_inf, 'b') == get_desired(tab_inf))
		{
			if (status.do_ra)
			{
				rotate_lst(lst_inf, "ra\n", param);
				status.do_ra = 0;
				status.i_rotated++;
			}
			push(lst_inf, "pa\n", param);
			if (get_int(lst_inf, 'a') == get_desired(tab_inf))
			{
				if (get_int(lst_inf, 'a') < tab_inf->sorted[status.pivot_min])
					status.i_sent--;
				if (status.i_rotated < status.max_to_rotate)
				{
					tab_inf->next_index++;
					status.do_ra = 1;
				}
			}
			status.i_sent++;
		}
		else
			choose_rotate(lst_inf, tab_inf, &status, param);
}

void		split_b(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_param param)
{
	t_split_status	status;

	status.i_sent = 0;
	status.i_rotated = 0;
	status.nb_to_send = 0;
	status.nb_to_send = lst_inf->len_b / 2;
	status.max_to_rotate = lst_inf->len_b - status.nb_to_send;
	status.pivot_min = lst_inf->len_b / 2 + lst_inf->len_b % 2
		+ tab_inf->next_index;
	status.do_ra = 0;
	status.modifier = 3;
	send_in_a(status, lst_inf, tab_inf, param);
	while (lst_inf->lst_b && get_int(lst_inf, 'b') == get_desired(tab_inf))
	{
		push(lst_inf, "pa\n", param);
		rotate_lst(lst_inf, "ra\n", param);
		tab_inf->next_index++;
	}
}

void		send_half(t_lst_inf *lst_inf, t_tab_inf *tab_inf,
	t_split_status status, t_param param)
{
	int i;
	int pivot_max;

	i = 0;
	pivot_max = status.pivot_min + status.nb_to_send - 1;
	while (i < status.nb_to_send)
	{
		if (get_int(lst_inf, 'a') == get_desired(tab_inf) &&
			tab_inf->next_index != 0)
		{
			rotate_lst(lst_inf, "ra\n", param);
			tab_inf->next_index++;
			i++;
		}
		else if (get_int(lst_inf, 'a') >= tab_inf->sorted[status.pivot_min] &&
			get_int(lst_inf, 'a') <= tab_inf->sorted[pivot_max])
		{
			push(lst_inf, "pb\n", param);
			i++;
		}
		else
			rotate_lst(lst_inf, "ra\n", param);
	}
}

void		send_in_b(t_lst_inf *lst_inf, int diff, t_tab_inf *tab_inf,
	t_param param)
{
	int i;

	i = 0;
	while (i < diff)
	{
		if (get_int(lst_inf, 'a') <= get_desired(tab_inf))
		{
			rotate_lst(lst_inf, "ra\n", param);
			tab_inf->next_index++;
		}
		else if (get_int_lst(lst_inf->lst_a->next) == get_desired(tab_inf) &&
			get_int(lst_inf, 'a') == tab_inf->sorted[tab_inf->next_index + 1])
		{
			swap(lst_inf, "sa\n", param);
			i--;
		}
		else
			push(lst_inf, "pb\n", param);
		i++;
	}
}
