/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 22:34:25 by aachfenn          #+#    #+#             */
/*   Updated: 2023/07/22 00:17:45 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"



void draw_lines(void *mlx_ptr, void *win_ptr,t_player *player, t_game *game)
{
	int r;
	float rx,ry, ra;
	int wall_x = 0;
	t_casting *cast;
	float dist_to_wall;
	 float corrected_angle;
		int color;
	float wall_height;
	int wall_start ;
	int wall_end;


	cast = malloc(sizeof(t_casting));

	cast->ra = player->angle - DR *  WIGHT/4;
	if (cast->ra < 0)
		cast->ra += 2 * PI;
	if (cast->ra > 2 * PI)
		cast->ra -= 2 * PI;
	for (r = 0; r < WIGHT / 2 ;r++)
	{
		horizontal_vertical_lines(cast,player, game);
		

        corrected_angle = player->angle - cast->ra;
		
		if (dist(cast->hx, cast->hy, player->x, player->y, cast->ra) >= dist(cast->vx, cast->vy, player->x, player->y, cast->ra))
		{
			if (cast->ra >= P3 || cast->ra < PI / 2)
				color = 0xFF0000;
			else if (cast->ra >= PI/2 && cast->ra < P3)
				color = 0xFFACAC;
			draw_line(mlx_ptr, win_ptr, player->x , player->y, cast->vx, cast->vy, color);
			dist_to_wall = dist(cast->vx, cast->vy, player->x, player->y, cast->ra)* cos(corrected_angle);
		}
		else
		{
			if (cast->ra >= 0 && cast->ra < PI)
				color = 0xCC0000;
			else if (cast->ra >= PI && cast->ra < 2 * PI)
				color = 0xCCACAC;
			draw_line(mlx_ptr, win_ptr, player->x, player->y, cast->hx, cast->hy, color);
			dist_to_wall = dist(cast->hx, cast->hy, player->x, player->y, cast->ra) * cos(corrected_angle);
		}

		wall_height = ((HEIGHT) / dist_to_wall) * 32;
		wall_start = (int)((HEIGHT - wall_height) / 2);
		wall_end = wall_start + wall_height;
    	draw_line(mlx_ptr, win_ptr, r + WIGHT / 2 , 0, r+ WIGHT / 2, wall_start,0x00FF00 );
		
    	draw_line(mlx_ptr, win_ptr, r+ WIGHT / 2, wall_start, r+ WIGHT / 2, wall_end, color);
    	draw_line(mlx_ptr, win_ptr, r+ WIGHT / 2, wall_end, r+ WIGHT / 2, HEIGHT, 0x0000FF);

		
		cast->ra+= DR; 
		if (cast->ra < 0)
			cast->ra += 2 * PI;
		if (cast->ra > 2 * PI)
			cast->ra -= 2 * PI;
	}
	

}





void draw_player(t_game *game,t_player *player, void *mlx_ptr, void *win_ptr)
{
    draw_rectangle(mlx_ptr, win_ptr, player->x, player->y, 1);
	draw_lines(mlx_ptr, win_ptr,player, game);
}




int main(int ac, char **av)
{
	void	*init;
	void	*win;
	char	**map;
	char	**mape;
	t_cub	cub;
	t_game *game;

	(void)ac;
	(void)av;
	(void)map;
	(void)win;
	if (ac == 2)
	{
		name_check(av[1]);
		cub.maplines = maplines(av[1]);
		map = mapreader(av[1]);
		cub.i = 0;
		cub.j = 0;
		check_the_path(map, &cub);
		check_the_path_2(map, &cub);
		check_component(map);
	}


	game = insert_to_game();
	game->mlx = mlx_init();
	set_game(game, av[1]);
	mlx_hook(game->win, 2, 1L<<0, key_press, game);
	while (1) {
        mlx_clear_window(game->mlx, game->win);

		draw_map(game);
        draw_player(game,game->player, game->mlx, game->win);
 
        mlx_do_sync(game->mlx);
    }
	mlx_loop(game->mlx);

	return (0);
}
