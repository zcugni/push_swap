/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:29:38 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/14 14:29:39 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static char	*init(t_sort_status status, t_lst_inf *lst_inf, t_list **lst)
{
	if (!status.asc)
	{
		*lst = lst_inf->lst_b;
		return ("b\n");
	}
	else
	{
		*lst = lst_inf->lst_a;
		return ("a\n");
	}
}

void		sort_mini(t_sort_status status, t_lst_inf *lst_inf,
											t_tab_inf *tab_inf, t_param param)
{
	t_list	*lst;
	char	*letter;
	char	*str;

	letter = init(status, lst_inf, &lst);
	while (!test_sorted(lst, status.asc))
	{
		if (should_swap(get_int_lst(lst), get_int_lst(lst->next), status))
		{
			str = ft_strjoin("s", letter);
			swap(lst_inf, str, param);
		}
		else
		{
			if (should_reverse(status.asc, tab_inf, status, lst))
				str = ft_strjoin("rr", letter);
			else
				str = ft_strjoin("r", letter);
			rotate_lst(lst_inf, str, param);
		}
		free(str);
		lst = lst_inf->lst_a;
		if (!status.asc)
			lst = lst_inf->lst_b;
	}
}
