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

void    real_qs_lst(t_lst_inf *lst_inf, int *sorted, int *next_index, t_list **lst_halves, int verbose)
{
    int half;

    if (lst_inf->len_b > 9)
    {
        half = lst_inf->len_b / 2;
        ft_lstadd(lst_halves, ft_lstnew(&half, sizeof(half)));
        //printf("avant split\n");
        //debug(lst_inf);
        split_b(lst_inf, sorted, next_index, verbose, &nb_instruct);
        //printf("apres split\n");
        //debug(lst_inf);
        real_qs_lst(lst_inf, sorted, next_index,lst_halves, verbose);
        //printf("avant send - half : %i\n", *((int *)(*lst_halves)->content));
        //debug(lst_a, lst_b);
        send_in_b(lst_inf, ft_pop_value(lst_halves), sorted, next_index, verbose, &nb_instruct);
        //printf("apres send\n");
        //debug(lst_a, lst_b);
        real_qs_lst(lst_inf, sorted, next_index, lst_halves, verbose);
    }
    else
    {
        //printf("avant sort - desired : %i\n", sorted[*next_index]);
        //debug(lst_a, lst_b);
        sort_batch(lst_inf, sorted, &nb_instruct, next_index, verbose);
        //printf("apres sort - desired : %i\n", sorted[*next_index]);
        //debug(lst_a, lst_b);
    }
}

void get_instruct(t_lst_inf *lst_inf, int *sorted, int sorted_len, int verbose)
{
    int next_index;
    int len_b;
    t_list *lst_halves;

    lst_halves = NULL;
    next_index = 0;
    len_b = 0;
    if (sorted_len > 9)
    {
        send_half(lst_inf, sorted, 0, sorted_len / 2, &next_index, verbose, &nb_instruct);
        //debug(lst_inf);
        real_qs_lst(lst_inf, sorted, &next_index, &lst_halves, verbose);
        //printf("desired : %i\n", sorted[next_index]);
        //debug(lst_a, lst_b);
        send_half(lst_inf, sorted, sorted_len / 2, sorted_len / 2 + sorted_len % 2, &next_index, verbose, &nb_instruct);
        /*debug(lst_a, lst_b);
        printf("\n");*/
        real_qs_lst(lst_inf, sorted, &next_index, &lst_halves, verbose);
    }
    else
    {
        //en vrai, ca marche avec send_half ici, mais vu que je fais que des ra et pas des rra, c'est moins opti
        little_list(lst_inf, sorted, sorted_len, &nb_instruct); // a faire mieux
    }
}

int main(int argc, char **argv)
{
	//t_list  *lst_a;
	//t_list	*lst_b;
	int     *sorted;
    int     sorted_len;
    int     verbose;
    int     color;
    t_lst_inf lst_inf;

    lst_inf.lst_b = NULL;
    lst_inf.lst_a = NULL;
    //lst_b = NULL;
    //lst_a = NULL;
    sorted = NULL;
    if (valid_input(argc, argv, &sorted, &sorted_len, &lst_inf, &verbose, &color))
    {
        debug(&lst_inf);
        get_instruct(&lst_inf, sorted, sorted_len, verbose);
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