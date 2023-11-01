/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:19:23 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/01 10:58:20 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_toint_check_ext(char *str, int res, int *i, t_game *game)
{
	long	new_res;

	new_res = res;
	while (str[*i])
	{
		new_res = new_res * 10 + str[*i] - '0';
		if (!(str[*i] >= '0' && str[*i] <= '9') || new_res > INT32_MAX)
			error("ERROR IN THE COLORS\n", game);
		(*i)++;
	}
	return (new_res);
}

int	ft_toint_check(char *str, t_game *game)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32)
		i++;
	if (str[i + 1] && str[i] == '+')
		i++;
	res = ft_toint_check_ext(str, res, &i, game);
	return (res * sign);
}

int	counter(const char *s, char c)
{
	int	word;
	int	i;

	word = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			word++;
		while (s[i] && c != s[i])
			i++;
	}
	return (word);
}

void	comma_calcu(char *str, t_game *game)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i])
	{
		if (str[i] == ',')
			check++;
		i++;
	}
	if (check > 2)
		error("COMMA ',' ERROR\n", game);
}

void	check_c_f_ext(t_cub *cub, char **c_str, char **f_str, t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		cub->c_color[i] = ft_toint_check(c_str[i], game);
		if (cub->c_color[i] > 255 || cub->c_color[i] < 0)
			error("COLOR RANGE NOT RESPECTED\n", game);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		cub->f_color[i] = ft_toint_check(f_str[i], game);
		if (cub->f_color[i] > 255 || cub->f_color[i] < 0)
			error("COLOR RANGE NOT RESPECTED\n", game);
		i++;
	}
	cub->c_color[3] = 255;
	cub->f_color[3] = 255;
}

void	check_c_f(t_cub	*cub, t_game *game)
{
	char	**c_str;
	char	**f_str;
	int		i;

	if (!cub->C || !cub->F)
		error("ERROR IN THE COLOR\n", game);
	comma_calcu(cub->C, game);
	comma_calcu(cub->F, game);
	if (counter(cub->C, ',') != 3 || counter(cub->F, ',') != 3)
		error("ERROR IN THE COLOR\n", game);
	cub->c_color = malloc(sizeof(int) * 4);
	cub->f_color = malloc(sizeof(int) * 4);
	c_str = ft_split(cub->C, ',');
	f_str = ft_split(cub->F, ',');
	check_c_f_ext(cub, c_str, f_str, game);
	i = 0;
	while (i < counter(cub->C, ','))
		free(c_str[i++]);
	free(c_str);
	i = 0;
	while (i < counter(cub->C, ','))
		free(f_str[i++]);
	free(f_str);
}

void error(char *str, t_game *game)
{
	while (*str)
		write(2, str++, 1);
	to_free(game);
	// system("leaks cub3D");
	exit (1);
}

void	check_mid_ext(char **map, t_game *game, int i, size_t j)
{
	if (map[i][j] == '0' && map[i][j + 1] != '0' && \
	map[i][j + 1] != '1' && map[i][j + 1] != game->cub->start_p)
		error("NOT A VALID MAP\n", game);
	if (j > 0 && map[i][j] == '0' && (map[i][j - 1] != '0' && \
	map[i][j - 1] != '1' && map[i][j - 1] != game->cub->start_p))
		error("NOT A VALID MAP\n", game);
	if ((map[i][j] == '0' || map[i][j] == game->cub->start_p))
	{
		if (i == game->cub->lines)
			error("NOT A VALID MAP\n", game);
		if (j > ft_strlen(map[i + 1]))
			error("NOT A VALID MAP\n", game);
		if (map[i + 1][j] == 32 || map[i + 1][j] == '\n')
			error("NOT A VALID MAP\n", game);
	}
	if (i - 1 < (game->cub->lines) && (map[i][j] == '0' \
	|| map[i][j] == game->cub->start_p) && (map[i - 1][j] == 32 \
	|| map[i - 1][j] == '\n' || !map[i - 1][j] \
	|| j > ft_strlen(map[i - 1])))
		error("NOT A VALID MAP\n", game);
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

void	check_first_line(char **map, t_cub *cub, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void)cub;
	(void)map;
	while (map[0][j])
	{
		if (map[i][j] && (map[i][j] == '1' &&\
		 (map[i][j + 1] == '0' || map[i][j + 1] == cub->start_p)))
			error("NOT A VALID MAP FIRST LINE\n", game);
		j++;
	}
}

int	name_check(char *name)
{
	int		j;

	j = ft_strlen(name) - 4;
	if (name[j] == '.' && name[j + 1] == 'c' && \
	name[j + 2] == 'u' && name[j + 3] == 'b')
		return (1);
	else
		printf("YOUR MAP DOENS'T END WHITH '.cub'\n");
	return (0);
}
