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

void	swap(t_lst_inf *lst_inf, char *to_print, t_param param)
{
	int	tmp;

	if (ft_strchr(to_print, 'a') && lst_inf->lst_a && lst_inf->lst_a->next)
	{
		tmp = *(int *)lst_inf->lst_a->next->content;
		*((int *)lst_inf->lst_a->next->content) = get_int(lst_inf, 'a');
		*((int *)lst_inf->lst_a->content) = tmp;
	}
	else if (lst_inf->lst_a && lst_inf->lst_a->next)
	{
		tmp = *(int *)lst_inf->lst_b->next->content;
		*((int *)lst_inf->lst_b->next->content) = get_int(lst_inf, 'b');
		*((int *)lst_inf->lst_b->content) = tmp;
	}
	if (!param.silent)
		ft_printf("%s", to_print);
	if (param.verbose)
		show_state(lst_inf, param, to_print);
}

void	swap_both(t_lst_inf *lst_inf, char *to_print, t_param param)
{
	int old_silent;
	int old_verbose;

	old_silent = param.silent;
	old_verbose = param.verbose;
	param.silent = 1;
	param.verbose = 0;
	swap(lst_inf, "a\n", param);
	swap(lst_inf, "b\n", param);
	param.silent = old_silent;
	param.verbose = old_verbose;
	if (!param.silent)
		ft_printf("%s", to_print);
	if (param.verbose)
		show_state(lst_inf, param, to_print);
}

void	push(t_lst_inf *lst_inf, char *to_print, t_param param)
{
	t_list *new;

	if (ft_strchr(to_print, 'a') && lst_inf->lst_b)
	{
		new = ft_pop(&lst_inf->lst_b);
		ft_lstadd(&lst_inf->lst_a, new);
		lst_inf->len_b--;
	}
	else if (lst_inf->lst_a)
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

void	rotate(int up, t_lst_inf *lst_inf, char *to_print, t_param param)
{
	t_list	*first;
	t_list	*last;
	t_list	*lst;

	if (ft_strchr(to_print, 'a'))
		lst = lst_inf->lst_a;
	else
		lst = lst_inf->lst_b;
	first = lst;
	if (up)
	{
		if (ft_strchr(to_print, 'a'))
			lst_inf->lst_a = lst_inf->lst_a->next;
		else
			lst_inf->lst_b = lst_inf->lst_b->next;
		while (lst->next)
			lst = lst->next;
		lst->next = first;
		first->next = NULL;
	}
	else
	{
		while (lst->next->next->next)
			lst = lst->next;
		last = lst->next->next;
		lst->next->next = NULL;
		last->next = first;
		
		if (ft_strchr(to_print, 'a'))
			lst_inf->lst_a = last;
		else
			lst_inf->lst_b = last;
	}
	if (!param.silent)
		ft_printf("%s", to_print);
	if (param.verbose)
		show_state(lst_inf, param, to_print);
}

void	rotate_both(int up, t_lst_inf *lst_inf, char *to_print, t_param param)
{
	int old_silent;
	int old_verbose;

	old_silent = param.silent;
	old_verbose = param.verbose;
	param.silent = 1;
	param.verbose = 0;
	rotate(up, lst_inf, "a\n", param);
	rotate(up, lst_inf, "b\n", param);
	param.silent = old_silent;
	param.verbose = old_verbose;
	if (!param.silent)
		ft_printf("%s", to_print);
	if (param.verbose)
		show_state(lst_inf, param, to_print);
}
