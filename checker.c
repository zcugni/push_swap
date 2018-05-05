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

# include "push_swap.h"

static int	switch_op(t_lst_inf *lst_inf, t_param param)
{
	char    **instruction;
	int     up;

	instruction = malloc(sizeof(char *));
	if (!instruction)
		return (0);
	while (get_next_line(0, instruction, '\n'))
	{
		if (ft_strnstr(instruction[0], "rr", 2) && ft_strlen(instruction[0]) > 2)
			up = 0;
		else if (ft_strchr(instruction[0], 'r'))
			up = 1;
		if (ft_strchr(instruction[0], 's') == 0)
			swap(lst_inf, ft_strjoin_free(instruction[0], "\n", 0), param);
		else if (ft_strchr(instruction[0], 'r'))
			rotate(up, lst_inf, ft_strjoin_free(instruction[0], "\n", 0), param);
		else if (ft_strchr(instruction[0], 'p') == 0)
			push(lst_inf,  ft_strjoin_free(instruction[0], "\n", 0), param);
		else
			return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_lst_inf	lst_inf;
	t_tab_inf	tab_inf;
	t_param		param;
	int			first_nb_i;

	lst_inf.lst_b = NULL;
	lst_inf.lst_a = NULL;
	//enlever la gestion des params de checker
	if(!init_param(argc, argv, &param, &first_nb_i))
        return (display_error());
	param.silent = 1;
	if (valid_input(first_nb_i, argv, &tab_inf, &lst_inf.lst_a))
	{
		if (switch_op(&lst_inf, param))
		{
			if (lst_inf.lst_b || !test_sorted(lst_inf.lst_a, 1))	
				ft_putstr("KO\n");
			else
				ft_putstr("OK\n");
		}
		else
			display_error();
	}
	else
		return (display_error());
	return (0);
}
