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

static int	test_sorted(t_list *lst, int ascending)
{
	while (lst->next)
	{
		if (*((int *)lst->content) > *((int *)lst->next->content) && ascending)
			return (0);
		else if (*((int *)lst->content) < *((int *)lst->next->content) && !ascending)
			return (0);
		lst = lst->next;
	}
	return (1);
}

static int	should_swap(t_list *lst, t_tab_inf *tab_inf, int nb)
{
	int up;
	int down;
	int i;

	i = 0;
	while (tab_inf->sorted[i] != nb)
		i++;
	if (i == 0)
		down = tab_inf->sorted[0];
	else
		down = tab_inf->sorted[i - 1];
	if (i == tab_inf->sorted_len)
		up = tab_inf->sorted[i];
	else
		up = tab_inf->sorted[i + 1];
	if (*((int *)lst->next->content) == down)
		return (1);
	while (lst->next)
		lst = lst->next;
	if (*((int *)lst->content) == up)
		return (0);
	else
		return (1);
}

static void	choose_op(int first, int ascending, int need_swap, t_list **lst)
{
	if (first && need_swap)
	{
		if (ascending)
			swap(*lst, "sa\n");
		else
			swap(*lst, "sb\n");
	}
	else
	{
		if (ascending)
			rotate(0, lst, "rra\n");
		else
			rotate(0, lst, "rrb\n");
	}
}

static void	sort_mini(int ascending, t_list **lst, t_tab_inf *tab_inf, int *nb_instruct)
{
	t_list	*tmp;
	int 	first;
	int		need_swap;

	first = 1;
	tmp = *lst;
	while (!test_sorted(*lst, ascending))
		if ((*((int *)tmp->content) < *((int *)tmp->next->content) && !ascending) || (*((int *)tmp->content) > *((int *)tmp->next->content) && ascending))
		{
			need_swap = should_swap(*lst, tab_inf, *((int *)tmp->content));
			choose_op(first, ascending, need_swap, lst);
			(*nb_instruct)++;
			tmp = *lst;
			first = 1;
		}
		else
		{
			first = 0;
			tmp = tmp->next;
		}
}

void	    little_list(t_lst_inf *lst_inf, t_tab_inf *tab_inf, int *nb_instruct)
{
	int half;

	lst_inf->len_b = 0;
	half = tab_inf->sorted[tab_inf->sorted_len / 2];
	if (tab_inf->sorted_len > 3)
	{
		while (lst_inf->len_b < tab_inf->sorted_len / 2)
		{
			if (*((int *)lst_inf->lst_a->content) < half)
				push(lst_inf, "pb\n");
			else
				rotate(1, &lst_inf->lst_a, "ra\n");
			(*nb_instruct)++;
		}
		sort_mini(1, &lst_inf->lst_a, tab_inf, nb_instruct);
		sort_mini(0, &lst_inf->lst_b, tab_inf, nb_instruct);
		while (lst_inf->lst_b)
		{
			push(lst_inf, "pa\n");
			(*nb_instruct)++;
		}
	}
	else
		sort_mini(1, &lst_inf->lst_a, tab_inf, nb_instruct);
}
