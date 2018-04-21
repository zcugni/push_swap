// Je supprimerais/modifierais un bon nombre de ces fonctions quand je factoriserais la principale, mais en attendant je les mets ici

#include "push_swap.h"

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

int		abs(int nb)
{
	if (nb < 0)
		return (-nb);
	else
		return (nb);
}

int		adjacent(int nb, t_list *lst, int *sorted)
{
	int i;

	i = 0;
	if (lst)
	{
		while (sorted[i] != lst->nb)
			i++;
		if (nb == sorted[i - 1])
			return (-1);
		else if (nb == sorted[i + 1]) //segfault ?
			return (1);
	}
	return (0);
}

int	will_send(int nb, int *sorted, t_list *lst_a_ori, int len_current, int len_ori)
{
	//je devrais peut-etre continuer plus loin (verifier si je dois send le next de celui-ci et deduire en fonction)
	int up;
	int dist_up;
	
	up = get_up(nb, sorted, len_ori);
	dist_up = get_up_dist(nb, up, lst_a_ori, len_current);
	if (((dist_up > 2 && dist_up != 100) || dist_up < -2))
		return (1);
	else
		return (0);
}

#include "stdio.h"

int will_receive(t_list **lst_a_current, t_list **lst_b, int *sorted, int len_current, int len_ori, t_list **lst_a_ori)
{
	int up;
	int dist_up;

	up = get_up((*lst_a_current)->nb, sorted, len_ori);
	dist_up = get_up_dist((*lst_a_current)->nb, up, *lst_a_ori, len_current);
	if (adjacent((*lst_a_current)->nb, *lst_b, sorted) || ((*lst_a_current)->next && (adjacent((*lst_a_current)->next->nb, *lst_b, sorted))))
	{
		if ((*lst_a_ori)->nb == (*lst_a_current)->nb && (*lst_a_ori)->nb != sorted[len_ori - 1])
			if (dist_up <= 2 && dist_up >= -2)
				return (1);
	}
	return (0);
}

int	is_last_down(int nb, t_list *lst, int *sorted, int len)
{
	t_list *tmp;

	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->nb == get_down(nb, sorted, len))
		return (1);
	return (0);
}