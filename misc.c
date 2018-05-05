#include "push_swap.h"

#include <stdio.h>

static void	show_lst(t_list *lst, int lst_len, t_param param, char last_op)
{
	int 	nb_to_show;
	int 	i;
	t_list *tmp_lst;

	nb_to_show = 20;
    tmp_lst = lst;
    i = 0;
	if ((last_op == 'p' || last_op == 'u') && param.color)
		ft_printf("\033[32m_ \033[0m");
    while (tmp_lst)
    {
        if (i < nb_to_show || i >= lst_len - nb_to_show || param.full)
		{
			if (param.color &&
			((i == 0 && (last_op == 's' || last_op == 'r' || last_op == 'd')) ||
			(i == 1 && last_op == 's') ||
			(!tmp_lst->next && last_op == 'u')))
				ft_printf("\033[32m%i\033[0m ", *((int *)tmp_lst->content));
			else
				ft_printf("%i ", *((int *)tmp_lst->content));
		}
        if (i == nb_to_show && tmp_lst->next && !param.full)
            ft_printf("... ");
        tmp_lst = tmp_lst->next;
        i++;
    }
	if (param.color && last_op == 'd')
		ft_printf("\033[32m_\033[0m");
}

void    show_state(t_lst_inf *lst_inf, t_param param, char *last_op)
{
    int		len_a;
	char	code;

	ft_printf("A : ");
    if (lst_inf->lst_a)
    {
		if (ft_strcmp(last_op, "ss\n") == 0 || ft_strcmp(last_op, "sa\n") == 0)
			code = 's';
		else if (ft_strcmp(last_op, "rr\n") == 0 || ft_strcmp(last_op, "ra\n") == 0)
			code = 'u';
		else if (ft_strcmp(last_op, "rrr\n") == 0 || ft_strcmp(last_op, "rra\n") == 0)
			code = 'd';
		else if (ft_strcmp(last_op, "pa\n") == 0)
			code = 'r';
		else if (ft_strcmp(last_op, "pb\n") == 0)
			code = 'p';
		len_a = ft_lstlength(lst_inf->lst_a); //a opti
		show_lst(lst_inf->lst_a, len_a, param, code);
    }
	ft_printf("\n");
	ft_printf("B : ");
	code = ' ';
	if (ft_strcmp(last_op, "ss\n") == 0 || ft_strcmp(last_op, "sb\n") == 0)
		code = 's';
	else if (ft_strcmp(last_op, "rr\n") == 0 || ft_strcmp(last_op, "rb\n") == 0)
		code = 'u';
	else if (ft_strcmp(last_op, "rrr\n") == 0 || ft_strcmp(last_op, "rrb\n") == 0)
		code = 'd';
	else if (ft_strcmp(last_op, "pa\n") == 0)
		code = 'p';
	else if (ft_strcmp(last_op, "pb\n") == 0)
		code = 'r';
	show_lst(lst_inf->lst_b, lst_inf->len_b, param, code);
	ft_printf("\n");	
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

void	choose_rotate(t_lst_inf *lst_inf, t_tab_inf *tab_inf, int modifier, int *do_ra, int *i_rotate, t_param param)
{
	int i;

	i = lst_findi(lst_inf->lst_b, &(tab_inf->sorted[tab_inf->next_index]), sizeof(tab_inf->sorted[tab_inf->next_index]));
	if (i > lst_inf->len_b / 2 + lst_inf->len_b / 2 / 2 + modifier)
	{
		rotate(0, lst_inf, "rrb\n", param);
	}   
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
		{
			rotate(1, lst_inf, "rb\n", param);
		}
    }
}

int	test_sorted(t_list *lst, int ascending)
{
	t_list *tmp;

	tmp = lst;
	while (tmp->next)
	{
		if (*((int *)tmp->content) > *((int *)tmp->next->content) && ascending)
			return (0);
		else if (*((int *)tmp->content) < *((int *)tmp->next->content) && !ascending)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
