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

	up = -1;
	//LES PRINTS SONT COMPLETEMENT FAUX !!!!
	instruction = malloc(sizeof(char *)); //proteger
	while (get_next_line(0, instruction, '\n'))
	{
		if (ft_strnstr(instruction[0], "rr", 2) && ft_strlen(instruction[0]) > 2)
			up = 0;
		else if (ft_strchr(instruction[0], 'r'))
			up = 1;
		if (ft_strcmp(instruction[0], "sa") == 0 || ft_strcmp(instruction[0], "ss") == 0 || ft_strcmp(instruction[0], "sb") == 0)
		{
			if (!ft_strchr(instruction[0], 'a'))
				swap(lst_inf, "sa\n", param);
			if (!ft_strchr(instruction[0], 'b'))
				swap(lst_inf, "sb\n", param);
		}
		else if (up > -1)
		{
			if (!ft_strchr(instruction[0], 'a'))
				rotate(up, lst_inf, "ra\n", param);
			if (!ft_strchr(instruction[0], 'b'))
				rotate(up, lst_inf, "rb\n", param);
		}
		else if (ft_strcmp(instruction[0], "pa") == 0)
			push(lst_inf, "pa\n", param);
		else if (ft_strcmp(instruction[0], "pb") == 0)
			push(lst_inf, "pb\n", param);
		else
			return (0); //on dirait qu'il passe une fois de trop dans get_next_line et du coup 1 fois dans error
		up = -1;
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_list	*tmp_lst;
	int		is_sorted;
	t_lst_inf	lst_inf;
	t_tab_inf	tab_inf;
	t_param		param;

	//gestion des doublons ?

	lst_inf.lst_b = NULL;
	lst_inf.lst_a = NULL;
	is_sorted = 1;
	if (valid_input(argc, argv, &tab_inf, &lst_inf.lst_a, &param))
	{
		if (switch_op(&lst_inf, param))
		{
			if (!lst_inf.lst_b)
			{
				tmp_lst = lst_inf.lst_a;
				while (tmp_lst->next && is_sorted)
				{
					if (*((int *)tmp_lst->content) > *((int *)tmp_lst->next->content))
						is_sorted = 0;
					tmp_lst = tmp_lst->next;
				}
			}
			if (lst_inf.lst_b || !tab_inf.sorted)	
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
