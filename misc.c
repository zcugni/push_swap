#include "push_swap.h"


#include <stdio.h>

void	quicksort(int *arr, int len) //a ameliorer
{
	int pivot_index;
	int i;
	int first_supp;
	int tmp;

	//pivot = len / 2;
	pivot_index = 0;
	i = 0;
	first_supp = 0;
	while (i < len)
	{
		if (arr[i] > arr[pivot_index] && first_supp == 0)
			first_supp = i;
		else if (arr[i] < arr[pivot_index] && first_supp != 0)
		{
			tmp = arr[first_supp];
			arr[first_supp] = arr[i];
			arr[i] = tmp;
			first_supp++;
		}
		i++;
	}
	if (len > 1)
	{
		if (first_supp == 0)
		{
			tmp = arr[first_supp];
			arr[first_supp] = arr[1];
			arr[1] = tmp;
			quicksort(arr, len);
		}
		else
		{
			tmp = arr[first_supp - 1];
			arr[first_supp - 1] = arr[pivot_index];
			arr[pivot_index] = tmp;
			quicksort(arr, first_supp);
			quicksort(&arr[first_supp], len - first_supp);
		}
	}
}

void	sort_batch(t_list **lst_a, t_list **lst_b, int *sorted, int *nb_instruct, int *next_index, int *len_b, int verbose)
{
	int i;
	int dist;
	int do_ra = 0;

	i = 0;
	if (*lst_b)
	{
		while (*lst_b)
		{
			if (*((int *)(*lst_b)->content) == sorted[*next_index])
			{
				while ((*((int *)(*lst_a)->content) <= sorted[*next_index] && *((int *)(*lst_a)->content) != sorted[0])
				|| (*((int *)(*lst_a)->content) <= sorted[*next_index] && *((int *)(*lst_b)->content) == sorted[1]))
				{
					rotate(1, lst_a, "ra\n");
					(*nb_instruct)++;
					if (verbose)
						debug(lst_a, lst_b);
				}
				push(lst_a, lst_b, "pa\n");
				(*len_b)--;
				i++;
				do_ra = 1;
				(*next_index)++;
			}
			else
			{
				//dans l'immediat c'est plus opti sans mais je devrais pouvoir l'integrer d'une facon ou d'une autre
				/*if (*((int *)(*lst_b)->content) > *((int *)(*lst_b)->next->content))
					swap(*lst_b, "sb\n");
				else
				{*/
					dist = ft_lstfind_i(*lst_b, sorted[*next_index]);
					if (dist > *len_b / 2 - 1)
						rotate(0, lst_b, "rrb\n");
					else
					{
						if (do_ra)
						{
							rotate_both(1, lst_a, lst_b, "rr\n");
							do_ra = 0;
						}
						else
							rotate(1, lst_b, "rb\n");
					}
				//}
			}
			(*nb_instruct)++;
			if (verbose)
				debug(lst_a, lst_b);
		}
		rotate(1, lst_a, "ra\n");
		(*nb_instruct)++;
		if (verbose)
			debug(lst_a, lst_b);
	}
}

int		test_sorted(t_list *lst, int ascending)
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

int		should_swap(t_list *lst, int *sorted, int nb, int len)
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

void	sort_mini(int ascending, t_list **lst, int *sorted, int len, int *nb_instruct)
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

void	little_list(t_list **lst_a, t_list **lst_b, int *sorted, int len, int *nb_instruct)
{
	int half;
	int len_b = 0;

	half = sorted[len / 2];
	if (len > 3)
	{
		while (len_b < len / 2)
		{
			if (*((int *)(*lst_a)->content) < half)
			{
				push(lst_b, lst_a, "pb\n");
				len_b++;
			}
			else
				rotate(1, lst_a, "ra\n");
			(*nb_instruct)++;
		}
		sort_mini(1, lst_a, sorted, len, nb_instruct);
		sort_mini(0, lst_b, sorted, len, nb_instruct);
		while (*lst_b)
		{
			push(lst_a, lst_b, "pa\n");
			(*nb_instruct)++;
		}
	}
	else
		sort_mini(1, lst_a, sorted, len, nb_instruct);
}
