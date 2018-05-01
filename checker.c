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

int	switch_op(t_list **lst_a, t_list **lst_b)
{
	char    **instruction;
	int     up;

	up = -1;
	instruction = malloc(sizeof(char *)); //proteger
	while (get_next_line(0, instruction))
	{
		if (ft_strnstr(instruction[0], "rr", 2) && ft_strlen(instruction[0]) > 2)
			up = 0;
		else if (ft_strchr(instruction[0], 'r'))
			up = 1;
		if (ft_strcmp(instruction[0], "sa") == 0 || ft_strcmp(instruction[0], "ss") == 0 || ft_strcmp(instruction[0], "sb") == 0)
		{
			if (!ft_strchr(instruction[0], 'a'))
				swap(*lst_b, ""); //je suis pas sure que ca marche sans rien afficher en vrai
			if (!ft_strchr(instruction[0], 'b'))
				swap(*lst_a, "");
		}
		else if (up > -1)
		{
			if (!ft_strchr(instruction[0], 'a'))
				rotate(up, lst_b, "");
			if (!ft_strchr(instruction[0], 'b'))
				rotate(up, lst_a, "");
		}
		else if (ft_strcmp(instruction[0], "pa") == 0)
			push(lst_a, lst_b, "");
		else if (ft_strcmp(instruction[0], "pb") == 0)
			push(lst_b, lst_a, "");
		else
			return (0); //on dirait qu'il passe une fois de trop dans get_next_line et du coup 1 fois dans error
		up = -1;
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_list  *lst_a;
	t_list  *lst_b;
	t_list	*tmp_lst;
	int		is_sorted;
	int		*sorted;
	int		verbose;
	int		color;
	int		sorted_len;

	//gestion des doublons ?

	lst_b = NULL;
	lst_a = NULL;
	sorted = NULL;
	is_sorted = 1;
	if (valid_input(argc, argv, &sorted, &sorted_len, &lst_a, &verbose, &color))
	{
		if (switch_op(&lst_a, &lst_b))
		{
			if (!lst_b)
			{
				tmp_lst = lst_a;
				while (tmp_lst->next && is_sorted)
				{
					if (*((int *)tmp_lst->content) > *((int *)tmp_lst->next->content))
						is_sorted = 0;
					tmp_lst = tmp_lst->next;
				}
			}
			if (lst_b || !sorted)	
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
