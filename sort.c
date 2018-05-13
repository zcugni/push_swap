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

static void	choose_op(t_lst_inf *lst_inf, t_tab_inf *tab_inf,
										t_split_status status, t_param param)
{
	if (get_int(lst_inf, 'b') == get_desired(tab_inf))
	{
		while ((get_int(lst_inf, 'a') < get_desired(tab_inf) &&
								get_int(lst_inf, 'a') != tab_inf->sorted[0]) ||
								((get_int(lst_inf, 'a') == tab_inf->sorted[0] &&
								get_desired(tab_inf) == tab_inf->sorted[1])))
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
		while ((get_int(lst_inf, 'a') == get_desired(tab_inf) &&
				get_int(lst_inf, 'a') != tab_inf->sorted[0]) ||
				((get_int(lst_inf, 'a') == tab_inf->sorted[0] &&
				get_desired(tab_inf) == tab_inf->sorted[1])))
		{
			tab_inf->next_index++;
			rotate(lst_inf, "ra\n", param);
		}
		while (lst_inf->lst_b)
			choose_op(lst_inf, tab_inf, status, param);
		rotate(lst_inf, "ra\n", param);
	}
}

static int	get_next(int ascending, int nb, t_tab_inf *tab_inf)
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

static int	get_i_unsorted(t_list *lst, int asc)
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

static int	should_swap(int current_nb, int next_nb, t_sort_status status)
{
	if (status.asc)
	{
		if (current_nb > next_nb &&
			!(current_nb == status.p_max_val && next_nb == status.p_min_val))
			return (1);
		else
			return (0);
	}
	else
	{
		if (current_nb < next_nb &&
			!(current_nb == status.p_min_val && next_nb == status.p_max_val))
			return (1);
		else
			return (0);
	}
}

static int	should_reverse(int asc, t_tab_inf *tab_inf, t_sort_status status,
																t_list *lst)
{
	int		len;
	t_list	*last;
	int		last_nb;
	int		current_nb;

	current_nb = get_int_lst(lst);
	last = lst;
	while (last->next)
		last = last->next;
	len = tab_inf->sorted_len / 2;
	if (asc)
		len += tab_inf->sorted_len % 2;
	last_nb = get_int_lst(last);
	if (last_nb == get_next(asc, current_nb, tab_inf))
		return (1);
	if (get_i_unsorted(lst, asc) >= len / 2 && !(last_nb == status.p_max_val &&
												current_nb == status.p_min_val))
		return (1);
	if (lst->next && lst->next->next &&
						get_int_lst(lst->next) == status.p_max_val &&
						get_int_lst(lst->next->next) == status.p_min_val &&
						current_nb != tab_inf->sorted[status.p_max_i - 1])
		return (1);
	return (0);
}

void	sort_mini_v2(t_sort_status status, t_lst_inf *lst_inf,
											t_tab_inf *tab_inf, t_param param)
{
	t_list	*lst;
	char	*letter;

	status.p_min_val = tab_inf->sorted[status.p_min_i];
	status.p_max_val = tab_inf->sorted[status.p_max_i];
	lst = lst_inf->lst_a;
	letter = "a\n";
	if (!status.asc)
		lst = lst_inf->lst_b;
	if (!status.asc)
		letter = "b\n";
	while (!test_sorted(lst, status.asc))
	{
		if (should_swap(get_int_lst(lst), get_int_lst(lst->next), status))
			swap(lst_inf, ft_strjoin("s", letter), param);
		else
		{
			if (should_reverse(status.asc, tab_inf, status, lst))
				rotate(lst_inf, ft_strjoin("rr", letter), param);
			else
				rotate(lst_inf, ft_strjoin("r", letter), param);
		}
		lst = lst_inf->lst_a;
		if (!status.asc)
			lst = lst_inf->lst_b;
	}
}
