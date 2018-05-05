/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:01:16 by zcugni            #+#    #+#             */
/*   Updated: 2018/03/21 16:01:19 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


#include <stdio.h>
int nb_instruct = 0;

void    real_qs_lst(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_list **lst_halves, t_param param)
{
    int half;

    if (lst_inf->len_b > 9)
    {
        half = lst_inf->len_b / 2;
        ft_lstadd(lst_halves, ft_lstnew(&half, sizeof(half)));
        split_b(lst_inf, tab_inf,  param, &nb_instruct);
        real_qs_lst(lst_inf, tab_inf, lst_halves,  param);
        send_in_b(lst_inf, ft_pop_value(lst_halves), tab_inf, param, &nb_instruct);
        real_qs_lst(lst_inf, tab_inf, lst_halves,  param);
    }
    else
    {
        sort_batch(lst_inf, tab_inf, param, &nb_instruct);
    }
}

void get_instruct(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_param param)
{
    t_list *lst_halves;

    lst_halves = NULL;
    tab_inf->next_index = 0;
    lst_inf->len_b = 0;
    if (tab_inf->sorted_len > 9)
    {
        send_half(lst_inf, tab_inf, 0, tab_inf->sorted_len / 2,
            param, &nb_instruct);
        real_qs_lst(lst_inf, tab_inf, &lst_halves,  param);
        send_half(lst_inf, tab_inf, tab_inf->sorted_len / 2, 
            tab_inf->sorted_len / 2 + tab_inf->sorted_len % 2,
            param, &nb_instruct);
        real_qs_lst(lst_inf, tab_inf, &lst_halves,  param);
    }
    else
    {
        //en vrai, ca marche avec send_half ici, mais vu que je fais que des ra et pas des rra, c'est moins opti
        little_list(lst_inf, tab_inf, &nb_instruct, param); // a faire mieux
    }
}

int main(int argc, char **argv)
{
    t_param     param;
    t_lst_inf   lst_inf;
    t_tab_inf   tab_inf;
    int         first_nb_i;

    lst_inf.lst_b = NULL;
    lst_inf.lst_a = NULL;
    if(!init_param(argc, argv, &param, &first_nb_i))
        return (display_error());
    if (valid_input(first_nb_i, argv, &tab_inf, &(lst_inf.lst_a)))
    {
        get_instruct(&lst_inf, &tab_inf, param);
        printf("nb_instruct : %i\n", nb_instruct);
    }
	else
        return (display_error());
	return (0);    
}