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

void    split_b(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_param param, int *nb_instruct)
{
    int i_send;
    int i_rotate;
    int nb_to_send;
    int max_to_rotate;
    int do_ra; // je pourrais faire sans cette variable mais elle rends le code beaucoup plus lisible
    int pivot_min;

    pivot_min = lst_inf->len_b / 2 + lst_inf->len_b % 2 + tab_inf->next_index;
    i_send = 0;
    i_rotate = 0;
    do_ra = 0;
    nb_to_send = lst_inf->len_b / 2; //je pourrais utilise le half added en vrai
    max_to_rotate = lst_inf->len_b - nb_to_send;
    while (i_send < nb_to_send)
    {
        if (*((int *)lst_inf->lst_b->content) >= tab_inf->sorted[pivot_min] || *((int *)lst_inf->lst_b->content) == tab_inf->sorted[tab_inf->next_index])
        {
            if (do_ra)
            {
                rotate(1, lst_inf, "ra\n", param);
                do_ra = 0;
                (*nb_instruct)++;
                i_rotate++;
            }
            push(lst_inf, "pa\n", param);
            if (get_int(lst_inf, 'a') == get_desired(tab_inf))
            {
                if (*((int *)lst_inf->lst_a->content) < tab_inf->sorted[pivot_min])
                    i_send--;
                if (i_rotate < max_to_rotate)
                {
                    tab_inf->next_index++;
                    do_ra = 1;
                }
            }
            i_send++;
        }
        //else if (*((int *)lst_inf->lst_a->next->content) == sorted[*next_index] && *((int *)lst_inf->lst_a->content) == sorted[*next_index + 1]) //c'est tellement specifique comme cas que ca n'arrive jamais
        //    swap(*lst_b, "sb\n");
        else
        {
            choose_rotate(lst_inf, tab_inf, 3, &do_ra, &i_rotate, param); //(-3)
        }
        (*nb_instruct)++;
    }
    //ce truc n'arrive jamais, je suis pas sure qu'il est encore d'actu
    /*if (*((int *)lst_inf->lst_a->content) < sorted[*next_index])
    {
        printf("yo\n");
        (*next_index)--;
    }*/
    //je devrais pas faire une verif ou je tourne lst_a avant dans ce while ?
    //printf("interne\n");
    //show_state(lst_inf, param);
    while (lst_inf->lst_b && get_int(lst_inf, 'b') == get_desired(tab_inf))
    {
        push(lst_inf, "pa\n", param);
        rotate(1, lst_inf, "ra\n", param);
        *nb_instruct += 2;
        tab_inf->next_index++;
    }
}

void    send_half(t_lst_inf *lst_inf, t_tab_inf *tab_inf, int pivot_min, int nb_to_send, t_param param, int *nb_instruct)
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
        if (get_int(lst_inf, 'a') == get_desired(tab_inf) && tab_inf->next_index != 0)
        {
            rotate(1, lst_inf, "ra\n", param);
            tab_inf->next_index++;
            i++;
        }
        else if (get_int(lst_inf, 'a') >= tab_inf->sorted[pivot_min] && get_int(lst_inf, 'a') <= tab_inf->sorted[pivot_min + nb_to_send - 1])
        {
            push(lst_inf, "pb\n", param);
            i++;
        }
        else
            rotate(1, lst_inf, "ra\n", param);
        (*nb_instruct)++;
    }
}

void    send_in_b(t_lst_inf *lst_inf, int diff, t_tab_inf *tab_inf, t_param param, int *nb_instruct)
{
    int i;

    i = 0;
    while (i < diff)
    {
        //je risque pas d'avoir un segfault si next_index est le max ?
        
        if (get_int(lst_inf, 'a') <= get_desired(tab_inf))
        {
            rotate(1, lst_inf, "ra\n", param);
            tab_inf->next_index++;
        }
        else if (*((int *)lst_inf->lst_a->next->content) == get_desired(tab_inf) && get_int(lst_inf, 'a') == tab_inf->sorted[tab_inf->next_index + 1])
        {
            swap(lst_inf, "sa\n", param);
            i--;
        }
        else
            push(lst_inf, "pb\n", param);
        i++;
        (*nb_instruct)++;
    }
}
