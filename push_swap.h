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

typedef struct	s_g_list
{
	void	*content;
    size_t	content_size;
    struct s_g_list   *next;
}				t_g_list;

typedef struct	s_path_dist
{
	t_g_list	*instruct;
    int			dist;
	t_g_list	*state;
}				t_path_dist;

typedef struct	s_list
{
	int				nb; //pointeur ?
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(int nb);
void			ft_lstappend(t_list **alst, t_list *new);
void			ft_lstadd(t_list **alst, t_list *new);
int				ft_lstfind_i(t_list *lst, int nb);
t_list			*ft_pop(t_list **lst);
void			swap(t_list *lst);
void			push(t_list **lst_x, t_list **lst_y);
void			rotate(int up, t_list **lst);
void			quicksort(int *arr, int len);
int				abs(int nb);

t_list			*ft_lstcpy(t_list *ori);
int    			lst_length(t_list *lst);
void    		debug(t_list **lst_a, t_list **lst_b, int show);
void			define_direction(t_list **lst_b, int *sorted, int pivot_min, int last);
void			sort_batch(t_list **lst_a, t_list **lst_b, int *sorted, int *nb_instruct, int *next_index, int *len_b, int verbose, int *nb_ra, int *nb_sb, int *nb_rrb, int *nb_pa_2, int *nb_rr, int *nb_rb);
#endif
