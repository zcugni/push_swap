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

t_list  *find_pivot(int *sorted, int len)
{
    t_list *pivot_lst;

    pivot_lst = NULL;
    while (len > 5)
    {
        len /= 2;
        ft_lstappend(&pivot_lst, ft_lstnew(sorted[len - 1]));
    }
    return (pivot_lst);
}

void    debug(t_list **lst_a, t_list **lst_b)
{
    t_list *tmp_a;
    t_list *tmp_b;

    tmp_a = *lst_a;
    tmp_b = *lst_b;
    while (tmp_a)
	{
        printf("%i ", tmp_a ->nb);
        tmp_a  = tmp_a ->next;
	}
    printf("\n");
    while (tmp_b)
	{
        printf("%i ", tmp_b->nb);
        tmp_b = tmp_b->next;
	}
    printf("\n");
    //exit(1);
}

//je pourrais peut-etre l'appelee dans le principale au lieu de dans get_instruct
void    divide_lst(int pivot, t_list **lst_a, t_list **lst_b, int *sorted)
{
    int nb;

    while (pivot > 0)
    {
        nb = 0;
        if (!*lst_b)
        {
            while (nb < pivot)
            {
                //printf("nb, lst_a, sorted, pivot, lst_pivot : %i, %i, %i, %i, %i\n", nb, (*lst_a)->nb, sorted[pivot_lst->nb - 1], pivot_lst->nb - 1, last_pivot);
                if ((*lst_a)->nb <= sorted[pivot - 1]) // && (*lst_a)->nb > last_pivot
                {
                    push(lst_b, lst_a);
                    printf("pb\n");
                    nb++;
                }
                else
                {
                    rotate(1, lst_a);
                    printf("ra\n");
                }
            }
        }
        else
        {
            while (nb < pivot)
            {
                //printf("nb, lst_a, sorted, pivot, lst_pivot : %i, %i, %i, %i, %i\n", nb, (*lst_b)->nb, sorted[pivot_lst->nb - 1], pivot_lst->nb - 1, last_pivot);
                if ((*lst_b)->nb > sorted[pivot - 1] && (*lst_b)->nb <= sorted[pivot + 5 - 1])
                {
                    push(lst_a, lst_b);
                    printf("pa\n");
                    nb++;
                }
                else
                {
                    rotate(1, lst_b);
                    printf("rb\n");
                }
            }
        }
        pivot -= 5;
    }
}



void get_instruct(int length, t_list **lst_a, t_list **lst_b, int *sorted)
{
    int nb;
    int pivot_min;
    int pivot_max;

    int i = 0;
    int debug1;
    pivot = 5;
    while (i < 4) //sorted en vrai
    {
        debug1 = 0;
        divide_lst(length / 2, lst_a, lst_b, sorted);
        debug(lst_a, lst_b);
        printf("finish divide\n");
        nb = 0; //le pivot min d'avant
        
        while (*lst_b)
        {
            if ((*lst_b)->nb == sorted[pivot - nb - 1])
            {
                push(lst_a, lst_b);
                printf("pa\n");
                nb++;
            }
            else //ameliorer la logique
            {
                rotate(1, lst_b);
                printf("rb\n");
            }
            //debug(lst_a, lst_b);
            debug1++;
            if (debug1 > 15)
                exit(1);
        
        }
        debug(lst_a, lst_b);
        exit(1);
        i++;
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
	//int		nb_instruct = 0;
    int     len;
	int     j;

	i = 1;
	res = 1;
    lst_b = NULL;
	if (argc > 1)
	{
		sorted = malloc((argc - 1) * sizeof(int));
		while (argv[i])
		{
			tmp = ft_atoi(argv[i]);
			sorted[i - 1] = tmp;
			i++;
			ft_lstappend(&lst_a, ft_lstnew(tmp));
		}
		quicksort(sorted, i - 1);
        len = i - 1;
        j = 0;
        printf("len : %i\n", len);
		get_instruct(len, &lst_a, &lst_b, sorted);
        exit(1);
		while (lst_a)
		{
			printf("%i ", lst_a->nb);
			lst_a = lst_a->next;
		}
		printf("\n");
		printf("nb_instructs : %i\n", j - 1);
	}
	return (0);    
}

