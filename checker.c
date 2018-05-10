/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:21:23 by zcugni            #+#    #+#             */
/*   Updated: 2018/01/24 16:21:25 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	switch_op(t_lst_inf *lst_inf, t_param param)
{
	char	**inst;

	inst = malloc(sizeof(char *));
	if (!inst)
		return (0);
	while (get_next_line(0, inst, '\n'))
	{
		if (inst && *inst)
		{
			if ((!ft_strcmp(inst[0], "sa") || !ft_strcmp(inst[0], "sb")
												|| !ft_strcmp(inst[0], "ss")))
				swap(lst_inf, ft_strjoin_free(inst[0], "\n", 0), param);
			else if ((!ft_strcmp(inst[0], "rra") || !ft_strcmp(inst[0], "rrb")
				|| !ft_strcmp(inst[0], "rrr") || !ft_strcmp(inst[0], "ra") ||
						!ft_strcmp(inst[0], "rb") || !ft_strcmp(inst[0], "rr")))
				rotate(lst_inf, ft_strjoin_free(inst[0], "\n", 0), param);
			else if (!ft_strcmp(inst[0], "pa") || !ft_strcmp(inst[0], "pb"))
				push(lst_inf, ft_strjoin_free(inst[0], "\n", 0), param);
			else
				return (0);
		}
		else
			return (0);
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_lst_inf	lst_inf;
	t_tab_inf	tab_inf;
	t_param		param;
	int			first_nb_i;
	int			status_ok;

	lst_inf.lst_b = NULL;
	lst_inf.lst_a = NULL;
	if (argc == 1)
		return (0);
	if (!init_param(argc, argv, &param, &first_nb_i))
		return (display_error());
	param.silent = 1;
	if ((status_ok = valid_input(first_nb_i, argv, &tab_inf, &lst_inf.lst_a)))
		if (!test_sorted(lst_inf.lst_a, 1))
			if ((status_ok = switch_op(&lst_inf, param)))
			{
				if (lst_inf.lst_b || !test_sorted(lst_inf.lst_a, 1))
					ft_putstr("KO\n");
				else
					ft_putstr("OK\n");
			}
	if (!status_ok)
		return (display_error());
	return (0);
}
