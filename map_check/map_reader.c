/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:39:28 by aachfenn          #+#    #+#             */
/*   Updated: 2023/10/13 07:53:01 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	maplines(char *mapber)
{
	char	*str;
	int		fd;
	int		i;

	i = 0;
	fd = open(mapber, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		i++;
		free(str);
	}
	close(fd);
	return (i);
}

char	**mapreader(char *mapber)
{
	char	**str;
	int		fd;
	int		i;
	int		lines;

	i = 0;
	lines = maplines(mapber);
	fd = open(mapber, O_RDONLY);
	str = malloc((lines + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (1)
	{
		str[i] = get_next_line(fd);
		if (str[i] == NULL)
			break ;
		i++;
	}
	close(fd);
	return (str);
}
