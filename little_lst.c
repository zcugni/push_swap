/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 22:35:18 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/03 22:35:19 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*static int	should_swap(t_list *lst, t_tab_inf *tab_inf, int nb)
{
	int up;
	int down;
	int i;

	i = 0;
	while (tab_inf->sorted[i] != nb)
		i++;
	printf("i, nb : %i, %i\n", i, nb);
	
	if (i == 0)
		down = tab_inf->sorted[0];
	else
		down = tab_inf->sorted[i - 1];
	if (i == tab_inf->sorted_len)
		up = tab_inf->sorted[i];
	else
		up = tab_inf->sorted[i + 1];

	printf("up, down, lst : %i, %i, %i\n", up, down, *((int *)lst->content));
	if (*((int *)lst->next->content) == down)
		return (1);
	return (0);
	while (lst->next)
		lst = lst->next;
	printf("lst : %i\n", *((int *)lst->content));
	exit(1);
	if (*((int *)lst->content) == up)
		return (0);
	else
		return (1);
}*/

static void	choose_op(int asc, int need_swap, t_lst_inf *lst_inf, t_param param)
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

static void	sort_mini(int ascending, t_lst_inf *lst_inf,
	t_param param)
{
	t_list	*lst;

	lst = lst_inf->lst_a;
	if (!ascending)
		lst = lst_inf->lst_b;
	while (!test_sorted(lst, ascending))
	{
		if (test_diff(lst, ascending))
			choose_op(ascending, 1, lst_inf, param);
		else
			choose_op(ascending, 0, lst_inf, param);
		lst = lst_inf->lst_a;
		if (!ascending)
			lst = lst_inf->lst_b;
	}
}

void		little_list(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_param param)
{
	int half;

	lst_inf->len_b = 0;
	half = tab_inf->sorted[tab_inf->sorted_len / 2];
	if (tab_inf->sorted_len > 3)
	{
		while (lst_inf->len_b < tab_inf->sorted_len / 2)
		{
			if (get_int(lst_inf, 'a') < half)
				push(lst_inf, "pb\n", param);
			else
				rotate(lst_inf, "ra\n", param);
		}
		exit(1);
		sort_mini(1, lst_inf, param);
		sort_mini(0, lst_inf, param);
		while (lst_inf->lst_b)
			push(lst_inf, "pa\n", param);
	}
	else
		sort_mini(1, lst_inf, param);
}
