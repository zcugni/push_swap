/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 21:52:13 by zcugni            #+#    #+#             */
/*   Updated: 2018/05/07 21:52:15 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_tab(int *arr, int index_1, int index_2)
{
	int tmp;

	tmp = arr[index_1];
	arr[index_1] = arr[index_2];
	arr[index_2] = tmp;
}

static int	sort_tab(int *arr, int len, int first_supp)
{
	if (first_supp == 0)
	{
		swap_tab(arr, first_supp, 1);
		if (!quicksort(arr, len))
			return (0);
	}
	else
	{
		swap_tab(arr, first_supp - 1, 0);
		if (!quicksort(arr, first_supp))
			return (0);
		if (!quicksort(&arr[first_supp], len - first_supp))
			return (0);
	}
	return (1);
}

int			quicksort(int *arr, int len)
{
	int i;
	int first_supp;

	i = 1;
	first_supp = 0;
	while (i < len)
	{
		if (arr[i] > arr[0] && first_supp == 0)
			first_supp = i;
		else if (arr[i] < arr[0] && first_supp != 0)
			swap_tab(arr, first_supp++, i);
		else if (arr[i] == arr[0])
			return (0);
		i++;
	}
	if (len > 1)
	{
		if (!sort_tab(arr, len, first_supp))
			return (0);
	}
	return (1);
}
