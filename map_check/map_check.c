/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:19:23 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/01 14:20:33 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void error(char *str, t_game *game)
{
	while (*str)
		write(2, str++, 1);
	to_free(game);
	system("leaks cub3D");
	exit (1);
}

void	check_mid_ext(char **map, t_game *game, int i, size_t j)
{
	if (map[i][j] == '0' && map[i][j + 1] != '0' && \
	map[i][j + 1] != '1' && map[i][j + 1] != game->cub->start_p)
		error("NOT A VALID MAP >>\n", game);
	if (j > 0 && map[i][j] == '0' && (map[i][j - 1] != '0' && \
	map[i][j - 1] != '1' && map[i][j - 1] != game->cub->start_p))
		error("NOT A VALID MAP <<\n", game);
	if ((map[i][j] == '0' || map[i][j] == game->cub->start_p))
	{
		// TODO the (+1) was added recently and should be reviewed
		if (i == game->cub->lines + 1)
			error("NOT A VALID MAP 1\n", game);
		if (j > ft_strlen(map[i + 1]))
			error("NOT A VALID MAP 2\n", game);
		if (map[i + 1][j] == 32 || map[i + 1][j] == '\n')
			error("NOT A VALID MAP 3\n", game);
	}
	if (i - 1 < (game->cub->lines) && (map[i][j] == '0' \
	|| map[i][j] == game->cub->start_p) && (map[i - 1][j] == 32 \
	|| map[i - 1][j] == '\n' || !map[i - 1][j] \
	|| j > ft_strlen(map[i - 1])))
		error("NOT A VALID MAP ^\n", game);
}

void	check_mid(char **map, t_game *game)
{
	int		i;
	size_t	j;

	i = 1;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			check_mid_ext(map, game, i, j);
			j++;
		}
		i++;
	}
}

void check_component_ext(char **map, t_game *game, int i, int j)
{
	if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' \
	|| map[i][j] == 'W')
	{
		game->cub->start_p = map[i][j];
		game->cub->y = i;
		game->cub->x = j;
		game->cub->check++;
	}
	if (map[i][j] != 32 && map[i][j] != '\n' && map[i][j] != '0' \
	&& map[i][j] != '1' && map[i][j] != game->cub->start_p)
		error("UNKNOWN CHARACTER\n", game);
}

void	check_component(char **map, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->cub->check = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			check_component_ext(map, game, i, j);
			j++;
		}
		i++;
	}
	if (game->cub->check != 1)
		error("ERROR ON THE SPAWNING\n", game);
}
