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

void	choose_rotate(t_lst_inf *lst_inf, t_tab_inf *tab_inf,
										t_split_status *status, t_param param)
{
	int i;

	i = lst_findi(lst_inf->lst_b, &(tab_inf->sorted[tab_inf->next_index]),
		sizeof(tab_inf->sorted[tab_inf->next_index]));
	if (i > lst_inf->len_b / 2 + lst_inf->len_b / 2 / 2 + status->modifier)
		rotate_lst(lst_inf, "rrb\n", param);
	else
	{
		if (status->do_ra)
		{
			rotate_lst(lst_inf, "rr\n", param);
			status->do_ra = 0;
			if (status->i_rotated)
				(status->i_rotated)++;
		}
		else
			rotate_lst(lst_inf, "rb\n", param);
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

	if (str[0] != '-' && !ft_isdigit(str[0]))
		return (0);
	i = 1;
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
