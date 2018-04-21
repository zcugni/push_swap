// Je supprimerais/modifierais un bon nombre de ces fonctions quand je factoriserais la principale, mais en attendant je les mets ici

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

void	sort_batch(t_list **lst_a, t_list **lst_b, int *sorted, int *nb_instruct, int *next_index, int *len_b, int verbose, int *nb_ra, int *nb_sb, int *nb_rrb, int *nb_pa_2, int *nb_rr, int *nb_rb)
{
	int i;
	int dist;

	i = 0;
	while (*lst_b)
	{
		while ((*lst_a)->nb == sorted[*next_index])
		{
			rotate(1, lst_a);
			//printf("ra ");
			(*nb_instruct)++;
			(*nb_ra)++;
			(*next_index)++;
			if (verbose)
				debug(lst_a, lst_b, 0);
		}
		if ((*lst_b)->nb == sorted[*next_index])
		{
            push(lst_a, lst_b);
			(*len_b)--;
			(*nb_pa_2)++;
			//ft_putstr("pa ");
            i++;
        }
        else
        {
			if ((*lst_b)->nb > (*lst_b)->next->nb)
			{
				swap(*lst_b);
				(*nb_sb)++;
				//ft_putstr("sb ");
			}
			else
			{
				dist = ft_lstfind_i(*lst_b, sorted[*next_index]);
				if (dist > *len_b / 2)
				{
					rotate(0, lst_b);
					(*nb_rrb)++;
					//ft_putstr("rrb ");
				}
				else
				{
					rotate(1, lst_b);
					if ((*lst_a)->nb <= sorted[*next_index])
					{
						if ((*lst_a)->nb == sorted[*next_index])
							(*next_index)++;
						rotate(1, lst_a);
						(*nb_instruct)++;
						//ft_putstr("rr ");
						(*nb_rr)++;
					}
					else
					{
						//ft_putstr("rb ");
					}
					(*nb_rb)++;
				}
			}
		}
		(*nb_instruct)++;
		if (verbose)
			debug(lst_a, lst_b, 0);
	}
	//tourne a
	while ((*lst_a)->nb == sorted[*next_index])
	{
		rotate(1, lst_a);
		//printf("ra ");
		(*nb_ra)++;
		(*nb_instruct)++;
		(*next_index)++;
		if (verbose)
			debug(lst_a, lst_b, 0);
	}
}

/*void	define_direction(t_list **lst_b, int *sorted, int pivot_min, int last)
{
	int i;
	t_list *tmp_b;
	int	dist_front;
	int dist_back;
	int len_b;

	tmp_b = *lst_b; //a tester
	len_b = lst_length(*lst_b);
	dist_front = 0;
	dist_back = -1;
	i = 0;
	//a opti
	while (tmp_b)
	{
		//if (dist_front != 0 && len_b < 10)
		//	printf("nb, sorted[min], last, dist_front : %i, %i, %i, %i\n", tmp_b->nb, sorted[pivot_min], last, dist_front);
		if (tmp_b->nb >= sorted[pivot_min] && tmp_b->nb < last && dist_front == 0)
		{
			dist_front = i;
			dist_back = len_b - i;
		}
		else if (tmp_b->nb >= sorted[pivot_min] && tmp_b->nb < last && dist_front != 0)
			dist_back = len_b - i;
		tmp_b = tmp_b->next;
		i++;
	}
	/// rr ?

	//voir dans test1.txt, mais la punition la plus opti n'est pas toujours la meme
	//a analyser
	if (dist_back != -1)
		dist_back += 1;
	printf("\ndist_front, dist_back, min, max : %i, %i, %i, %i\n", dist_front, dist_back, pivot_min, last);
	debug(NULL, lst_b, 1);
	///quand ils sont egalise sur le 1, je pense que c'est worth de faire un rrb pour repartir en rb
	if (dist_front <= dist_back || dist_back == -1)
	{
		rotate(1, lst_b);
		ft_putstr("rb ");
	}
	else
	{
		rotate(0, lst_b);
		ft_putstr("\033[31mrrb \033[0m");
	}
	printf("\n\n");
}*/