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

void    split_b(t_list **lst_a, t_list **lst_b, int *sorted, int *next_index, int *len_b, int verbose)
{
    int i_send;
    int i_rotate;
    int nb_to_send;
    int do_ra; // je pourrais faire sans cette variable mais elle rends le code beaucoup plus lisible
    int pivot_min;
    //int do_rb = 0;

    int do_rb;
    pivot_min = *len_b / 2 + *len_b % 2 + *next_index;
    i_send = 0;
    i_rotate = 0;
    do_ra = 0;
    nb_to_send = *len_b / 2; //je pourrais utilise le half added en vrai

    do_rb = 0;
    while (i_send < nb_to_send)
    {
        if (*((int *)(*lst_b)->content) >= sorted[pivot_min] || *((int *)(*lst_b)->content) == sorted[*next_index])
        {
            if (do_ra && i_rotate <= nb_to_send - 1)
            {
                rotate(1, lst_a, "ra\n");
                do_ra = 0;
                nb_instruct++;
                i_rotate++;
            }
            push(lst_a, lst_b, "pa\n");
            (*len_b)--;
            if (*((int *)(*lst_a)->content) == sorted[*next_index])
            {
                if (*((int *)(*lst_a)->content) < sorted[pivot_min])
                    i_send--;
                if (i_rotate <= nb_to_send - 1)
                    (*next_index)++;
                do_ra = 1;
            }
            i_send++;
        }
        else
        {
            int index = lst_findi(*lst_b, &(sorted[*next_index]), sizeof(sorted[*next_index]));
            if (index > *len_b / 2 + *len_b / 2 / 2)
            {
                rotate(0, lst_b, "rrb");
            } 
            else
                do_rb = 1;
            if (do_ra && do_rb && i_rotate <= nb_to_send - 1)
            {
                rotate_both(1, lst_a, lst_b, "rr\n");
                do_ra = 0;
                do_rb = 0;
                i_rotate++;
            }
            else if (do_rb)
            {
                rotate(1, lst_b, "rb\n");
                do_rb = 0;
            }
                
            //swap si je suis le next de next_desired ?
        }
        nb_instruct++;
        if (verbose)
            debug(lst_a, lst_b);
    }
    if (*((int *)(*lst_a)->content) < sorted[*next_index]) //avant <= mais je sais plus pourquoi
        (*next_index)--;
    while (*lst_b && *((int *)(*lst_b)->content) == sorted[*next_index]) //je dois pouvoir fusionner avec en dessus mais en attendant laissons comme ca
    {
        push(lst_a, lst_b, "pa\n");
        rotate(1, lst_a, "ra\n");
        nb_instruct += 2;
        (*len_b)--;
        (*next_index)++;
        if (verbose)
            debug(lst_a, lst_b);
    }
}

void    send_half(t_list **lst_a, t_list **lst_b, int *sorted, int pivot_min, int nb_to_send, int *next_index, int *len_b, int verbose)
{
    int i;

    i = 0;
    while (i < nb_to_send)
    {
        //c'est un cas tellement particulier qu'il apparait jamais meme s'il est logique
        //pas de risque de segfault si next_index est le max ?
        /*if (*next_index != 0 && *((int *)(*lst_a)->next->content) == sorted[*next_index] && *((int *)(*lst_a)->content) == sorted[*next_index + 1])
        {
            printf("yup\n");
            exit(1);
            swap(*lst_a, "sa\n");
        }*/
        if (*((int *)(*lst_a)->content) == sorted[*next_index] && *next_index != 0)
        {
            rotate(1, lst_a, "ra\n");
            (*next_index)++;
            i++;
        }
        else if (*((int *)(*lst_a)->content) >= sorted[pivot_min] && *((int *)(*lst_a)->content) <= sorted[pivot_min + nb_to_send - 1])
        {
            push(lst_b, lst_a, "pb\n");
            i++;
            (*len_b)++;
        }
        else
            rotate(1, lst_a, "ra\n");
        nb_instruct++;
        if (verbose)
            debug(lst_a, lst_b);
    }
}

void    send_in_b(t_list **lst_a, t_list **lst_b, int diff, int *sorted, int *next_index, int *len_b, int verbose)
{
    int i;

    i = 0;
    while (i < diff)
    {
        //je risque pas d'avoir un segfault si next_index est le max ?
        
        if (*((int *)(*lst_a)->content) <= sorted[*next_index])
        {
            rotate(1, lst_a, "ra\n");
            (*next_index)++;
        }
        else if (*((int *)(*lst_a)->next->content) == sorted[*next_index] && *((int *)(*lst_a)->content) == sorted[*next_index + 1])
        {
            swap(*lst_a, "sa\n");
            i--;
        }
        else
        {
            push(lst_b, lst_a, "pb\n");
            (*len_b)++;
        }
        i++;
        nb_instruct++;
        if (verbose)
            debug(lst_a, lst_b);
    }
}

void    real_qs_lst(t_list **lst_a, t_list **lst_b, int *sorted, int *next_index, int *len_b, t_list **lst_halves, int verbose)
{
    int half;

    if (*len_b > 9)
    {
        half = *len_b / 2;
        ft_lstadd(lst_halves, ft_lstnew(&half, sizeof(half)));
        //printf("avant split\n");
        //debug(lst_a, lst_b);
        split_b(lst_a, lst_b, sorted, next_index, len_b, verbose);
        //printf("apres split\n");
        //debug(lst_a, lst_b);
        real_qs_lst(lst_a, lst_b, sorted, next_index, len_b, lst_halves, verbose);
        //printf("avant send - half : %i\n", *((int *)(*lst_halves)->content));
        //debug(lst_a, lst_b);
        send_in_b(lst_a, lst_b, ft_pop_value(lst_halves), sorted, next_index, len_b, verbose);
        //printf("apres send\n");
        //debug(lst_a, lst_b);
        real_qs_lst(lst_a, lst_b, sorted, next_index, len_b, lst_halves, verbose);
    }
    else
    {
        //printf("avant sort - desired : %i\n", sorted[*next_index]);
        //debug(lst_a, lst_b);
        sort_batch(lst_a, lst_b, sorted, &nb_instruct, next_index, len_b, verbose);
        //printf("apres sort\n");
        //debug(lst_a, lst_b);
    }
}

void get_instruct(t_list **lst_a, t_list **lst_b, int *sorted, int sorted_len, int verbose)
{
    int next_index;
    int len_b;
    t_list *lst_halves;

    lst_halves = NULL;
    next_index = 0;
    len_b = 0;
    if (sorted_len > 9)
    {
        send_half(lst_a, lst_b, sorted, 0, sorted_len / 2, &next_index, &len_b, verbose);
        /*debug(lst_a, lst_b);
        printf("\n");*/
        real_qs_lst(lst_a, lst_b, sorted, &next_index, &len_b, &lst_halves, verbose);
        //printf("desired : %i\n", sorted[next_index]);
        //debug(lst_a, lst_b);
        send_half(lst_a, lst_b, sorted, sorted_len / 2, sorted_len / 2 + sorted_len % 2, &next_index, &len_b, verbose);
        /*debug(lst_a, lst_b);
        printf("\n");*/
        real_qs_lst(lst_a, lst_b, sorted, &next_index, &len_b, &lst_halves, verbose);
    }
    else
    {
        //en vrai, ca marche avec send_half ici, mais vu que je fais que des ra et pas des rra, c'est moins opti
        little_list(lst_a, lst_b, sorted, sorted_len, &nb_instruct); // a faire mieux
    }
}

int main(int argc, char **argv)
{
	t_list  *lst_a;
	t_list	*lst_b;
	int     *sorted;
    int     sorted_len;
    int     verbose;
    int     color;

    lst_b = NULL;
    lst_a = NULL;
    sorted = NULL;
    if (valid_input(argc, argv, &sorted, &sorted_len, &lst_a, &verbose, &color))
    {
        debug(&lst_a, NULL);
        get_instruct(&lst_a, &lst_b, sorted, sorted_len, verbose);
        //faire ca mieux
		while (lst_a)
		{
			printf("%i ", *((int *)lst_a->content));
			lst_a = lst_a->next;
		}
		printf("\n");
        printf("nb_instruct : %i\n", nb_instruct);
    }
	else
        return (display_error());
	return (0);    
}