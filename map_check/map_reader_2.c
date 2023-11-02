/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:59:29 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/02 12:55:55 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**buff_map(char **map, t_cub *cub)
{
	int		i;
	char	**new_map;
	int		width;
	char	*str;

	i = 0;
	width = width_calc(map) - 1;
	str = malloc((width + 1) * sizeof(char));
	i = 0;
	while (i < width)
		str[i++] = '1';
	str[i] = '\0';
	new_map = malloc((cub->lines + 3) * sizeof(char *));
	i = 0;
	while (i <= cub->lines + 1)
	{
		new_map[i] = ft_strdup(str);
		i++;
	}
	new_map[i] = NULL;
	free(str);
	buff_map_ext(map, new_map, cub);
	return (new_map);
}

void	buff_map_ext(char **map, char **new_map, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i <= cub->lines)
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] != 32)
				new_map[i][j] = map[i][j];
			j++;
		}
		i++;
	}
}

int	width_calc(char **map)
{
	int		i;
	size_t len;

	i = 0;
	len = 0;
	while (map[i])
	{
		if (len < ft_strlen(map[i]))
			len = ft_strlen(map[i]);
		i++;
	}
	return (len);
}

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
