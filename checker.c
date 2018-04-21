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

void	display_state(t_list *lst_a, t_list *lst_b)
{
	t_list *tmp_a;
	t_list *tmp_b;

	tmp_a = lst_a;
	tmp_b = lst_b;
	ft_putstr("A : ");
	while (tmp_a)
	{
		ft_putnbr(tmp_a->nb);
		if (tmp_a->next)
				ft_putstr(" -> ");
		tmp_a = tmp_a->next;
	}
	ft_putstr("\nB : ");
	while (tmp_b)
	{
		ft_putnbr(tmp_b->nb);
		if (tmp_b->next)
			ft_putstr(" -> ");
		tmp_b = tmp_b->next;
	}
	ft_putstr("\n\n");
}

void	switch_op(t_list *lst_a, t_list *lst_b)
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
			if (ft_strchr(instruction[0], 'a') || ft_strcmp(instruction[0], "ss") == 0)
				swap(lst_a);
			if (ft_strchr(instruction[0], 'b') || ft_strcmp(instruction[0], "ss") == 0)
				swap(lst_b);
		}
		else if (up > -1)
		{
			if (!ft_strchr(instruction[0], 'a'))
				rotate(up, &lst_b);
			if (!ft_strchr(instruction[0], 'b'))
				rotate(up, &lst_a);
		}
		else if (ft_strcmp(instruction[0], "pa") == 0)
			push(&lst_a, &lst_b);
		else if (ft_strcmp(instruction[0], "pb") == 0)
			push(&lst_b, &lst_a);
		else
			ft_putstr_fd("Error\n", 2); //on dirait qu'il passe une fois de trop dans get_next_line et du coup 1 fois dans error
		display_state(lst_a, lst_b);
		up = -1;
	}
}

int main(int argc, char **argv)
{
	int     i;
	t_list  *lst_a;
	t_list  *lst_b;
	t_list	*tmp_lst;
	int		sorted;

	//gestion des doublons ?
	//Si push_swap ecrit error sur la sortie d'erreur, je devrais lire la-bas avant d'essayer de verifier les instructions non ?

	lst_b = NULL;
	sorted = 1;
	i = 1;
	if (argc > 1)
	{
		while (argv[i])
			ft_lstappend(&lst_a, ft_lstnew(ft_atoi(argv[i++])));
		switch_op(lst_a, lst_b);
		if (!lst_b)
		{
			tmp_lst = lst_a;
			while (tmp_lst->next && sorted)
			{
				if (tmp_lst->nb > tmp_lst->next->nb)
					sorted = 0;
				tmp_lst = tmp_lst->next;
			}
		}
		if (lst_b || !sorted)	
			ft_putstr("KO\n");
		else
			ft_putstr("OK\n");
	}
	return (0);
}
