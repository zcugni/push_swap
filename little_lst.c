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



