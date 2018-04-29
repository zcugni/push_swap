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

int		get_up(int nb, int *sorted)
{
	int i;

	i = 0;
	while (sorted[i] != nb)
		i++;
	return (sorted[i + 1]);
}

int		test_sorted(t_list *lst)
{
	while (lst->next)
	{
		if (*((int *)lst->content) > *((int *)lst->next->content))
			return (0);
		lst = lst->next;
	}
	return (1);
}

void	sort_mini(t_list **lst_a, t_list **lst_b, int *sorted, int len, int *nb_instruct)
{
	//int up;
	int half;
	int len_b = 0;

	half = sorted[len / 2];

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

	debug(lst_a, lst_b);
	printf("\n");
	exit(1);
	/*while (!test_sorted(*lst_a))
	{
		printf("yo?\n");
		if (*((int *)(*lst_a)->content) > *((int *)(*lst_a)->next->content))
		{
			swap(*lst_a, "sa\n");
			(*nb_instruct)++;
		}
		else if (*((int *)(*lst_a)->content) > sorted[len / 2])
		{
			rotate(0, lst_a, "rra\n");
			(*nb_instruct)++;
		}
	}*/

	int nb_index = ft_lstfindi(lst_a, );

	while (*((int *)(*lst_b)->content) != sorted[len / 2 + len % 2])
	{
		if (*((int *)(*lst_a)->content) > *((int *)(*lst_a)->next->content))
		{
			swap(*lst_a, "sa\n");
			(*nb_instruct)++;
		}
		else if (*((int *)(*lst_a)->content) > sorted[len / 2])
		{
			
		}
	}



	if (*((int *)(*lst_b)->content) < *((int *)(*lst_b)->next->content))
	{
		swap(*lst_b, "sb\n");
		(*nb_instruct)++;
	}
		
	while (len_b > 0)
	{
		push(lst_a, lst_b, "pa\n");
		len_b--;
		(*nb_instruct)++;
	}
}
