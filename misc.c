#include "push_swap.h"


#include <stdio.h>

void    debug(t_lst_inf *lst_inf)
{
    t_list *tmp_a;
    t_list *tmp_b;
    int i;
    int len_a;
    int len_b;

    int nb_to_show = 101;

    if (lst_inf->lst_a)
    {
        len_a = ft_lstlength(lst_inf->lst_a); //a opti
        tmp_a = lst_inf->lst_a;
        i = 0;
        while (tmp_a)
        {
            if (i < nb_to_show || i >= len_a - nb_to_show)
                printf("%i ", *((int *)tmp_a->content));
             if (i == nb_to_show)
                printf("... "); //a ameliorer
            tmp_a = tmp_a->next;
            i++;
        }
        printf("\n");
    }
    if (lst_inf->lst_b)
    {
        len_b = ft_lstlength(lst_inf->lst_b); //a opti
        tmp_b = lst_inf->lst_b;
        i = 0;
        while (tmp_b)
        {
            if (i < nb_to_show || i > len_b - nb_to_show)
                printf("%i ", *((int *)tmp_b->content));
            if (i == nb_to_show)
                printf("... "); //a ameliorer
            tmp_b = tmp_b->next;
            i++;
        }
        printf("\n");
    }
	printf("\n");
}

int	quicksort(int *arr, int len) //a ameliorer
{
	int i;
	int first_supp;
	int tmp;

	i = 1;
	first_supp = 0;
	while (i < len)
	{
		if (arr[i] > arr[0] && first_supp == 0)
			first_supp = i;
		else if (arr[i] < arr[0] && first_supp != 0)
		{
			tmp = arr[first_supp];
			arr[first_supp] = arr[i];
			arr[i] = tmp;
			first_supp++;
		}
		else if (arr[i] == arr[0])
			return (0);
		i++;
	}
	if (len > 1)
	{
		if (first_supp == 0)
		{
			tmp = arr[first_supp];
			arr[first_supp] = arr[1];
			arr[1] = tmp;
			if (!quicksort(arr, len))
				return (0);
		}
		else
		{
			tmp = arr[first_supp - 1];
			arr[first_supp - 1] = arr[0];
			arr[0] = tmp;
			if (!quicksort(arr, first_supp))
				return (0);
			if (!quicksort(&arr[first_supp], len - first_supp))
				return (0);
		}
	}
	return (1);
}


