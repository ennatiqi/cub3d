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
	int r, mx,my,mp ,dof;
	float rx,ry, ra,xo,yo;
	float hx,hy;
	float vx,vy;
	int wall_x = 0;

	ra = player->angle - DR * 30;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	for (r = 0; r < 60 ;r++)
	{
		//check horizontal lines
		dof = 0;
		float atan = 1/tan(ra);
		// if (sin(ra)> 0)
		if (ra < PI)
		{
			hy = (int)player->y * 64 / 64 - 1; 
			hx = (player->y - hy ) * atan + player->x; 
			yo = -0.5; 
			xo = -yo * atan;
		}
		// if (sin(ra) < 0)
		if (ra > PI) 
		{
			hy = ((int)player->y * 64 / 64) + 64;
			hx = (player->y - hy ) * atan + player->x; 
			yo = 0.5; 
			xo = -yo * atan;
		}
		if (ra == 0 || ra == (float)PI)
		{
			hy = player->y;
			hx = player->x;
		}
		else
		{
			while (1)
			{
				mx = (int)(hx) / 64;
				my = (int)(hy) / 64;
				mp = my * game->width + mx;

				if (mx >= 0 && mx < game->width && my >= 0 && my < game->height)
				{
					if (game->line[mp] == '1')
						break;
					else
					{
						hx += xo;
						hy += yo;
					}
				}
				else
					break;
		}
        }

		//check vertical lines
		dof = 0;
		atan = tan(ra);
		if (ra < P2 || ra > P3)  
		{
			vx = (int)player->x * 64 / 64 + 64; 
			vy = (player->x - vx ) * atan + player->y; 
			xo = 0.5; 
			yo = -xo * atan;
		}
		if (ra > P2 && ra < P3) 
		{
			vx = ((int)player->x * 64 / 64) - 1;
			vy = (player->x - vx ) * atan + player->y; 
			xo = -0.5; 
			yo = -xo * atan;
		}
		if (ra == P2 || ra == P3)
		{
			vx = player->x; 
			vy = player->y;
		}
		else
		{
			while (1)
			{
				mx = (int)(vx) / 64;
				my = (int)(vy) / 64;
				mp = my * game->width + mx;

				if (mx >= 0 && mx < game->width && my >= 0 && my < game->height)
				{
					if (game->line[mp] == '1')
					{
						break;
					}
					else
					{
						vx += xo;
						vy += yo;
					}
				}
				else
					break;

		}
        }

		float dist_to_wall;
        float corrected_angle = player->angle - ra;
		int color;
		if (dist(hx, hy, player->x, player->y, ra) > dist(vx, vy, player->x, player->y, ra))
		{
			color = 0xCC0000;
			draw_line(mlx_ptr, win_ptr, player->x + 2, player->y + 2, vx, vy, 0xFF0000);
			dist_to_wall = dist(vx, vy, player->x, player->y, ra)* cos(corrected_angle);
		}
		else
		{
			color = 0xFF0000;
			draw_line(mlx_ptr, win_ptr, player->x + 2, player->y + 2, hx, hy, 0xFF0000);
			dist_to_wall = dist(hx, hy, player->x, player->y, ra) * cos(corrected_angle);
		}



		int wall_height = (int)((64 * game->height) / dist_to_wall) * 10;

		int wall_start = (64 *game->height - wall_height) / 2;
		int wall_end = (wall_start + wall_height);
		for(int k = 0; k < game->width ; k++)
		{
    		draw_line(mlx_ptr, win_ptr, wall_x + k + game->width * 64, wall_start, wall_x+ k+ game->width* 64, wall_end, 0xFF0000);

    	}	
		// draw_rectangle2(mlx_ptr, win_ptr, wall_x + game->width * 64, wall_start , wall_x, wall_end - wall_start, 0xFF0000) ;
		wall_x += game->width * 64 / 60; 
		
		ra+= DR; 
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
	

}





void draw_player(t_game *game,t_player *player, void *mlx_ptr, void *win_ptr) {
   

    draw_rectangle(mlx_ptr, win_ptr, player->x, player->y, 8);
	draw_lines(mlx_ptr, win_ptr,player, game);

    // draw_line(mlx_ptr, win_ptr, player->x + 2, player->y + 2, player->x + 52 * cos(player->angle), player->y - 52 * sin(player->angle), 0xFFFF66);
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
