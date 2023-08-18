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

void draw_wall(void *mlx_ptr, void *win_ptr,void *img,int textures_offsetX,int textures_offsetY, int i, int r)
{
	int bpp, size_line, endian;
	char *diraction;

	diraction = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	int pos = textures_offsetY * size_line + textures_offsetX * (bpp / 8);
	int color = *(int *)(diraction + pos);
	mlx_pixel_put(mlx_ptr, win_ptr, r + WIGHT / 2 , i, color);
}

void draw_wall_textures(void *mlx_ptr, void *win_ptr, t_game *game,t_wall *wall,int r)
{
	draw_line(mlx_ptr, win_ptr, r + WIGHT / 2, 0, r+ WIGHT / 2, wall->wall_start,0x212121 );

		int color;
		int textures_offsetX;
		int textures_offsetY;
	if (wall->diraction == 1 || wall->diraction == 2) 
		textures_offsetX = (int)wall->cast->vy % 64;
	else if (wall->diraction == 3 || wall->diraction == 4)
		textures_offsetX =  (int)wall->cast->hx % 64;

	for (int i = wall->wall_start; i < wall->wall_end; i++)
	{
		textures_offsetY = (int)((i - wall->wall_start) * (64.0 / wall->wall_height));


		if (wall->diraction == 1) 
			draw_wall(mlx_ptr, win_ptr,game->textures->ea,textures_offsetX,textures_offsetY,i,r);
		else if (wall->diraction == 2)
			draw_wall(mlx_ptr, win_ptr,game->textures->we,textures_offsetX,textures_offsetY,i,r);
		else if (wall->diraction == 3)
			draw_wall(mlx_ptr, win_ptr,game->textures->no,textures_offsetX,textures_offsetY,i,r);
		else
			draw_wall(mlx_ptr, win_ptr,game->textures->so,textures_offsetX,textures_offsetY,i,r);

	}

    draw_line(mlx_ptr, win_ptr, r+ WIGHT / 2, wall->wall_end, r+ WIGHT / 2, HEIGHT, 0x7D7D7D);


}


void draw_lines(void *mlx_ptr, void *win_ptr,t_player *player, t_game *game)
{
	int r;
	float rx,ry, ra;
	int wall_x = 0;
	t_casting *cast;
	t_wall *wall;

	wall = malloc(sizeof(t_wall));
	

	cast = malloc(sizeof(t_casting));

	wall->cast = cast;
	cast->ra = player->angle - DR *  WIGHT/4;
	if (cast->ra < 0)
		cast->ra += 2 * PI;
	if (cast->ra > 2 * PI)
		cast->ra -= 2 * PI;
	for (r = 0; r < WIGHT / 2 ;r++)
	{
		horizontal_vertical_lines(cast,player, game);
		

        wall->corrected_angle = player->angle - cast->ra;
		
		if (dist(cast->hx, cast->hy, player->x, player->y, cast->ra) >= dist(cast->vx, cast->vy, player->x, player->y, cast->ra))
		{
			if (cast->ra >= P3 || cast->ra < PI / 2)
				wall->diraction = 1;
			else if (cast->ra >= PI/2 && cast->ra < P3)
				wall->diraction = 2;
			draw_line(mlx_ptr, win_ptr, player->x , player->y, cast->vx, cast->vy, 0x00FF00);
			wall->dist_to_wall = dist(cast->vx, cast->vy, player->x, player->y, cast->ra)* cos(wall->corrected_angle);
		}
		else
		{
			if (cast->ra >= 0 && cast->ra < PI)
				wall->diraction = 3;
			else if (cast->ra >= PI && cast->ra < 2 * PI)
				wall->diraction = 4;
			draw_line(mlx_ptr, win_ptr, player->x, player->y, cast->hx, cast->hy, 0xFF0000);
			wall->dist_to_wall = dist(cast->hx, cast->hy, player->x, player->y, cast->ra) * cos(wall->corrected_angle);
		}

		wall->wall_height = ((HEIGHT) / wall->dist_to_wall) * 32;
		wall->wall_start = (int)((HEIGHT - wall->wall_height) / 2);
		wall->wall_end = wall->wall_start + wall->wall_height;


		draw_wall_textures(mlx_ptr, win_ptr,game, wall, r);

		
		cast->ra+= DR;
		if (cast->ra < 0)
			cast->ra += 2 * PI;
		if (cast->ra > 2 * PI)
			cast->ra -= 2 * PI;
	}
	

}





void draw_player(t_game *game,t_player *player, void *mlx_ptr, void *win_ptr)
{
    draw_rectangle(mlx_ptr, win_ptr, player->x, player->y, 2);
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
	// mlx_hook(game->win, 6, 0, &mouse_move, cub3d);
	while (1) {
        mlx_clear_window(game->mlx, game->win);

		draw_map(game);
        draw_player(game,game->player, game->mlx, game->win);
 
        mlx_do_sync(game->mlx);
    }
	mlx_loop(game->mlx);

	return (0);
}
