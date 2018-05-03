/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 22:35:25 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/03 22:35:26 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    split_b(t_lst_inf *lst_inf, int *sorted, int *next_index, int verbose, int *nb_instruct)
{
    int i_send;
    int i_rotate;
    int nb_to_send;
    int do_ra; // je pourrais faire sans cette variable mais elle rends le code beaucoup plus lisible
    int pivot_min;

    pivot_min = lst_inf->len_b / 2 + lst_inf->len_b % 2 + *next_index;
    i_send = 0;
    i_rotate = 0;
    do_ra = 0;
    nb_to_send = lst_inf->len_b / 2; //je pourrais utilise le half added en vrai

    while (i_send < nb_to_send)
    {
        if (*((int *)lst_inf->lst_b->content) >= sorted[pivot_min] || *((int *)lst_inf->lst_b->content) == sorted[*next_index])
        {
            if (do_ra && i_rotate <= nb_to_send - 1)
            {
                rotate(1, &lst_inf->lst_a, "ra\n");
                do_ra = 0;
                (*nb_instruct)++;
                i_rotate++;
            }
            push(&lst_inf->lst_a, &lst_inf->lst_b, "pa\n");
            lst_inf->len_b--;
            if (*((int *)lst_inf->lst_a->content) == sorted[*next_index])
            {
                if (*((int *)lst_inf->lst_a->content) < sorted[pivot_min])
                    i_send--;
                if (i_rotate <= nb_to_send - 1)
                    (*next_index)++;
                do_ra = 1;
            }
            i_send++;
        }
        //else if (*((int *)lst_inf->lst_a->next->content) == sorted[*next_index] && *((int *)lst_inf->lst_a->content) == sorted[*next_index + 1]) //c'est tellement specifique comme cas que ca n'arrive jamais
        //    swap(*lst_b, "sb\n");
        else
        {
            int index = lst_findi(lst_inf->lst_b, &(sorted[*next_index]), sizeof(sorted[*next_index]));
            if (index > lst_inf->len_b / 2 + lst_inf->len_b / 2 / 2) //si je rajoute -1 c'est des fois plus opti
                rotate(0, &lst_inf->lst_b, "rrb");
            else
            {
                if (do_ra && i_rotate <= nb_to_send - 1)
                {
                    rotate_both(1, &lst_inf->lst_a, &lst_inf->lst_b, "rr\n");
                    do_ra = 0;
                    i_rotate++;
                }
                else
                    rotate(1, &lst_inf->lst_b, "rb\n");
            }
        }
        (*nb_instruct)++;
        if (verbose)
            debug(lst_inf);
    }
    //ce truc n'arrive jamais, je suis pas sure qu'il est encore d'actu
    /*if (*((int *)lst_inf->lst_a->content) < sorted[*next_index])
    {
        printf("yo\n");
        (*next_index)--;
    }*/
    //je devrais pas faire une verif ou je tourne lst_a avant dans ce while ?
    while (lst_inf->lst_b && *((int *)lst_inf->lst_b->content) == sorted[*next_index])
    {
        push(&lst_inf->lst_a, &lst_inf->lst_b, "pa\n");
        rotate(1, &lst_inf->lst_a, "ra\n");
        *nb_instruct += 2;
        lst_inf->len_b--;
        (*next_index)++;
        if (verbose)
            debug(lst_inf);
    }
}

void    send_half(t_lst_inf *lst_inf, int *sorted, int pivot_min, int nb_to_send, int *next_index, int verbose, int *nb_instruct)
{
    int i;

    i = 0;
    while (i < nb_to_send)
    {
        //c'est un cas tellement particulier qu'il apparait jamais meme s'il est logique
        //pas de risque de segfault si next_index est le max ?
        /*if (*next_index != 0 && *((int *)lst_inf->lst_a->next->content) == sorted[*next_index] && *((int *)lst_inf->lst_a->content) == sorted[*next_index + 1])
        {
            printf("yup\n");
            exit(1);
            swap(*lst_a, "sa\n");
        }*/
        if (*((int *)lst_inf->lst_a->content) == sorted[*next_index] && *next_index != 0)
        {
            rotate(1, &lst_inf->lst_a, "ra\n");
            (*next_index)++;
            i++;
        }
        else if (*((int *)lst_inf->lst_a->content) >= sorted[pivot_min] && *((int *)lst_inf->lst_a->content) <= sorted[pivot_min + nb_to_send - 1])
        {
            push(&lst_inf->lst_b, &lst_inf->lst_a, "pb\n");
            i++;
            lst_inf->len_b++;
        }
        else
            rotate(1, &lst_inf->lst_a, "ra\n");
        (*nb_instruct)++;
        if (verbose)
            debug(lst_inf);
    }
}

void    send_in_b(t_lst_inf *lst_inf, int diff, int *sorted, int *next_index, int verbose, int *nb_instruct)
{
    int i;

    i = 0;
    while (i < diff)
    {
        //je risque pas d'avoir un segfault si next_index est le max ?
        
        if (*((int *)lst_inf->lst_a->content) <= sorted[*next_index])
        {
            rotate(1, &lst_inf->lst_a, "ra\n");
            (*next_index)++;
        }
        else if (*((int *)lst_inf->lst_a->next->content) == sorted[*next_index] && *((int *)lst_inf->lst_a->content) == sorted[*next_index + 1])
        {
            swap(lst_inf->lst_a, "sa\n");
            i--;
        }
        else
        {
            push(&lst_inf->lst_b, &lst_inf->lst_a, "pb\n");
            lst_inf->len_b++;
        }
        i++;
        (*nb_instruct)++;
        if (verbose)
            debug(lst_inf);
    }
}
