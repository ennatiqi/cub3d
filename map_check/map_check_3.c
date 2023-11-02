/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:17:18 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/01 14:21:12 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		if (map[i][j] && (map[i][j] == '1' && \
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
	{
		printf("YOUR MAP DOENS'T END WHITH '.cub'\n");
		exit(0);
	}
	return (0);
}
