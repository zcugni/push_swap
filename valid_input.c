/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 11:37:55 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/06 11:37:57 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		read_file(int fd, t_tab_inf *tab_inf, t_list **lst_a)
{
	char	**arg;
	int		i;
	int		tmp_nb;
	int		res;

	arg = malloc(sizeof(char *));
	if (!arg)
		return (0);
	i = 0;
	while ((res = get_next_line(fd, arg, ' ')))
	{
		if (res == -1)
			return (0);
		if (is_int(*arg))
		{
			tmp_nb = ft_atoi(*arg);
			ft_lstappend(lst_a, ft_lstnew(&tmp_nb, sizeof(tmp_nb)));
		}
		else
			return (0);
		ft_strdel(arg);
		i++;
	}
	close(fd);
	free(arg);
	tab_inf->sorted_len = i;
	return (1);
}

static int		read_args(char **argv, t_tab_inf *tab_inf, t_list **lst_a)
{
	int i;
	int tmp_nb;

	i = 0;
	while (argv[i])
	{
		if (is_int(argv[i]))
		{
			tmp_nb = ft_atoi(argv[i]);
			ft_lstappend(lst_a, ft_lstnew(&tmp_nb, sizeof(tmp_nb)));
		}
		else
			return (0);
		i++;
	}
	tab_inf->sorted_len = i;
	return (1);
}

int				init_param(int argc, char **argv, t_param *param, int *first_nb)
{
	int i;

	i = 1;
	param->verbose = 0;
	param->full = 0;
	param->silent = 0;
	param->color = 0;
	while (argv[i] && argv[i][0] == '-' && ft_isalpha(argv[i][1]))
	{
		if (ft_strcmp(argv[i], "-v") == 0)
			param->verbose = 1;
		if (ft_strcmp(argv[i], "-c") == 0)
			param->color = 1;
		if (ft_strcmp(argv[i], "-f") == 0)
			param->full = 1;
		i++;
	}
	i = param->verbose + param->color + param->full + 1;
	*first_nb = i;
	if (argc <= i)
		return (0);
	return (1);
}

int				valid_input(int first_nb, char **argv, t_tab_inf *tab_inf, t_list **lst_a)
{
	int		fd;
	int		i;
	int		state;
	t_list	*tmp_lst;

	fd = open(argv[first_nb], O_RDONLY);
	if (!is_int(argv[first_nb]) && fd == -1)
		return (0);
	else if (!is_int(argv[first_nb]))
		state = read_file(fd, tab_inf, lst_a);
	else
		state = read_args(&(argv[first_nb]), tab_inf, lst_a);
	if (!state)
		return (0);
	tab_inf->sorted = malloc(tab_inf->sorted_len * sizeof(int));
	if (!tab_inf->sorted)
		return (0);
	i = 0;
	tmp_lst = *lst_a;
	while (i < tab_inf->sorted_len)
	{
		tab_inf->sorted[i] = *((int *)tmp_lst->content);
		i++;
		tmp_lst = tmp_lst->next;
	}
	return (quicksort(tab_inf->sorted, tab_inf->sorted_len));
}
