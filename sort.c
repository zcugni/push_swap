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

static void	choose_op_big(int asc, int need_swap, t_lst_inf *lst_inf, t_param param)
{
	if (need_swap)
	{
		if (asc)
			swap(lst_inf, "sa\n", param);
		else
			swap(lst_inf, "sb\n", param);
	}
	else
	{
		if (asc)
			rotate(lst_inf, "rra\n", param);
		else
			rotate(lst_inf, "rrb\n", param);
	}
}

static int	test_diff(t_list *lst, int ascending)
{
	int nb;
	int next_nb;

	nb = *((int *)lst->content);
	next_nb = *((int *)lst->next->content);
	if ((nb < next_nb && !ascending) || (nb > next_nb && ascending))
		return (1);
	else
		return (0);
}

void	sort_mini(int ascending, t_lst_inf *lst_inf,
	t_param param)
{
	t_list	*lst;

	lst = lst_inf->lst_a;
	if (!ascending)
		lst = lst_inf->lst_b;
	while (!test_sorted(lst, ascending))
	{
		if (test_diff(lst, ascending))
			choose_op_big(ascending, 1, lst_inf, param);
		else
			choose_op_big(ascending, 0, lst_inf, param);
		lst = lst_inf->lst_a;
		if (!ascending)
			lst = lst_inf->lst_b;
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

/*static int	get_prev(int ascending, int nb, t_tab_inf *tab_inf)
{
	int i;

	i = 0;
	while (i < tab_inf->sorted_len)
	{
		if (nb == tab_inf->sorted[i])
		{
			if (ascending)
			{
				if (i == 0)
					return (tab_inf->sorted[1]);
				else
					return (tab_inf->sorted[i - 1]);
			}
			else
			{
				if (i == tab_inf->sorted_len - 1)
					return (tab_inf->sorted[0]);
				else
					return (tab_inf->sorted[i + 1]);
			}
		}
		i++;
	}
	return (0);
}*/

static int	get_i_unsorted(t_lst_inf *lst_inf, char letter, int ascending)
{
	t_list	*lst;
	int		i;

	lst = lst_inf->lst_a;
	if (letter == 'b')
		lst = lst_inf->lst_b;
	i = 0;
	while (lst->next)
	{
		if (test_diff(lst, ascending))
			return (i);
		i++;
		lst = lst->next;
	}
	return (-1);
}

static int	is_min_border(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_list *lst, int pivot_min, int pivot_max, char letter, int asc)
{
	if (asc)
	{
		if (get_int(lst_inf, letter) == tab_inf->sorted[pivot_max] && get_int_lst(lst->next) == tab_inf->sorted[pivot_min])
			return (1);
		else
			return (0);
	}
	else
	{
		if (get_int(lst_inf, letter) == tab_inf->sorted[pivot_min] && get_int_lst(lst->next) == tab_inf->sorted[pivot_max])
			return (1);
		else
			return (0);
	}
}

int y = 0;
void	sort_mini_v2(int ascending, int pivot_min, int pivot_max, t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_param param)
{
	t_list	*lst;
	char	*letter;
	t_list	*tmp;
	int		next;
	//int		prev;
	int		len;
	
	lst = lst_inf->lst_a;
	letter = "a\n";
	if (!ascending)
	{
		lst = lst_inf->lst_b;
		letter = "b\n";
	}
	while (!test_sorted(lst, ascending))
	{
		y++;
		if (y >= 10)
			exit(1);
		tmp = lst;
		while (tmp->next)
			tmp = tmp->next;
		next = get_next(ascending, get_int(lst_inf, letter[0]), tab_inf);
		//prev = get_prev(ascending, get_int(lst_inf, letter[0]), tab_inf);
		//de base j'avais mis cette condition mais elle fait aucun sens : get_int(lst_inf, 'a') != tab_inf->sorted[0] && get_int_lst(lst->next) != tab_inf->sorted[1]
		printf("lst, lst->next, tmp, up, sorted[max], sorted[min] : %i, %i, %i, %i, %i, %i\n", get_int(lst_inf, letter[0]), get_int_lst(lst->next), get_int_lst(tmp), next, tab_inf->sorted[pivot_max], tab_inf->sorted[pivot_min]);
		printf("test_diff, is_min_border : %i, %i\n", test_diff(lst, ascending), is_min_border(lst_inf, tab_inf, lst, pivot_min, pivot_max, letter[0], ascending));
		if (test_diff(lst, ascending) && !is_min_border(lst_inf, tab_inf, lst, pivot_min, pivot_max, letter[0], ascending))
			swap(lst_inf, ft_strjoin("s", letter), param);
		else if (get_int_lst(tmp) == next)
			rotate(lst_inf, ft_strjoin("rr", letter), param);
		else
		{
			if (ascending)
				len = tab_inf->sorted_len / 2 + tab_inf->sorted_len % 2;
			else
				len = tab_inf->sorted_len / 2;
			printf("i_unsorted, len : %i, %i\n", get_i_unsorted(lst_inf, letter[0], ascending), len / 2);
			if ((get_i_unsorted(lst_inf, letter[0], ascending) >= len / 2 && get_int_lst(tmp) != tab_inf->sorted[pivot_max] && get_int_lst(lst) != tab_inf->sorted[pivot_min])
				|| (lst->next && lst->next->next && get_int_lst(lst->next) == tab_inf->sorted[pivot_max] && get_int_lst(lst->next->next) == tab_inf->sorted[pivot_min]))
				rotate(lst_inf, ft_strjoin("rr", letter), param);
			else
				rotate(lst_inf, ft_strjoin("r", letter), param);
		}
			
		lst = lst_inf->lst_a;
		if (!ascending)
			lst = lst_inf->lst_b;
	}
}

/*
		printf("lst, lst->next, tmp, next, sorted[max], sorted[min] : %i, %i, %i, %i, %i, %i\n", get_int(lst_inf, letter[0]), get_int_lst(lst->next), get_int_lst(tmp), next, tab_inf->sorted[pivot_max], tab_inf->sorted[pivot_min]);
		if (test_diff(lst, ascending) && !(get_int(lst_inf, letter[0]) == tab_inf->sorted[pivot_max] && get_int_lst(lst->next) == tab_inf->sorted[pivot_min]))
			swap(lst_inf, ft_strjoin("s", letter), param);
		else if (get_int_lst(tmp) == next || (get_int_lst(tmp) == prev && get_int_lst(lst->next) == next)) //de base je faisais le precedent que pour les premiers, la je fais pour tout, a voir
			rotate(lst_inf, ft_strjoin("rr", letter), param);
		else
			rotate(lst_inf, ft_strjoin("r", letter), param);
*/