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

void    real_qs_lst(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_list **lst_halves, int verbose)
{
    int half;

    if (lst_inf->len_b > 9)
    {
        half = lst_inf->len_b / 2;
        ft_lstadd(lst_halves, ft_lstnew(&half, sizeof(half)));
        printf("avant split\n");
        //debug(lst_inf);
        split_b(lst_inf, tab_inf, verbose, &nb_instruct);
        printf("apres split\n");
        //debug(lst_inf);
        real_qs_lst(lst_inf, tab_inf, lst_halves, verbose);
        printf("avant send - half : %i\n", *((int *)(*lst_halves)->content));
        //debug(lst_inf);
        send_in_b(lst_inf, ft_pop_value(lst_halves), tab_inf, verbose, &nb_instruct);
        printf("apres send\n");
        //debug(lst_inf);
        real_qs_lst(lst_inf, tab_inf, lst_halves, verbose);
    }
    else
    {
        printf("avant sort");
        debug(lst_inf);
        sort_batch(lst_inf, tab_inf, &nb_instruct, verbose);
        printf("apres sort");
        //debug(lst_inf);
    }
}

void get_instruct(t_lst_inf *lst_inf, t_tab_inf *tab_inf, int verbose)
{
    t_list *lst_halves;

    lst_halves = NULL;
    tab_inf->next_index = 0;
    lst_inf->len_b = 0;
    if (tab_inf->sorted_len > 9)
    {
        send_half(lst_inf, tab_inf, 0, tab_inf->sorted_len / 2, verbose, &nb_instruct);
        debug(lst_inf);
        printf("plop\n");
        real_qs_lst(lst_inf, tab_inf, &lst_halves, verbose);
        printf("yo\n");
        //printf("desired : %i\n", sorted[next_index]);
        //debug(lst_inf);
        send_half(lst_inf, tab_inf, tab_inf->sorted_len / 2, tab_inf->sorted_len / 2 + tab_inf->sorted_len % 2, verbose, &nb_instruct);
        /*debug(lst_inf);
        printf("\n");*/
        real_qs_lst(lst_inf, tab_inf, &lst_halves, verbose);
    }
    else
    {
        //en vrai, ca marche avec send_half ici, mais vu que je fais que des ra et pas des rra, c'est moins opti
        little_list(lst_inf, tab_inf, &nb_instruct); // a faire mieux
    }
}

int main(int argc, char **argv)
{
    int     verbose;
    int     color;
    t_lst_inf lst_inf;
    t_tab_inf tab_inf;

    lst_inf.lst_b = NULL;
    lst_inf.lst_a = NULL;
    if (valid_input(argc, argv, &tab_inf, &(lst_inf.lst_a), &verbose, &color))
    {
        debug(&lst_inf);
        get_instruct(&lst_inf, &tab_inf, verbose);
        //faire ca mieux
		while (lst_inf.lst_a)
		{
			printf("%i ", *((int *)lst_inf.lst_a->content));
			lst_inf.lst_a = lst_inf.lst_a->next;
		}
		printf("\n");
        printf("nb_instruct : %i\n", nb_instruct);
    }
	else
        return (display_error());
	return (0);    
}