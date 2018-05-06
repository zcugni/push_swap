/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 10:52:52 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/06 10:52:53 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		show_lst(t_list *tmp_lst, int lst_len, t_param param, char last_op)
{
	int		nb_to_show;
	int		i;

	nb_to_show = 20;
	i = 0;
	if ((last_op == 'p' || last_op == 'u') && param.color)
		ft_printf("\033[32m_ \033[0m");
	while (tmp_lst)
	{
		if (i < nb_to_show || i >= lst_len - nb_to_show || param.full)
		{
			if (param.color &&
			((i == 0 && (last_op == 's' || last_op == 'r' || last_op == 'd')) ||
			(i == 1 && last_op == 's') ||
			(!tmp_lst->next && last_op == 'u')))
				ft_printf("\033[32m%i\033[0m ", *((int *)tmp_lst->content));
			else
				ft_printf("%i ", *((int *)tmp_lst->content));
		}
		if (i == nb_to_show && tmp_lst->next && !param.full)
			ft_printf("... ");
		tmp_lst = tmp_lst->next;
		i++;
	}
	if (param.color && last_op == 'd')
		ft_printf("\033[32m_\033[0m");
}

static	char	define_code(char *last_op, char letter)
{
	char code;

	code = ' ';
	if (ft_strcmp(last_op, "ss\n") == 0 ||
		(ft_strchr(last_op, 's') && ft_strchr(last_op, letter)))
		code = 's';
	else if (ft_strcmp(last_op, "rr\n") == 0 ||
		(ft_strchr(last_op, 'r') && ft_strchr(last_op, letter) && last_op[2] == '\n'))
		code = 'u';
	else if (ft_strcmp(last_op, "rrr\n") == 0 ||
		(ft_strchr(last_op, 'r') && ft_strchr(last_op, letter)))
		code = 'd';
	else if ((ft_strchr(last_op, 'p') && ft_strchr(last_op, letter)))
		code = 'r';
	else if ((ft_strchr(last_op, 'p') && !ft_strchr(last_op, letter)))
		code = 'p';
	return (code);
}

void			show_state(t_lst_inf *lst_inf, t_param param, char *last_op)
{
	int		len_a;

	ft_printf("A : ");
	len_a = ft_lstlength(lst_inf->lst_a); //a opti
	show_lst(lst_inf->lst_a, len_a, param, define_code(last_op, 'a'));
	ft_printf("\n");
	ft_printf("B : ");
	show_lst(lst_inf->lst_b, lst_inf->len_b, param, define_code(last_op, 'b'));
	ft_printf("\n");
	ft_printf("\n");
}

int				display_error(void)
{
	ft_putstr_fd("Error\n", 2);
	return (0);
}
