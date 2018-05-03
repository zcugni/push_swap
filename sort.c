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

void	    sort_batch(t_lst_inf *lst_inf, int *sorted, int *nb_instruct, int *next_index, int verbose)
{
	int i;
	int dist;
	int do_ra = 0;

	i = 0;

	if (lst_inf->lst_b)
	{
		//avancer le next_index pour qu'il commence avec celui qui est dans b
		/*while (*((int *)(*lst_a)->content) == sorted[*next_index] && *((int *)(*lst_a)->content) != sorted[0])
		{
			(*next_index)++;
			do_ra = 1;
		}*/
		while (lst_inf->lst_b)
		{
			//printf("interne\n");
			//debug(lst_a, lst_b);
			/// a opti
			while (*((int *)lst_inf->lst_a->content) == sorted[*next_index] && *((int *)lst_inf->lst_a->content) != sorted[0])
			{
				rotate(1, &lst_inf->lst_a, "ra\n");
				(*nb_instruct)++;
				(*next_index)++;
				do_ra = 0;
			}
			if (*((int *)lst_inf->lst_a->content) == sorted[*next_index])
			{
				while ((*((int *)lst_inf->lst_a->content) <= sorted[*next_index] && *((int *)lst_inf->lst_a->content) != sorted[0])
				|| (*((int *)lst_inf->lst_a->content) <= sorted[*next_index] && *((int *)lst_inf->lst_b->content) == sorted[1]))
				{
					rotate(1, &lst_inf->lst_a, "ra\n");
					(*nb_instruct)++;
					if (verbose)
						debug(lst_inf);
				}
				//printf("before push\n");
				//debug(lst_a, lst_b);
				push(&lst_inf->lst_a, &lst_inf->lst_b, "pa\n");
				//printf("after push\n");
				//debug(lst_a, lst_b);
				lst_inf->len_b--;
				i++;
				do_ra = 1;
				(*next_index)++;
			}
			else
			{
				//debug(lst_a, lst_b);
				//dans l'immediat c'est plus opti sans mais je devrais pouvoir l'integrer d'une facon ou d'une autre
				/*if (*((int *)(*lst_b)->content) > *((int *)(*lst_b)->next->content))
					swap(*lst_b, "sb\n");
				else
				{*/
					dist = lst_findi(lst_inf->lst_b, &(sorted[*next_index]), sizeof(sorted[*next_index]));
					//if (dist > *len_b / 2 - *len_b / 2 / 2)
					if (dist == lst_inf->len_b)
						rotate(0, &lst_inf->lst_b, "rrb\n");
					else
					{
						if (do_ra)
						{
							rotate_both(1, &lst_inf->lst_a, &lst_inf->lst_b, "rr\n");
							do_ra = 0;
						}
						else
							rotate(1, &lst_inf->lst_b, "rb\n");
					}
				//}
			}
			(*nb_instruct)++;
			if (verbose)
				debug(lst_inf);
		}
		//printf("interne rotate\n");
		//debug(lst_a, lst_b);
		rotate(1, &lst_inf->lst_a, "ra\n");
		(*nb_instruct)++;
		if (verbose)
			debug(lst_inf);
	}
}

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

static int	should_swap(t_list *lst, int *sorted, int nb, int len)
{
	int up;
	int down;
	int i;

	i = 0;
	while (sorted[i] != nb)
		i++;
	if (i == 0)
		down = sorted[0];
	else
		down = sorted[i - 1];
	if (i == len)
		up = sorted[i];
	else
		up = sorted[i + 1];
	if (*((int *)lst->next->content) == down)
		return (1);
	while (lst->next)
		lst = lst->next;
	if (*((int *)lst->content) == up)
		return (0);
	else
		return (1);
}

static void	sort_mini(int ascending, t_list **lst, int *sorted, int len, int *nb_instruct)
{
	t_list *tmp;
	int first;

	first = 1;
	tmp = *lst;
	while (!test_sorted(*lst, ascending))
	{
		if ((*((int *)tmp->content) < *((int *)tmp->next->content) && !ascending) || (*((int *)tmp->content) > *((int *)tmp->next->content) && ascending))
		{
			if (first && should_swap(*lst, sorted, *((int *)tmp->content), len))
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
}

void	    little_list(t_lst_inf *lst_inf, int *sorted, int len, int *nb_instruct)
{
	int half;
	int len_b = 0;

	half = sorted[len / 2];
	if (len > 3)
	{
		while (len_b < len / 2)
		{
			if (*((int *)lst_inf->lst_a->content) < half)
			{
				push(&lst_inf->lst_b, &lst_inf->lst_a, "pb\n");
				len_b++;
			}
			else
				rotate(1, &lst_inf->lst_a, "ra\n");
			(*nb_instruct)++;
		}
		sort_mini(1, &lst_inf->lst_a, sorted, len, nb_instruct);
		sort_mini(0, &lst_inf->lst_b, sorted, len, nb_instruct);
		while (lst_inf->lst_b)
		{
			push(&lst_inf->lst_a, &lst_inf->lst_b, "pa\n");
			(*nb_instruct)++;
		}
	}
	else
		sort_mini(1, &lst_inf->lst_a, sorted, len, nb_instruct);
}
