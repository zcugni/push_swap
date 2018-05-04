/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:41:02 by zcugni            #+#    #+#             */
/*   Updated: 2018/02/02 17:41:03 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include "libft/libft.h"

typedef	struct			s_lst_inf
{
	t_list *lst_a;
    t_list *lst_b;
    int     len_b;
}						t_lst_inf;

typedef struct          s_tab_inf
{
    int     *sorted;
    int     sorted_len;
    int     next_index;
}                       t_tab_inf;

t_list	*ft_pop(t_list **lst);
int		ft_pop_value(t_list **lst);

void	swap(t_list *lst, char *to_print);
void	swap_both(t_list *lst_a, t_list *lst_b, char *to_print);
void	push(t_list **lst_receiver, t_list **lst_giver, char *to_print);
void	rotate(int up, t_list **lst, char *to_print);
void	rotate_both(int up, t_list **lst_a, t_list **lst_b, char *to_print);

int 	quicksort(int *arr, int len);
int		abs(int nb);
void    debug(t_lst_inf *lst_inf);

void	sort_batch(t_lst_inf *lst_inf, t_tab_inf *tab_inf, int *nb_instruct, int verbose);
void	little_list(t_lst_inf *lst_inf, t_tab_inf *tab_inf, int *nb_instruct);

int     valid_input(int argc, char **argv, t_tab_inf *tab_inf, t_list **lst_a, int *verbose, int *color);
int     display_error();

void    split_b(t_lst_inf *lst_inf, t_tab_inf *tab_inf, int verbose, int *nb_instruct);
void    send_half(t_lst_inf *lst_inf, t_tab_inf *tab_inf, int pivot_min, int nb_to_send, int verbose, int *nb_instruct);
void    send_in_b(t_lst_inf *lst_inf, int diff, t_tab_inf *tab_inf, int verbose, int *nb_instruct);

void    get_instruct(t_lst_inf *lst_inf, t_tab_inf *tab_inf, int verbose);
#endif
