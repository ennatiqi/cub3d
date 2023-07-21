/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:19:10 by aachfenn          #+#    #+#             */
/*   Updated: 2023/07/21 23:30:34 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_the_path(char **map, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[0][j])
	{
		if ((map[i][j] == '1' && map[i][j + 1] == '0') && j != 0)
		{
			printf("%d ,, %d\n", i, j);
			printf("NOT A VALID MAP FIRST LINE\n");
			exit(1);
		}
		j++;	
	}
	j = 0;
	// printf("%d ,, %d\n", cub->maplines, j);
	while (map[cub->maplines - 1][j])
	{
		if (map[cub->maplines - 1][j] == '0')
		{
			printf("NOT A VALID MAP LAST LINE\n");
			exit(1);
		}
		j++;	
	}
	j = 0;
	i = 1;
	while (map[i])
	{
		// printf("'%d',,,  '%c'..\n" , ft_strlen(map[i]), map[i][ft_strlen(map[i]) - 2]);
		// printf("'%d'\n", i);
		if (map[i][ft_strlen(map[i]) - 2] != '1')
		{
			printf("NOT A VALID MAP LAST POSITION\n");
			exit(1);
		}
		i++;
	}
	j = 0;
	i = 1;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == 32)
			j++;
		if (map[i][j] != '1')
		{
			// printf("%d ,%d, %s\n", i , j, map[i]);
			printf("NOT A VALID MAP FIRST POSITION\n");
			exit(1);
		}
		i++;
	}
}

//unusual maps
void	check_the_path_2(char **map, t_cub *cub)
{
	int	i;
	int	j;
	int check;

	j = 0;
	i = 0;
	check = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			// printf("%c\n", map[i][j]);
			if (map[i][j] == '0' && map[i][j + 1] == 32)
				check = 1;
			if (map[i][j] == '0' && map[i][j - 1] == 32)
				check = 1;
			if (map[i][j] == '0' && map[i + 1][j] == 32)
				check = 1;
			if (map[i][j] == '0' && map[i - 1][j] == 32)
				check = 1;
			j++;
		}
		i++;
	}
	if (check == 1)
	{
		printf("ERROR\n");
		exit (1);
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
		exit(1);
	}
}

int	exiter()
{
	exit(0);
}
