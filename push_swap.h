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

t_list	*ft_pop(t_list **lst);
int		ft_pop_value(t_list **lst);

void	swap(t_list *lst, char *to_print);
void	push(t_list **lst_receiver, t_list **lst_giver, char *to_print);
void	rotate(int up, t_list **lst, char *to_print);
void	rotate_both(int up, t_list **lst_a, t_list **lst_b, char *to_print);
int 	quicksort(int *arr, int len);
int		abs(int nb);
int		ft_lstfind_i(t_list *lst, int nb);

void    debug(t_list **lst_a, t_list **lst_b);
void	sort_batch(t_list **lst_a, t_list **lst_b, int *sorted, int *nb_instruct, int *next_index, int *len_b, int verbose);
void    define_direction(t_list **lst_b, int pivot_min, int desired, int len_b);

void	little_list(t_list **lst_a, t_list **lst_b, int *sorted, int len, int *nb_instruct);
int     valid_input(int argc, char **argv, int **sorted, int *sorted_len, t_list **lst_a, int *verbose, int *color);
int    display_error();
#endif
