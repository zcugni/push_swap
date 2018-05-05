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
# include "fcntl.h"

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

typedef struct          s_param
{
    int     verbose;
    int     color;
    int     full;
    int     silent;
}                       t_param;

t_list	*ft_pop(t_list **lst);
int		ft_pop_value(t_list **lst);

void	swap(t_lst_inf *lst_inf, char *to_print, t_param param);
void	swap_both(t_lst_inf *lst_inf, char *to_print, t_param param);
void	push(t_lst_inf *lst_inf, char *to_print, t_param param);
void	rotate(int up, t_lst_inf *lst_inf, char *to_print, t_param param);
void	rotate_both(int up, t_lst_inf *lst_inf, char *to_print, t_param param);

int 	quicksort(int *arr, int len);
int		abs(int nb);
void    show_state(t_lst_inf *lst_inf, t_param param, char *last_op);
void	choose_rotate(t_lst_inf *lst_inf, t_tab_inf *tab_inf, int modifier, int *do_ra, int *i_rotate, t_param param);

void	sort_batch(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_param param, int *nb_instruct);
void	little_list(t_lst_inf *lst_inf, t_tab_inf *tab_inf, int *nb_instruct, t_param param);

int     valid_input(int argc, char **argv, t_tab_inf *tab_inf, t_list **lst_a, t_param *param);
int     display_error();

void    split_b(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_param param, int *nb_instruct);
void    send_half(t_lst_inf *lst_inf, t_tab_inf *tab_inf, int pivot_min, int nb_to_send, t_param param, int *nb_instruct);
void    send_in_b(t_lst_inf *lst_inf, int diff, t_tab_inf *tab_inf, t_param param, int *nb_instruct);

void    get_instruct(t_lst_inf *lst_inf, t_tab_inf *tab_inf, t_param param);

int get_desired(t_tab_inf *tab_inf);
int get_int(t_lst_inf *lst_inf, char lst_letter);
#endif
