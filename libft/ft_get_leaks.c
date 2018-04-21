/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_leaks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:02:16 by zcugni            #+#    #+#             */
/*   Updated: 2018/03/21 16:02:19 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void    ft_get_leaks(char *msg)
{
    system("leaks push_swap");
    ft_putstr("\033[31m");
    ft_putstr(msg);
    ft_putstr("\033[0m");
    getchar();
}
