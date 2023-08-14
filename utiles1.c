/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:12:01 by rennatiq          #+#    #+#             */
/*   Updated: 2023/01/21 17:27:50 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_ifis_file(char *map)
{
	int		fd;

	fd = open(map, O_DIRECTORY);
	if (fd == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_rectangular(char *check, int size)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (check[i])
	{
		if (check[i] == '\n')
		{
			if (count - 1 != size)
				return (0);
			count = 0;
		}
		count++;
		i++;
		if (!check[i])
		{
			if (count - 1 != size)
				return (0);
		}
	}
	return (1);
}
char	*ft_strdup_noline(char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)malloc(ft_strlen(line));
	if (!tmp)
		return (0);
	while (i < (int)ft_strlen(line) - 1)
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\0';
	free(line);
	return (tmp);
}
char	*ft_strdup_m(char *s1)
{
	int		i;
	char	*s2;

	i = 0;
	s2 = (char *) malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!s2)
		return (0);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*read_norm(char *line, t_game *game)
{
	char	*check;

	check = ft_strdup_m(line);
	game->width = ft_strlen(line) - 1;
	game->line = ft_strdup_noline(line);
	return (check);
}
char	*ft_strjoin_so_long(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*resulta;
	int		m;
	int		n;

	i = 0;
	if (!s1 || !s2)
		return (0);
	n = ft_strlen(s1);
	m = ft_strlen(s2);
	resulta = (char *)malloc((n + m + 1) * sizeof(char));
	if (!resulta)
		return (0);
	while (i < n)
	{
		resulta[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0' && s2[j] != '\n')
		resulta[i++] = s2[j++];
	resulta[i] = 0;
	free(s1);
	free(s2);
	return (resulta);
}
void	read_maps(t_game *game, char *map)
{
	int		fd;
	char	*line;
	char	*check;

	// if (!check_ifis_file(map))
	// 	ft_error('F');
	fd = open(map, O_RDONLY);
	// if (fd < 0)
	// 	ft_error('S');
	line = get_next_line(fd);
	// if (!line)
	// 	ft_error('W');
	check = read_norm(line, game);
	while (line)
	{
		game->height++;
		line = get_next_line(fd);
		if (!line)
			break ;
		check = ft_strjoin(check, line);
		game->line = ft_strjoin_so_long(game->line, line);
	}
	// if (game->width > 40 || game->width < 2 || game->height > 30
	// 	|| game->height < 2 /* || !check_rectangular(check, game->width) */)
	// {
	// 	free(check);
	// 	ft_error('R');
	// }
	free(check);
	close(fd);
}
