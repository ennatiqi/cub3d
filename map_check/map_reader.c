/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:19:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/01 12:28:17 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

char **buff_map(char **map, t_cub *cub)
{
	int		i;
	char	**new_map;
	int		width = width_calc(map) - 1;
	char	*str;

	i = 0;
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
	free(str);
	buff_map_ext(map, new_map, cub);
	// i = 0;
	// while (i <= cub->lines)
	// {
	// 	int j = 0;
	// 	while (map[i][j] && map[i][j] != '\n')
	// 	{
	// 		if (map[i][j] != 32)
	// 			new_map[i][j] = map[i][j];
	// 		j++;
	// 	}
	// 	i++;
	// }
	return (new_map);
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

int	read_first_part(t_game *game, int fd, int lines)
{
	char **str;
	int	i;

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
			map[(*i)++] = tmp_1;
			free(tmp);
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
	// char	*tmp;
	// char	*tmp_1;
	int		fd;
	int		i;
	int		lines;
	int		j;

	i = 0;
	lines = maplines(mapber);
	fd = open(mapber, O_RDONLY);
	i = read_first_part(game, fd, lines);
	// str = malloc((lines + 1) * sizeof(char *));
	// if (!str)
	// 	return (NULL);
	// while (1)
	// {
	// 	str[i] = get_next_line(fd);
	// 	if (str[i] == NULL)
	// 		error("ERROR ON THE INPUT\n", game);
	// 	if (check_for_map(str[i], cub, game) == 0)
	// 	{
	// 		free(str[i]);
	// 		break ;
	// 	}
	// 	free(str[i]);
	// 	i++;
	// }
	// free(str);
	// if (cub->check_tex != 6)
	// 	error("INPUT ERROR (TEXTURES)\n", game);
	lines = lines - i - 3;
	
	i = 0;
	map = malloc((lines + 3) * sizeof(char *));
	j = read_middle_part(map, game, fd, &i);
	
	// map = malloc((lines + 3) * sizeof(char *));
	// i = 0;
	// j = 0;
	// while (1)
	// {
	// 	tmp_1 = get_next_line(fd);
	// 	tmp = ft_strtrim(tmp_1, " ");
	// 	if (tmp == NULL)
	// 	{
	// 		free(tmp_1);
	// 		free(tmp);
	// 		error("ERROR ON THE INPUT AFTER TEXTURES\n", game);
	// 	}
	// 	if (tmp[0] != '\n')
	// 	{
	// 		map[i++] = tmp_1;
	// 		free(tmp);
	// 		break ;
	// 	}
	// 	free(tmp_1);
	// 	free(tmp);
	// 	j++;
	// }

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
