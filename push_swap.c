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

void    debug(t_list **lst_a, t_list **lst_b)
{
    t_list *tmp_a;
    t_list *tmp_b;
    int i;
    int len_a;
    int len_b;

    int nb_to_show = 26;

    if (lst_a && *lst_a)
    {
        len_a = ft_lstlength(*lst_a); //a opti
        tmp_a = *lst_a;
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
    if (lst_b && *lst_b)
    {
        len_b = ft_lstlength(*lst_b); //a opti
        tmp_b = *lst_b;
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
}

void    split_b(t_list **lst_a, t_list **lst_b, int *sorted, int *next_index, int *len_b, int verbose)
{
    int i;
    int nb_to_send;
    int do_ra; // je pourrais faire sans cette variable mais elle rends le code beaucoup plus lisible
    int pivot_min;
    //int do_rb = 0;

    pivot_min = *len_b / 2 + *len_b % 2 + *next_index;
    i = 0;
    do_ra = 0;
    nb_to_send = *len_b / 2; //je pourrais utilise le half added en vrai
    while (i < nb_to_send)
    {
        if (*((int *)(*lst_b)->content) >= sorted[pivot_min] || *((int *)(*lst_b)->content) == sorted[*next_index])
        {
            if (do_ra)
            {
                rotate(1, lst_a, "ra\n");
                do_ra = 0;
                nb_instruct++;
            }
            push(lst_a, lst_b, "pa\n");
            (*len_b)--;
            if (*((int *)(*lst_a)->content) == sorted[*next_index])
            {
                if (*((int *)(*lst_a)->content) < sorted[pivot_min])
                    i--;
                (*next_index)++;
                do_ra = 1;
            }
            i++;
        }
        else //comparer avec et sans le define_direction, c'est pas forcement opti comme je l'ai fait la 
        {
            //define_direction(lst_b, pivot_min, sorted[*next_index], *len_b);
            if (do_ra)
            {
                rotate_both(1, lst_a, lst_b, "rr\n");
                do_ra = 0;
            }
            else
                rotate(1, lst_b, "rb\n");
        }
        nb_instruct++;
        if (verbose)
            debug(lst_a, lst_b);
    }
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

void    define_direction(t_list **lst_b, int pivot_min, int desired, int len_b)
{
    t_list *tmp;
    int i;
    int first;
    int last;

    tmp = *lst_b;
    i = 0;
    first = 0;
    last = 0;
    while (tmp)
    {
        //a opti
        if (*((int *)tmp->content) >= pivot_min || *((int *)tmp->content) == desired)
        {
            if (first == 0)
                first = i;
            else
                last = i;
        }
        i++;
        tmp = tmp->next;
    }
    //je sais pas si je devrais mettre une priorite sur le next_index ?
    if (last != 0 && len_b - last < first) //logiquement je devrais au moins ajouter une punition de +1
    {
        /*printf("first, last, len_b, len - last, min, desired : %i, %i, %i, %i, %i, %i\n", first, last, len_b, len_b - last, pivot_min, desired);
        debug(NULL, lst_b, 1);
        printf("\n");*/
        rotate(0, lst_b, "rrb\n");
    }
    else
        rotate(1, lst_b, "rb\n");
}

void    send_half(t_list **lst_a, t_list **lst_b, int *sorted, int pivot_min, int nb_to_send, int *next_index, int *len_b, int verbose)
{
    int i;

    i = 0;
    while (i < nb_to_send)
    {
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
        //y'a pas moyen de gagner des trucs en checkant si on vient pas d'envoyer le prochain ?
        //

        /*if (*((int *)(*lst_a)->next->content) == sorted[*next_index])
        {
            if ()
        }*/
        if (*((int *)(*lst_a)->next->content) == sorted[*next_index])
            swap(*lst_a, "sa\n");
        if (*((int *)(*lst_a)->content) == sorted[*next_index])
        {
            rotate(1, lst_a, "ra\n");
            (*next_index)++;
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
        split_b(lst_a, lst_b, sorted, next_index, len_b, verbose);
        real_qs_lst(lst_a, lst_b, sorted, next_index, len_b, lst_halves, verbose);
        send_in_b(lst_a, lst_b, ft_pop_value(lst_halves), sorted, next_index, len_b, verbose);
        real_qs_lst(lst_a, lst_b, sorted, next_index, len_b, lst_halves, verbose);
    }
    else
    {
        sort_batch(lst_a, lst_b, sorted, &nb_instruct, next_index, len_b, verbose);
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
        /*debug(lst_a, lst_b);
        printf("\n");*/
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
	int     i;
	t_list  *lst_a;
	t_list	*lst_b;
	int     *sorted;
	int     tmp;
	int		res;
    int     len;
    int     j;
    int     verbose;

	i = 1;
	res = 1;
    lst_b = NULL;
    lst_a = NULL;

    //int test = *((int *)content);
    /*int nb = 12;
    ft_lstappend(&lst_a, ft_lstnew(&nb, sizeof(nb)));
    nb = 13;
    ft_lstappend(&lst_a, ft_lstnew(&nb, sizeof(nb)));
    printf("%i\n", *((int *)lst_a->content));
    printf("%i\n", *((int *)lst_a->next->content));
    swap(lst_a);
    printf("%i\n", *((int *)lst_a->content));
    printf("%i\n", *((int *)lst_a->next->content));
    exit(1);*/

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
			ft_lstappend(&lst_a, ft_lstnew(&tmp, sizeof(tmp)));
		}
		quicksort(sorted, i - 1);
        len = i - 1;
        j = 0;
		get_instruct(&lst_a, &lst_b, sorted, len, verbose);
		while (lst_a)
		{
			printf("%i ", *((int *)lst_a->content));
			lst_a = lst_a->next;
		}
		printf("\n");
        printf("nb_instruct : %i\n", nb_instruct);
    }
	return (0);    
}