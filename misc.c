#include "push_swap.h"

static void	show_lst(t_list *lst, int lst_len, t_param param)
{
	int 	nb_to_show;
	int 	i;
	t_list *tmp_lst;

	nb_to_show = 20;
    tmp_lst = lst;
    i = 0;
    while (tmp_lst)
    {
        if (i < nb_to_show || i >= lst_len - nb_to_show || param.full)
            ft_printf("%i ", *((int *)tmp_lst->content));
        if (i == nb_to_show && tmp_lst->next && !param.full)
            ft_printf("... ");
        tmp_lst = tmp_lst->next;
        i++;
    }
}

void    show_state(t_lst_inf *lst_inf, t_param param)
{
    int len_a;

	ft_printf("A : ");
    if (lst_inf->lst_a)
    {
		len_a = ft_lstlength(lst_inf->lst_a); //a opti
		show_lst(lst_inf->lst_a, len_a, param);
    }
	ft_printf("\n");
	ft_printf("B : ");
    if (lst_inf->lst_b)
		show_lst(lst_inf->lst_b, lst_inf->len_b, param);
	ft_printf("\n");
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

void	choose_rotate(t_lst_inf *lst_inf, t_tab_inf *tab_inf, int modifier, int *do_ra, int *i_rotate)
{
	int i;

	i = lst_findi(lst_inf->lst_b, &(tab_inf->sorted[tab_inf->next_index]), sizeof(tab_inf->sorted[tab_inf->next_index]));
	if (i > lst_inf->len_b / 2 + lst_inf->len_b / 2 / 2 + modifier)
        rotate(0, &lst_inf->lst_b, "rrb");
    else
    {
        if (*do_ra)
        {
            rotate_both(1, &lst_inf->lst_a, &lst_inf->lst_b, "rr\n");
            *do_ra = 0;
			if (i_rotate)
            	(*i_rotate)++;
        }
        else
            rotate(1, &lst_inf->lst_b, "rb\n");
    }
}
