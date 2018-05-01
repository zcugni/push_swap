/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 12:13:48 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/27 12:13:50 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	if_return(char **rest, char **line, int index)
{
	*line = ft_strndup(*rest, index);
	if (index == (int)ft_strlen(*rest) - 1)
		ft_strdel(rest);
	else
		ft_memmove(*rest, &((*rest)[index + 1]),
				ft_strlen(&((*rest)[index + 1])) + 1);
	return (1);
}

static void	update_line(char **line, char **rest)
{
	*line = ft_strdup(*rest);
	ft_strdel(rest);
}

char		*ft_strjoin_overlap(char **s1, char **s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!*s1 || !*s2)
		return (NULL);
	i = 0;
	str = malloc(ft_strlen(*s1) + ft_strlen(*s2) + 1);
	if (!str)
		return (NULL);
	while (i < ft_strlen(*s1))
	{
		str[i] = (*s1)[i];
		i++;
	}
	ft_strdel(s1);
	j = 0;
	while (j < ft_strlen(*s2))
	{
		str[i + j] = (*s2)[j];
		j++;
	}
	str[i + j] = '\0';
	ft_strdel(s2);
	return (str);
}

int			get_next_line(const int fd, char **line)
{
	static char *rest = NULL;
	char		*buff;
	int			state;
	int			index;

	while (1)
	{
		rest = (rest == NULL ? ft_strnew(0) : rest);
		if ((index = ft_strchri(rest, '\n')) == -1)
		{
			buff = ft_strnew(BUFF_SIZE + 1);
			if ((state = read(fd, buff, BUFF_SIZE)) == 0)
			{
				if (!rest[0])
					return (0);
				update_line(line, &rest);
				return (1);
			}
			else if (state == -1)
				return (state);
			rest = ft_strjoin_overlap(&rest, &buff);
		}
		else
			return (if_return(&rest, line, index));
	}
}
