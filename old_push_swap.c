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

//gestion des doublons

#include "push_swap.h"


#include <stdio.h>
int nb_instruct = 0;
int nb_pb_1 = 0;
int nb_pa_1 = 0;
int nb_pb_2 = 0;
int nb_pb_3 = 0;
int nb_pa_2 = 0;
int nb_pa_3 = 0;
int nb_ra_1 = 0;
int nb_ra_2 = 0;
int nb_ra_3 = 0;
int nb_ra_4 = 0;
int nb_ra_5 = 0;
int nb_ra_6 = 0;
int nb_rb_1 = 0;
int nb_rb_2 = 0;
int nb_rrb = 0;
int nb_rr = 0;
int nb_sb = 0;


int debug_var = 0;

int plop = 0;

void    debug(t_list **lst_a, t_list **lst_b, int show)
{
    t_list *tmp_a;
    t_list *tmp_b;
    int i;
    int len_a;
    int len_b;

    int nb_to_show = 12;

    if (show)
    {
        if (lst_a && *lst_a)
        {
            len_a = lst_length(*lst_a); //a opti
            tmp_a = *lst_a;
            i = 0;
            while (tmp_a)
            {
                if (i < nb_to_show || i >= len_a - nb_to_show)
                    printf("%i ", tmp_a->nb);
                if (i == nb_to_show)
                    printf("... "); //a ameliorer
                tmp_a = tmp_a->next;
                i++;
            }
            printf("\n");
        }
        if (lst_b && *lst_b)
        {
            len_b = lst_length(*lst_b); //a opti
            tmp_b = *lst_b;
            i = 0;
            while (tmp_b)
            {
                if (i < nb_to_show || i > len_b - nb_to_show)
                    printf("%i ", tmp_b->nb);
                if (i == nb_to_show)
                    printf("... "); //a ameliorer
                tmp_b = tmp_b->next;
                i++;
            }
            printf("\n");
        }
    }
}

int r = 0;

void    send_half(t_list **sender, t_list **receiver, int *sorted, int pivot_min, int pivot_max, int sorted_len, int sender_a, int *next_index, int *len_b, int verbose)
{
    int i;
    int last;

    i = 0;
    if (pivot_max != sorted_len)
        last = sorted[pivot_max];
    else
        last = sorted[pivot_max - 1] + 1;
    while (i < pivot_max - pivot_min)
    {
        if (sender_a)
        {
            if ((*sender)->nb == sorted[*next_index] && *next_index != 0)
            {
                rotate(1, sender);
                (*next_index)++;
                i++;
                //ft_putstr("ra\n");
                nb_ra_1++;
            }
            else if ((*sender)->nb >= sorted[pivot_min] && (*sender)->nb < last)
            {
                push(receiver, sender);
                //ft_putstr("pb\n");
                (*len_b)++;
                nb_pb_1++;
                i++;
            }
            else
            {
                nb_ra_2++;
                rotate(1, sender);
                //ft_putstr("ra\n");
            }
        }
        else
        {
            if (((*sender)->nb >= sorted[pivot_min] && (*sender)->nb < last) || ((*sender)->nb == sorted[*next_index]))
            {
                push(receiver, sender);
                (*len_b)--;
                    //ft_putstr("pa\n");
                if ((*receiver)->nb == sorted[*next_index])
                {
                    if (((*receiver)->nb < sorted[pivot_min] || (*receiver)->nb > last))
                        i--;
                    (*next_index)++;
                    rotate(1, receiver);
                    //ft_putstr("ra\n");
                    nb_instruct++;
                    nb_ra_3++;
                }
                i++;
                nb_pa_1++;
            }
            else
            {
                rotate(1, sender);
                //ft_putstr("rb\n");
                nb_rb_1++;
            }
            //define_direction(sender, sorted, pivot_min, last);
        }
        nb_instruct++;
        if (verbose && sender_a)
            debug(sender, receiver, 0);
        else if (verbose && !sender_a)
            debug(receiver, sender, 0);
    }
}

int    send_in_b(t_list **lst_a, t_list **lst_b, int *sorted, int *next_index, int *len_b, int verbose)
{
    int i;
    int min;
    int max;
    
    i = 0;
    min = sorted[*next_index];
    max = 0;
    while ((*lst_a)->nb != sorted[*next_index])
    {
        if (max == 0 || (*lst_a)->nb > max)
            max = (*lst_a)->nb;
        push(lst_b, lst_a);
        //ft_putstr("pb ");
        nb_instruct++;
        nb_pb_2++;
        (*len_b)++;
        if (verbose)
            debug(lst_a, lst_b, 0);
        i++;
    }
    rotate(1, lst_a);
    //ft_putstr("ra ");
    nb_instruct++;
    (*next_index)++;
    nb_ra_4++;
    while (i < max - min)
    {
        if ((*lst_a)->nb == sorted[*next_index])
        {
            rotate(1, lst_a);
            //ft_putstr("ra\n");
            nb_ra_6++;
            (*next_index)++;
        }
        else
        {
            if (max == 0 || (*lst_a)->nb > max)
                max = (*lst_a)->nb;
            push(lst_b, lst_a);
            nb_pb_3++;
            (*len_b)++;
            //ft_putstr("pb ");
        }
        nb_instruct++;
        if (verbose)
            debug(lst_a, lst_b, 0);
        i++;
    }
    return (max);
}

int q = 0;

void    real_qs_lst(t_list **lst_a, t_list **lst_b, int *sorted, int pivot_min, int pivot_max, int sorted_len, int *next_index, int *len_b, int verbose)
{
    //int len_b;
    int diff;

    if (q >= 1)
    {
        printf("\033[31m\nnb_instructs : %i\nnb_ra_1 : %i\nnb_ra_2 : %i\nnb_ra_3 : %i\nnb_ra_4 : %i\nnb_ra_5 : %i\nnb_ra_6 : %i\ntotal_ra : %i\n\nnb_pa_1 : %i\nnb_pa_2 : %i\nnb_pa_3 : %i\ntotal_pa : %i\n\nnb_pb_1 : %i\nnb_pb_2 : %i\nnb_pb_3 : %i\ntotal_pb : %i\n\nnb_rb_1 : %i\nnb_rb_2 : %i\nnb_sb : %i\nnb_rr : %i\nnb_rrb  : %i\ntotal_autre: %i\n\033[0m", nb_instruct, nb_ra_1, nb_ra_2, nb_ra_3, nb_ra_4, nb_ra_5, nb_ra_6, nb_ra_1 + nb_ra_2 + nb_ra_3 + nb_ra_4 + nb_ra_5 + nb_ra_6, nb_pa_1, nb_pa_2, nb_pa_3, nb_pa_1 + nb_pa_2 + nb_pa_3, nb_pb_1, nb_pb_2, nb_pb_3, nb_pb_1 + nb_pb_2 + nb_pb_3, nb_rb_1, nb_rb_2, nb_sb, nb_rr, nb_rrb, nb_rb_1 + nb_rb_2 + nb_sb + nb_rr + nb_rrb);
        debug(lst_a, lst_b, 1);
        printf("\n");
    }

    //len_b = lst_length(*lst_b);
    if (*len_b > 9)
    {
        send_half(lst_b, lst_a, sorted, pivot_min, pivot_max, sorted_len, 0, next_index, len_b, verbose);
        //printf("apres send half - min, max, desired, diff : %i, %i, %i, %i\n", pivot_min, pivot_max, sorted[*next_index], pivot_max - pivot_min);
        
        //printf("test : desired, diff2, min2 : %i, %i, %i\n", sorted[*next_index], diff_2, sorted[*next_index] + diff_2 / 2);
        
        //int diff_2 = pivot_max - sorted[*next_index];
        diff = pivot_max - pivot_min;
        //pivot_min = sorted[*next_index] + diff_2 / 2;

        //pivot_min -= diff / 2;
        //if (diff / 2 == 0)
        //    pivot_min--;
        pivot_max -= diff;
        pivot_min = sorted[*next_index] + *len_b / 2;
        real_qs_lst(lst_a, lst_b, sorted, pivot_min, pivot_max, sorted_len, next_index, len_b, verbose);

        /*printf("\033[31m\nnb_instructs : %i\nnb_ra_1 : %i\nnb_ra_2 : %i\nnb_ra_3 : %i\nnb_ra_4 : %i\nnb_ra_5 : %i\nnb_ra_6 : %i\ntotal_ra : %i\n\nnb_pa_1 : %i\nnb_pa_2 : %i\nnb_pa_3 : %i\ntotal_pa : %i\n\nnb_pb_1 : %i\nnb_pb_2 : %i\nnb_pb_3 : %i\ntotal_pb : %i\n\nnb_rb_1 : %i\nnb_rb_2 : %i\nnb_sb : %i\nnb_rr : %i\nnb_rrb  : %i\ntotal_autre: %i\n\033[0m", nb_instruct, nb_ra_1, nb_ra_2, nb_ra_3, nb_ra_4, nb_ra_5, nb_ra_6, nb_ra_1 + nb_ra_2 + nb_ra_3 + nb_ra_4 + nb_ra_5 + nb_ra_6, nb_pa_1, nb_pa_2, nb_pa_3, nb_pa_1 + nb_pa_2 + nb_pa_3, nb_pb_1, nb_pb_2, nb_pb_3, nb_pb_1 + nb_pb_2 + nb_pb_3, nb_rb_1, nb_rb_2, nb_sb, nb_rr, nb_rrb, nb_rb_1 + nb_rb_2 + nb_sb + nb_rr + nb_rrb);
        debug(lst_a, lst_b, 1);
        printf("\n");*/

        pivot_max = send_in_b(lst_a, lst_b, sorted, next_index, len_b, verbose);

        /*printf("\033[31m\nnb_instructs : %i\nnb_ra_1 : %i\nnb_ra_2 : %i\nnb_ra_3 : %i\nnb_ra_4 : %i\nnb_ra_5 : %i\nnb_ra_6 : %i\ntotal_ra : %i\n\nnb_pa_1 : %i\nnb_pa_2 : %i\nnb_pa_3 : %i\ntotal_pa : %i\n\nnb_pb_1 : %i\nnb_pb_2 : %i\nnb_pb_3 : %i\ntotal_pb : %i\n\nnb_rb_1 : %i\nnb_rb_2 : %i\nnb_sb : %i\nnb_rr : %i\nnb_rrb  : %i\ntotal_autre: %i\n\033[0m", nb_instruct, nb_ra_1, nb_ra_2, nb_ra_3, nb_ra_4, nb_ra_5, nb_ra_6, nb_ra_1 + nb_ra_2 + nb_ra_3 + nb_ra_4 + nb_ra_5 + nb_ra_6, nb_pa_1, nb_pa_2, nb_pa_3, nb_pa_1 + nb_pa_2 + nb_pa_3, nb_pb_1, nb_pb_2, nb_pb_3, nb_pb_1 + nb_pb_2 + nb_pb_3, nb_rb_1, nb_rb_2, nb_sb, nb_rr, nb_rrb, nb_rb_1 + nb_rb_2 + nb_sb + nb_rr + nb_rrb);
        debug(lst_a, lst_b, 1);
        printf("\n");*/

        int diff_2 = pivot_max - sorted[*next_index];
        //min est trop gros ?
        pivot_min = sorted[*next_index] + diff_2 / 2 + 1 + diff_2 % 2;
        pivot_max++;
        real_qs_lst(lst_a, lst_b, sorted, pivot_min, pivot_max, sorted_len, next_index, len_b, verbose);
        q++;
        /*printf("\033[31m\nnb_instructs : %i\nnb_ra_1 : %i\nnb_ra_2 : %i\nnb_ra_3 : %i\nnb_ra_4 : %i\nnb_ra_5 : %i\nnb_ra_6 : %i\ntotal_ra : %i\n\nnb_pa_1 : %i\nnb_pa_2 : %i\nnb_pa_3 : %i\ntotal_pa : %i\n\nnb_pb_1 : %i\nnb_pb_2 : %i\nnb_pb_3 : %i\ntotal_pb : %i\n\nnb_rb_1 : %i\nnb_rb_2 : %i\nnb_sb : %i\nnb_rr : %i\nnb_rrb  : %i\ntotal_autre: %i\n\033[0m", nb_instruct, nb_ra_1, nb_ra_2, nb_ra_3, nb_ra_4, nb_ra_5, nb_ra_6, nb_ra_1 + nb_ra_2 + nb_ra_3 + nb_ra_4 + nb_ra_5 + nb_ra_6, nb_pa_1, nb_pa_2, nb_pa_3, nb_pa_1 + nb_pa_2 + nb_pa_3, nb_pb_1, nb_pb_2, nb_pb_3, nb_pb_1 + nb_pb_2 + nb_pb_3, nb_rb_1, nb_rb_2, nb_sb, nb_rr, nb_rrb, nb_rb_1 + nb_rb_2 + nb_sb + nb_rr + nb_rrb);
        debug(lst_a, lst_b, 1);
        printf("\n");
        exit(1);*/

    }
    else
    {
        sort_batch(lst_a, lst_b, sorted, &nb_instruct, next_index, len_b, verbose, &nb_ra_5, &nb_sb, &nb_rrb, &nb_pa_2, &nb_rr, &nb_rb_2);
        /*printf("\033[31m\nnb_instructs : %i\nnb_ra_1 : %i\nnb_ra_2 : %i\nnb_ra_3 : %i\nnb_ra_4 : %i\nnb_ra_5 : %i\nnb_ra_6 : %i\ntotal_ra : %i\n\nnb_pa_1 : %i\nnb_pa_2 : %i\nnb_pa_3 : %i\ntotal_pa : %i\n\nnb_pb_1 : %i\nnb_pb_2 : %i\nnb_pb_3 : %i\ntotal_pb : %i\n\nnb_rb_1 : %i\nnb_rb_2 : %i\nnb_sb : %i\nnb_rr : %i\nnb_rrb  : %i\ntotal_autre: %i\n\033[0m", nb_instruct, nb_ra_1, nb_ra_2, nb_ra_3, nb_ra_4, nb_ra_5, nb_ra_6, nb_ra_1 + nb_ra_2 + nb_ra_3 + nb_ra_4 + nb_ra_5 + nb_ra_6, nb_pa_1, nb_pa_2, nb_pa_3, nb_pa_1 + nb_pa_2 + nb_pa_3, nb_pb_1, nb_pb_2, nb_pb_3, nb_pb_1 + nb_pb_2 + nb_pb_3, nb_rb_1, nb_rb_2, nb_sb, nb_rr, nb_rrb, nb_rb_1 + nb_rb_2 + nb_sb + nb_rr + nb_rrb);
        debug(lst_a, lst_b, 1);
        printf("\n");
        exit(1);*/
    }
}

void get_instruct(t_list **lst_a, t_list **lst_b, int *sorted, int sorted_len, int verbose)
{
    int pivot_min;
    int pivot_max;
    int next_index;
    int len_b;

    next_index = 0;
    len_b = 0;
    send_half(lst_a, lst_b, sorted, 0, sorted_len / 2, sorted_len, 1, &next_index, &len_b, verbose);
    printf("\033[31m\nnb_instructs : %i\nnb_ra_1 : %i\nnb_ra_2 : %i\nnb_ra_3 : %i\nnb_ra_4 : %i\nnb_ra_5 : %i\nnb_ra_6 : %i\ntotal_ra : %i\n\nnb_pa_1 : %i\nnb_pa_2 : %i\nnb_pa_3 : %i\ntotal_pa : %i\n\nnb_pb_1 : %i\nnb_pb_2 : %i\nnb_pb_3 : %i\ntotal_pb : %i\n\nnb_rb_1 : %i\nnb_rb_2 : %i\nnb_sb : %i\nnb_rr : %i\nnb_rrb  : %i\ntotal_autre: %i\n\033[0m", nb_instruct, nb_ra_1, nb_ra_2, nb_ra_3, nb_ra_4, nb_ra_5, nb_ra_6, nb_ra_1 + nb_ra_2 + nb_ra_3 + nb_ra_4 + nb_ra_5 + nb_ra_6, nb_pa_1, nb_pa_2, nb_pa_3, nb_pa_1 + nb_pa_2 + nb_pa_3, nb_pb_1, nb_pb_2, nb_pb_3, nb_pb_1 + nb_pb_2 + nb_pb_3, nb_rb_1, nb_rb_2, nb_sb, nb_rr, nb_rrb, nb_rb_1 + nb_rb_2 + nb_sb + nb_rr + nb_rrb);
    debug(lst_a, lst_b, 1);
    printf("\n");
    pivot_max = sorted_len / 2;
    pivot_min = pivot_max / 2;
    real_qs_lst(lst_a, lst_b, sorted, pivot_min, pivot_max, sorted_len, &next_index, &len_b, verbose);
    printf("\033[31m\nnb_instructs : %i\nnb_ra_1 : %i\nnb_ra_2 : %i\nnb_ra_3 : %i\nnb_ra_4 : %i\nnb_ra_5 : %i\nnb_ra_6 : %i\ntotal_ra : %i\n\nnb_pa_1 : %i\nnb_pa_2 : %i\nnb_pa_3 : %i\ntotal_pa : %i\n\nnb_pb_1 : %i\nnb_pb_2 : %i\nnb_pb_3 : %i\ntotal_pb : %i\n\nnb_rb_1 : %i\nnb_rb_2 : %i\nnb_sb : %i\nnb_rr : %i\nnb_rrb  : %i\ntotal_autre: %i\n\033[0m", nb_instruct, nb_ra_1, nb_ra_2, nb_ra_3, nb_ra_4, nb_ra_5, nb_ra_6, nb_ra_1 + nb_ra_2 + nb_ra_3 + nb_ra_4 + nb_ra_5 + nb_ra_6, nb_pa_1, nb_pa_2, nb_pa_3, nb_pa_1 + nb_pa_2 + nb_pa_3, nb_pb_1, nb_pb_2, nb_pb_3, nb_pb_1 + nb_pb_2 + nb_pb_3, nb_rb_1, nb_rb_2, nb_sb, nb_rr, nb_rrb, nb_rb_1 + nb_rb_2 + nb_sb + nb_rr + nb_rrb);
    debug(lst_a, lst_b, 1);
    printf("\n");
    exit(1);
    pivot_min = pivot_max;
    pivot_max = sorted_len;
    send_half(lst_a, lst_b, sorted, pivot_min, pivot_max, sorted_len, 1, &next_index, &len_b, verbose);
    printf("\033[31m\nnb_instructs : %i\nnb_ra_1 : %i\nnb_ra_2 : %i\nnb_ra_3 : %i\nnb_ra_4 : %i\nnb_ra_5 : %i\nnb_ra_6 : %i\ntotal_ra : %i\n\nnb_pa_1 : %i\nnb_pa_2 : %i\nnb_pa_3 : %i\ntotal_pa : %i\n\nnb_pb_1 : %i\nnb_pb_2 : %i\nnb_pb_3 : %i\ntotal_pb : %i\n\nnb_rb_1 : %i\nnb_rb_2 : %i\nnb_sb : %i\nnb_rr : %i\nnb_rrb  : %i\ntotal_autre: %i\n\033[0m", nb_instruct, nb_ra_1, nb_ra_2, nb_ra_3, nb_ra_4, nb_ra_5, nb_ra_6, nb_ra_1 + nb_ra_2 + nb_ra_3 + nb_ra_4 + nb_ra_5 + nb_ra_6, nb_pa_1, nb_pa_2, nb_pa_3, nb_pa_1 + nb_pa_2 + nb_pa_3, nb_pb_1, nb_pb_2, nb_pb_3, nb_pb_1 + nb_pb_2 + nb_pb_3, nb_rb_1, nb_rb_2, nb_sb, nb_rr, nb_rrb, nb_rb_1 + nb_rb_2 + nb_sb + nb_rr + nb_rrb);
    debug(lst_a, lst_b, 1);
    printf("\n");
    pivot_min = sorted_len / 2 + (sorted_len / 2 / 2);
    pivot_max = sorted_len;
    real_qs_lst(lst_a, lst_b, sorted, pivot_min, pivot_max, sorted_len, &next_index, &len_b, verbose);
}

int main(int argc, char **argv)
{
	int     i;
	t_list  *lst_a;
	t_list	*lst_b;
	int     *sorted;
	int     tmp;
	int		res;
	//int		nb_instruct = 0;
    int     len;
    int     j;
    int     verbose;

	i = 1;
	res = 1;
    lst_b = NULL;
    lst_a = NULL;
	if (argc > 1)
	{
        if (ft_strcmp(argv[i], "-v") == 0)
            verbose = 1;
        else
            verbose = 0;
		sorted = malloc((argc - 1 - verbose) * sizeof(int));
		while (argv[i + verbose])
		{
			tmp = ft_atoi(argv[i + verbose]);
			sorted[i - 1] = tmp;
			i++;
			ft_lstappend(&lst_a, ft_lstnew(tmp));
		}
		quicksort(sorted, i - 1);
        len = i - 1;
        j = 0;
		get_instruct(&lst_a, &lst_b, sorted, len, verbose);
		while (lst_a)
		{
			printf("%i ", lst_a->nb);
			lst_a = lst_a->next;
		}
		printf("\n");
        printf("nb_instruct : %i\n", nb_instruct);
        printf("\033[31m\nnb_instructs : %i\nnb_ra_1 : %i\nnb_ra_2 : %i\nnb_ra_3 : %i\nnb_ra_4 : %i\nnb_ra_5 : %i\nnb_ra_6 : %i\ntotal_ra : %i\n\nnb_pa_1 : %i\nnb_pa_2 : %i\nnb_pa_3 : %i\ntotal_pa : %i\n\nnb_pb_1 : %i\nnb_pb_2 : %i\nnb_pb_3 : %i\ntotal_pb : %i\n\nnb_rb_1 : %i\nnb_rb_2 : %i\nnb_sb : %i\nnb_rr : %i\nnb_rrb  : %i\ntotal_autre: %i\n\033[0m", nb_instruct, nb_ra_1, nb_ra_2, nb_ra_3, nb_ra_4, nb_ra_5, nb_ra_6, nb_ra_1 + nb_ra_2 + nb_ra_3 + nb_ra_4 + nb_ra_5 + nb_ra_6, nb_pa_1, nb_pa_2, nb_pa_3, nb_pa_1 + nb_pa_2 + nb_pa_3, nb_pb_1, nb_pb_2, nb_pb_3, nb_pb_1 + nb_pb_2 + nb_pb_3, nb_rb_1, nb_rb_2, nb_sb, nb_rr, nb_rrb, nb_rb_1 + nb_rb_2 + nb_sb + nb_rr + nb_rrb);
	}
	return (0);    
}