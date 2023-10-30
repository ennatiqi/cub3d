/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:19:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/10/30 10:38:15 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char **buff_map(char **map, t_cub *cub)
{
	int i;
	char **new_map;
	int width = width_calc(map) - 1;
	char	*str;

	i = 0;
	str = malloc((width + 1) * sizeof(char));
	while (map[i])
	{
		i++;
	}
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
	i = 0;
	while (i <= cub->lines)
	{
		int j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] != 32)
				new_map[i][j] = map[i][j];
			j++;
		}
		i++;
	}
	return (new_map);
}

int	hight_calc(char **map)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (map[i])
	{
		len = i;
		printf("%d[%c] , %d\n", i, ft_strtrim(map[i], " ")[0], len);
		if (map[i] && ft_strtrim(map[i], " ")[0] == '\n')
		{
			while (map[i] && ft_strtrim(map[i], " ")[0] == '\n')
			{
				printf("in ww%d[%c] , %d\n", i, ft_strtrim(map[i], " ")[0], len);
				printf("====\n");
				if (map[i] && ft_strtrim(map[i], " ")[0] != '\n')
				{
					puts("ls");
					break ;
				}
				i++;
			}
			if (map[i] == NULL)
			{
				puts("cat");;
				return (len);
			}
		}
		i++;
	}
	return(len);
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

int	check_for_map(char *s, t_cub *cub)
{
	char	*str;

	str = ft_strtrim(s, " ");
	if (str[0] == 'N' && str[1] == 'O' && (str[2] == 32))
	{
		cub->NO = ft_strtrim(ft_substr(str, 2, ft_strlen(str)), " \n");
		cub->check_tex++;
	}
	else if (str[0] == 'S' && str[1] == 'O' && (str[2] == 32))
	{
		cub->SO = ft_strtrim(ft_substr(str, 2, ft_strlen(str)), " \n");
		cub->check_tex++;
	}
	else if (str[0] == 'W' && str[1] == 'E' && (str[2] == 32))
	{
		cub->WE = ft_strtrim(ft_substr(str, 2, ft_strlen(str)), " \n");
		cub->check_tex++;
	}
	else if (str[0] == 'E' && str[1] == 'A' && (str[2] == 32))
	{
		cub->EA = ft_strtrim(ft_substr(str, 2, ft_strlen(str)), " \n");
		cub->check_tex++;
	}
	else if (str[0] == 'F' && str[1] == 32)
	{
		cub->F = ft_strtrim(ft_substr(str, 1, ft_strlen(str)), " \n");
		cub->check_tex++;
	}
	else if (str[0] == 'C' && str[1] == 32)
	{
		cub->C = ft_strtrim(ft_substr(str, 1, ft_strlen(str)), " \n");
		cub->check_tex++;
	}
	else if (ft_isalnum(str[0]))
	{
		error("UNKNOWN ASSET\n");
		exit(0);
	}
	if (cub->check_tex == 6)
		return (0);
	return (1);
}

char	**just_map(char *mapber, t_cub *cub)
{
	char	**str;
	char	**map;
	char	*tmp;
	char	*tmp_1;
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
			error("ERROR ON THE INPUT\n");
		if (check_for_map(str[i], cub) == 0)
		{
			free(str[i]);
			break ;
		}
		free(str[i]);
		i++;
	}
	free(str);
	if (cub->check_tex != 6)
		error("INPUT ERROR (TEXTURES)\n");
	cub->lines = lines = lines - i - 3;
	map = malloc((lines + 3) * sizeof(char *));
	i = 0;
	while (1)
	{
		tmp_1 = get_next_line(fd);
		tmp = ft_strtrim(tmp_1, " ");
		if (tmp == NULL)
			error("ERROR ON THE INPUT AFTER TEXTURES\n");
		if (tmp[0] != '\n')
		{
			map[i++] = tmp_1;
			free(tmp);
			break ;
		}
	}
	while (1)
	{
		map[i] = get_next_line(fd);
		if (map[i] == NULL)
			break ;
		i++;
	}
	close(fd);
	// i = 0;
	// while (map[i])
	// 	printf("%s", map[i++]);
	return (map);
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
