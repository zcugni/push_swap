/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:33:02 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/10 14:33:07 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	printf("n : %zu\n", n);
	if (n != 0)
	{
		str = malloc((n + 1) * sizeof(char));
		if (str != NULL)
		{
			while (i < n)
			{
				str[i] = s1[i];
				i++;
			}
			str[i] = '\0';
		}
	}
	else
		str = NULL;
	printf("str : %s\n", str);
	return (str);
}
