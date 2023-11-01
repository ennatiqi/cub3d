/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:14:12 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/01 17:04:06 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_newline_ext(t_game *game, char *tmp, int *i, char **map)
{
	while (*i < game->cub->lines - 1)
	{
		free(tmp);
		tmp = ft_strtrim(map[(*i)], " ");
		if (tmp[0] != '\n') 
		{
			free(tmp);
			error("AN ERROR OCCURED\n", game);
		}
		(*i)++;
	}
}

void	check_newline(char **map, t_cub *cub, t_game *game)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i])
	{
		tmp = ft_strtrim(map[i], " ");
		if (tmp[0] != '\n' && j > 0)
		{
			free(tmp);
			error("AN ERROR OCCURED\n", game);
		}
		if (tmp[0] == '\n')
		{
			j++;
			check_newline_ext(game, tmp, &i, map);
		}
		free(tmp);
		i++;
	}
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
