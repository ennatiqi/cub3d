/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:19:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/02 12:57:30 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	read_first_part(t_game *game, int fd, int lines)
{
	char	**str;
	int		i;

	i = 0;
	str = malloc((lines + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (1)
	{
		str[i] = get_next_line(fd);
		if (str[i] == NULL)
			error("ERROR ON THE INPUT\n", game);
		if (check_for_map(str[i], game->cub, game) == 0)
		{
			free(str[i]);
			break ;
		}
		free(str[i]);
		i++;
	}
	free(str);
	if (game->cub->check_tex != 6)
		error("INPUT ERROR (TEXTURES)\n", game);
	return (i);
}

int	read_middle_part(char **map, t_game *game, int fd, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp_1;

	j = 0;
	while (1)
	{
		tmp_1 = get_next_line(fd);
		tmp = ft_strtrim(tmp_1, " ");
		if (tmp == NULL)
		{
			free(tmp_1);
			free(tmp);
			error("ERROR ON THE INPUT AFTER TEXTURES\n", game);
		}
		if (tmp[0] != '\n')
		{
			free(tmp);
			map[(*i)++] = tmp_1;
			break ;
		}
		free(tmp_1);
		free(tmp);
		j++;
	}
	return (j);
}

char	**just_map(char *mapber, t_cub *cub, t_game *game)
{
	char	**map;
	int		fd;
	int		i;
	int		lines;
	int		j;

	i = 0;
	lines = maplines(mapber);
	fd = open(mapber, O_RDONLY);
	i = read_first_part(game, fd, lines);
	lines = lines - i - 3;
	i = 0;
	map = malloc((lines + 3) * sizeof(char *));
	j = read_middle_part(map, game, fd, &i);
	cub->lines = lines - j;
	while (1)
	{
		map[i] = get_next_line(fd);
		if (map[i] == NULL)
			break ;
		i++;
	}
	close(fd);
	return (map);
}
