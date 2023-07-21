/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 22:34:25 by aachfenn          #+#    #+#             */
/*   Updated: 2023/07/21 15:30:38 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map_check(char **av)
{
	name_check(av[1]);
	return (0);
}

void	path_maker(char **mape, int i, int j, t_cub *cub)
{
	mape[i][j] = 'P';
	// int ii = 0;
	// while (mape[ii])
	// {
	// 	puts(mape[ii++]);
	// }
	if ((j != ft_strlen(mape[i]) && mape[i][j + 1] == '1'))
	{
		// printf("---> %zu\n", ft_strlen(mape[i]));
		// puts("()))))))))))");
		path_maker(mape, i, j + 1, cub);
	}
	if (j != 0 && mape[i][j - 1] == '1')
	{
		// puts("==============");
		path_maker(mape, i, j - 1, cub);
	}
	if (i != 0 && mape[i - 1][j] == '1')
	{
		// puts("+++++++++");
		path_maker(mape, i - 1, j, cub);
	}
	if (i != (cub->maplines - 1) && mape[i + 1][j] == '1')
	{
		// puts("-----------");
		path_maker(mape, i + 1, j, cub);
	}
}

void	check_the_path(char **map, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[0][j])
	{
		if ((map[i][j] == '1' && map[i][j + 1] == '0')&& j != 0)
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

int main(int ac, char **av)
{
	void	*init;
	void	*win;
	char	**map;
	char	**mape;
	t_cub	cub;

	(void)ac;
	(void)av;
	(void)map;
	(void)win;
	if (ac == 2)
	{
		cub.maplines = maplines(av[1]);
		map = mapreader(av[1]);
		cub.i = 0;
		cub.j = 0;
		check_the_path(map, &cub);
		check_the_path_2(map, &cub);
		int ii = 0;
		while (map[ii])
		{
			puts(map[ii++]);
		}
		map_check(av);
	}
	// init = mlx_init();
	// win = mlx_new_window(init, 500, 500, "101");
	// mlx_hook(win, 17, 0, exiter, NULL);
	// mlx_loop(init);
	return (0);
}
