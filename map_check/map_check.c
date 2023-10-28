/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:19:23 by aachfenn          #+#    #+#             */
/*   Updated: 2023/10/28 12:31:43 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_toint_check_ext(char *str, int res, int *i)
{
	long	new_res;

	new_res = res;
	while (str[*i])
	{
		new_res = new_res * 10 + str[*i] - '0';
		if (!(str[*i] >= '0' && str[*i] <= '9') || new_res > INT32_MAX)
			error("ERROR IN THE COLORS\n");
		(*i)++;
	}
	return (new_res);
}

int	ft_toint_check(char *str)
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
	res = ft_toint_check_ext(str, res, &i);
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

void	comma_calcu(char *str)
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
		error("COMMA ',' ERROR\n");
}

void	check_c_f_ext(t_cub *cub, char **c_str, char **f_str)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		cub->c_color[i] = ft_toint_check(c_str[i]);
		if (cub->c_color[i] > 255 || cub->c_color[i] < 0)
			error("COLOR RANGE NOT RESPECTED\n");
		i++;
	}
	i = 0;
	while (i < 3)
	{
		cub->f_color[i] = ft_toint_check(f_str[i]);
		if (cub->f_color[i] > 255 || cub->f_color[i] < 0)
			error("COLOR RANGE NOT RESPECTED\n");
		i++;
	}
	cub->c_color[3] = 255;
	cub->f_color[3] = 255;
}

void	check_c_f(t_cub	*cub)
{
	char	**c_str;
	char	**f_str;
	int		i;

	comma_calcu(cub->C);
	comma_calcu(cub->F);
	if (counter(cub->C, ',') != 3 || counter(cub->F, ',') != 3)
		error("ERROR IN THE COLOR\n");
	cub->c_color = malloc(sizeof(int) * 4);
	cub->f_color = malloc(sizeof(int) * 4);
	c_str = ft_split(cub->C, ',');
	f_str = ft_split(cub->F, ',');
	check_c_f_ext(cub, c_str, f_str);
	i = 0;
	while (i < counter(cub->C, ','))
		free(c_str[i++]);
	free(c_str);
	i = 0;
	while (i < counter(cub->C, ','))
		free(f_str[i++]);
	free(f_str);
}

void error(char *str)
{
	while (*str)
		write(2, str++, 1);
	exit (1);
}

void	check_mid(char **map, t_cub	*cub)
{
	int		i;
	size_t	j;

	i = 1;
	j = 0;
	(void)cub;
	printf("cub->lines = %d\n", cub->lines);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			// printf("map[%d][%zu] == '%c'\n", i, j, map[i][j]);
			if (map[i][j] == '0' && map[i][j + 1] != '0' && \
			map[i][j + 1] != '1' && map[i][j + 1] != cub->start_p)
				error("NOT A VALID MAP (j + 1)\n");
			if (j > 0 && map[i][j] == '0' && (map[i][j - 1] != '0' && \
			map[i][j - 1] != '1' && map[i][j - 1] != cub->start_p))
				error("NOT A VALID MAP (j - 1)\n");
			// if (i < (cub->lines - 1) && (map[i][j] == '0' || map[i][j] == cub->start_p) && \
			// (map[i + 1][j] == 32 || map[i + 1][j] == '\n' || !map[i + 1][j] || j > ft_strlen(map[i + 1])))
			// 	error("NOT A VALID MAP (i + 1)\n");
			if ((map[i][j] == '0' || map[i][j] == cub->start_p))
			{
				if (i == cub->lines)
					error("NOT A VALID MAP (i + 1)\n");
				if (j > ft_strlen(map[i + 1]))
					error("NOT A VALID MAP (i + 1)\n");
				if (map[i + 1][j] == 32 || map[i + 1][j] == '\n')
					error("NOT A VALID MAP (i + 1)\n");
			}
			if (i - 1 < (cub->lines) && (map[i][j] == '0' || map[i][j] == cub->start_p) && \
			(map[i - 1][j] == 32 || map[i - 1][j] == '\n' || !map[i - 1][j] || j > ft_strlen(map[i - 1])))
				error("NOT A VALID MAP (i - 1)\n");
			j++;
		}
		i++;
	}
}

void	check_component(char **map, t_cub *cub)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	check = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' \
			|| map[i][j] == 'W')
			{
				cub->start_p = map[i][j];
				cub->x = i;
				cub->y = j;
				check++;
			}
			if (map[i][j] != 32 && map[i][j] != '\n' && map[i][j] != '0' \
			&& map[i][j] != '1' && map[i][j] != cub->start_p)
				error("UNKNOWN CHARACTER\n");
			j++;
		}
		i++;
	}
	if (check != 1)
		error("ERROR ON THE SPAWNING\n");
}

void	check_the_path(char **map, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void)cub;
	(void)map;
	while (map[0][j])
	{
		if (map[i][j] && (map[i][j] == '1' && (map[i][j + 1] == '0' || map[i][j + 1] == cub->start_p)))
			error("NOT A VALID MAP FIRST LINE\n");
		j++;
	}
}

void	check_the_path_2(char **map, t_cub *cub)
{
	int		i;
	size_t	j;
	int		check;

	j = 0;
	i = 0;
	check = 0;
	(void)cub;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			// if (map[i][j] && map[i][0] == '0')
			// 	error("ERROR\n");
			// if (map[i][j + 1] && map[i][j] && map[i][j] == '0' \
			// && (map[i][j + 1] == 32 || map[i][j + 1] == '\n'))
			// 	error("ERROR\n");
			// if ((j - 1 >= 0) && map[i][j] && map[i][j] == '0' \
			// && map[i][j - 1] == 32)
			// 	error("ERROR\n");
			// if ((i + 1 > cub->lines) && map[i][j] && map[i][j] == '0' \
			// && map[i + 1][j] != '0' && map[i + 1][j] != '1' \
			// && map[i + 1][j] != cub->start_p)
			// 	error("ERROR\n");
			// if ((i + 1 > 0) && map[i][j] && map[i][j] == '0' \
			// && map[i - 1][j] != '0' && map[i - 1][j] != '1' \
			// && map[i - 1][j] != cub->start_p)
			// 	error("ERROR\n");
			j++;
		}
		i++;
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
		error("YOUR MAP DOENS'T END WHITH '.cub'\n");
	return (0);
}
