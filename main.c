/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 22:34:25 by aachfenn          #+#    #+#             */
/*   Updated: 2023/07/02 23:22:37 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map_check(char **av)
{
	name_check(av[1]);
	return (0);
}

void	path_maker(char **mape, int i, int j)
{
	mape[i][j] = 'P';
	printf("%c\n", mape[i][j]);
	if (mape[i][j + 1] != '\n' && mape[i][j + 1] == '1')
	{
		puts("()))))))))))");
		path_maker(mape, i, j + 1);
	}
	if (mape[i][j + 1] != '\n' && mape[i][j - 1] == '1')
	{
		path_maker(mape, i, j - 1);
		puts("==============");
	}
	if (mape[i][j + 1] != '\n' && mape[i - 1][j] == '1')
	{
		puts("+++++++++");
		path_maker(mape, i - 1, j);
	}
	if (mape[i][j + 1] != '\n' && mape[i + 1][j] == '1')
	{
		puts("-----------");
		path_maker(mape, i + 1, j);
	}
}

int main(int ac, char **av)
{
	void	*init;
	void	*win;
	char	**map;
	(void)ac;
	(void)av;
	(void)map;
	(void)win;
	
	if (ac == 2)
	{
		map = mapreader(av[1]);
		// path_maker(map, 0, 0);
		// int i = 0;
		// while (map[i])
		// {
		// 	puts(map[i++]);
		// }
		map_check(av);
	}

	init = mlx_init();
	win = mlx_new_window(init, 500, 500, "101");
	mlx_hook(win, 17, 0, exiter, NULL);
	mlx_loop(init);
	return (0);
}
