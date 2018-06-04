/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:58:30 by zcugni            #+#    #+#             */
/*   Updated: 2018/01/26 19:58:31 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		swap(t_lst_inf *lst_inf, char *to_print, t_param param)
{
	int	tmp;

	if (!ft_strchr(to_print, 'a') && lst_inf->lst_b && lst_inf->lst_b->next)
	{
		tmp = *(int *)lst_inf->lst_b->next->content;
		*((int *)lst_inf->lst_b->next->content) = get_int(lst_inf, 'b');
		*((int *)lst_inf->lst_b->content) = tmp;
	}
	if (!ft_strchr(to_print, 'b') && lst_inf->lst_a && lst_inf->lst_a->next)
	{
		tmp = *(int *)lst_inf->lst_a->next->content;
		*((int *)lst_inf->lst_a->next->content) = get_int(lst_inf, 'a');
		*((int *)lst_inf->lst_a->content) = tmp;
	}
	if (!param.silent)
		ft_printf("%s", to_print);
	if (param.verbose)
		show_state(lst_inf, param, to_print);
}

void		push(t_lst_inf *lst_inf, char *to_print, t_param param)
{
	t_list *new;

	new = NULL;
	if (ft_strchr(to_print, 'a') && lst_inf->lst_b)
	{
		new = ft_pop(&lst_inf->lst_b);
		ft_lstadd(&lst_inf->lst_a, new);
		lst_inf->len_b--;
	}
	else if (ft_strchr(to_print, 'b') && lst_inf->lst_a)
	{
		new = ft_pop(&lst_inf->lst_a);
		ft_lstadd(&lst_inf->lst_b, new);
		lst_inf->len_b++;
	}
	if (!param.silent)
		ft_printf("%s", to_print);
	if (param.verbose)
		show_state(lst_inf, param, to_print);
}

static void	rotate_up(t_lst_inf *lst_inf, char *to_print)
{
	t_list *first;
	t_list *tmp;

	if (!ft_strchr(to_print, 'a') && lst_inf->lst_b && lst_inf->lst_b->next)
	{
		tmp = lst_inf->lst_b;
		lst_inf->lst_b = lst_inf->lst_b->next;
		first = tmp;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = first;
		first->next = NULL;
	}
	if (!ft_strchr(to_print, 'b') && lst_inf->lst_a && lst_inf->lst_a->next)
	{
		tmp = lst_inf->lst_a;
		lst_inf->lst_a = lst_inf->lst_a->next;
		first = tmp;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = first;
		first->next = NULL;
	}
}

static void	rotate_down(t_lst_inf *lst_inf, char *to_print)
{
	t_list *last;
	t_list *tmp;

	if (!ft_strchr(to_print, 'a') && lst_inf->lst_b && lst_inf->lst_b->next)
	{
		tmp = lst_inf->lst_b;
		while (tmp->next->next)
			tmp = tmp->next;
		last = tmp->next;
		tmp->next = NULL;
		last->next = lst_inf->lst_b;
		lst_inf->lst_b = last;
	}
	if (!ft_strchr(to_print, 'b') && lst_inf->lst_a && lst_inf->lst_a->next)
	{
		tmp = lst_inf->lst_a;
		while (tmp->next->next)
			tmp = tmp->next;
		last = tmp->next;
		tmp->next = NULL;
		last->next = lst_inf->lst_a;
		lst_inf->lst_a = last;
	}
}

void		rotate(t_lst_inf *lst_inf, char *to_print, t_param param)
{
	if (ft_strstr(to_print, "rr") && ft_strlen(to_print) > 3)
		rotate_down(lst_inf, to_print);
	else
		rotate_up(lst_inf, to_print);
	if (!param.silent)
		ft_printf("%s", to_print);
	if (param.verbose)
		show_state(lst_inf, param, to_print);
}
