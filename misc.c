/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 10:34:55 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/06 10:34:56 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_tab(int *arr, int index_1, int index_2)
{
	int tmp;

	tmp = arr[index_1];
	arr[index_1] = arr[index_2];
	arr[index_2] = tmp;
}

int		quicksort(int *arr, int len) //a ameliorer
{
	int i;
	int first_supp;

	i = 1;
	first_supp = 0;
	while (i < len)
	{
		if (arr[i] > arr[0] && first_supp == 0)
			first_supp = i;
		else if (arr[i] < arr[0] && first_supp != 0)
			swap_tab(arr, first_supp++, i);
		else if (arr[i] == arr[0])
			return (0);
		i++;
	}
	if (len > 1)
	{
		if (first_supp == 0)
		{
			swap_tab(arr, first_supp, 1);
			if (!quicksort(arr, len))
				return (0);
		}
		else
		{
			swap_tab(arr, first_supp - 1, 0);
			if (!quicksort(arr, first_supp))
				return (0);
			if (!quicksort(&arr[first_supp], len - first_supp))
				return (0);
		}
	}
	return (1);
}

void	choose_rotate(t_lst_inf *lst_inf, t_tab_inf *tab_inf, int modifier, int *do_ra, int *i_rotate, t_param param)
{
	int i;

	i = lst_findi(lst_inf->lst_b, &(tab_inf->sorted[tab_inf->next_index]), sizeof(tab_inf->sorted[tab_inf->next_index]));
	if (i > lst_inf->len_b / 2 + lst_inf->len_b / 2 / 2 + modifier)
		rotate(0, lst_inf, "rrb\n", param);
	else
	{
		if (*do_ra)
		{
			rotate(1, lst_inf, "rr\n", param);
			*do_ra = 0;
			if (i_rotate)
				(*i_rotate)++;
		}
		else
			rotate(1, lst_inf, "rb\n", param);
	}
}

int		test_sorted(t_list *lst, int ascending)
{
	t_list *tmp;

	tmp = lst;
	while (tmp->next)
	{
		if (*((int *)tmp->content) > *((int *)tmp->next->content) && ascending)
			return (0);
		else if (*((int *)tmp->content) < *((int *)tmp->next->content)
			&& !ascending)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int		is_int(char *str)
{
	int			i;
	long long	nb;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	nb = ft_atoi(str);
	if (nb >= -2147483648 && nb <= 2147483647)
		return (1);
	else
		return (0);
}
