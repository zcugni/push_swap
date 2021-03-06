/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:01:16 by zcugni            #+#    #+#             */
/*   Updated: 2018/03/21 16:01:19 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	qs_lst(t_lst_inf *lst_inf, t_tab_inf *tab_inf,
	t_list **lst_halves, t_param param)
{
	int half;

	if (lst_inf->len_b > 9)
	{
		half = lst_inf->len_b / 2;
		ft_lstadd(lst_halves, ft_lstnew(&half, sizeof(half)));
		split_b(lst_inf, tab_inf, param);
		qs_lst(lst_inf, tab_inf, lst_halves, param);
		send_in_b(lst_inf, ft_pop_value(lst_halves), tab_inf, param);
		qs_lst(lst_inf, tab_inf, lst_halves, param);
	}
	else
		sort_batch(lst_inf, tab_inf, param);
}

static void	deal_little(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_param param)
{
	t_sort_status	sort_stat;

	sort_stat.p_min_i = tab_inf->sorted_len / 2;
	sort_stat.p_max_i = tab_inf->sorted_len - 1;
	sort_stat.p_min_val = tab_inf->sorted[sort_stat.p_min_i];
	sort_stat.p_max_val = tab_inf->sorted[sort_stat.p_max_i];
	sort_stat.asc = 1;
	sort_mini(sort_stat, lst_inf, tab_inf, param);
	sort_stat.p_min_i = 0;
	sort_stat.p_max_i = tab_inf->sorted_len / 2 - 1;
	sort_stat.p_min_val = tab_inf->sorted[sort_stat.p_min_i];
	sort_stat.p_max_val = tab_inf->sorted[sort_stat.p_max_i];
	sort_stat.asc = 0;
	sort_mini(sort_stat, lst_inf, tab_inf, param);
	while (lst_inf->lst_b)
		push(lst_inf, "pa\n", param);
}

static void	deal_default(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_param param)
{
	t_list			*lst_halves;
	t_split_status	split_stat;

	lst_halves = NULL;
	qs_lst(lst_inf, tab_inf, &lst_halves, param);
	split_stat.pivot_min = tab_inf->sorted_len / 2;
	split_stat.nb_to_send = tab_inf->sorted_len / 2 + tab_inf->sorted_len % 2;
	send_half(lst_inf, tab_inf, split_stat, param);
	qs_lst(lst_inf, tab_inf, &lst_halves, param);
}

static void	get_instruct(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_param param)
{
	t_split_status	split_stat;
	t_sort_status	sort_stat;

	if (tab_inf->sorted_len > 3)
	{
		split_stat.nb_to_send = tab_inf->sorted_len / 2;
		split_stat.pivot_min = 0;
		send_half(lst_inf, tab_inf, split_stat, param);
		if (tab_inf->sorted_len > 9)
			deal_default(lst_inf, tab_inf, param);
		else
			deal_little(lst_inf, tab_inf, param);
	}
	else
	{
		sort_stat.p_min_i = 0;
		sort_stat.p_max_i = tab_inf->sorted_len;
		sort_stat.p_min_val = tab_inf->sorted[sort_stat.p_min_i];
		sort_stat.p_max_val = tab_inf->sorted[sort_stat.p_max_i];
		sort_mini(sort_stat, lst_inf, tab_inf, param);
	}
}

int			main(int argc, char **argv)
{
	t_param		param;
	t_lst_inf	lst_inf;
	t_tab_inf	tab_inf;
	int			first_nb_i;

	lst_inf.lst_b = NULL;
	lst_inf.lst_a = NULL;
	if (argc == 1)
		return (0);
	if (!init_param(argc, argv, &param, &first_nb_i))
		return (display_error());
	if (valid_input(first_nb_i, argv, &tab_inf, &(lst_inf.lst_a)))
	{
		if (!test_sorted(lst_inf.lst_a, 1))
		{
			tab_inf.next_index = 0;
			lst_inf.len_b = 0;
			get_instruct(&lst_inf, &tab_inf, param);
		}
	}
	else
		return (display_error());
	return (0);
}
