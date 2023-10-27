/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:48:17 by aachfenn          #+#    #+#             */
/*   Updated: 2023/10/27 11:19:19 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_game(t_game  *game, char **av)
{
	t_cub	*cub;
	char	**map;
	
	game->player = malloc (sizeof(t_player));
	cub = malloc(sizeof(t_cub));
	game->cub = cub;
	cub->check_tex = 0;
	cub->NO = NULL;
	cub->EA = NULL;
	cub->SO = NULL;
	cub->WE = NULL;

		name_check(av[1]);
		cub->maplines = maplines(av[1]);
		map = just_map(av[1], cub);
		char **buff = buff_map(map, cub);
		int hh = hight_calc(map);
		printf("--%d--\n", hh);
		exit(0);
		check_the_path(map, cub);
		check_component(map, cub);
		check_the_path_2(map, cub);
		check_mid(map, cub);
		check_c_f(cub);
		if (cub->NO[0] == '\0' || cub->EA[0] == '\0' || cub->SO[0] == '\0' || cub->WE[0] == '\0')
			error("ERROR IN TEX\n");

		// printf("-->'%s'\n", cub->NO);
		// printf("-->'%s'\n", cub->SO);
		// printf("-->'%s'\n", cub->WE);
		// printf("-->'%s'\n", cub->EA);
		// printf("-->'%s'\n", cub->F);
		// printf("-->'%s'\n", cub->C);
		// printf("---<>%c\n", cub->start_p);
		// printf("x == %d, Y == %d, lines = %d\n",cub->x, cub->y, cub->lines);
		// int i = 0;
		// while (i < 4)
		// 	printf("cub->c_color ;%d;\n", cub->c_color[i++]);
		// i = 0;
		// while (i < 4)
		// printf("cub->f_color ;%d;\n", cub->f_color[i++]);
	game->maps = map;
	game->height = cub->lines;
	game->width = width_calc(map);
	game->player->x = (cub->x * 64) + 32;
	game->player->y = (cub->y * 64) + 32;
	if (cub->start_p == 'N')
		game->player->angle = 3 * M_PI_2;
	if (cub->start_p == 'S')
		game->player->angle = M_PI_2;
	if (cub->start_p == 'E')
		game->player->angle = 0;
	if (cub->start_p == 'W')
		game->player->angle = M_PI;
}

int valide_move(int tmpy,int tmpx,t_game *game)
{
	tmpy /= 64;
	tmpx /= 64;
	if (game->maps[tmpy][tmpx] == '1')
		return 0;
	return 1;
}

void key_press(void *game2)
{
	t_game *game = (t_game *)game2;
	int speed = 2;
	float tmpx = game->player->x;
	float tmpy = game->player->y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->angle -= 0.05;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->angle += 0.05;
	if (game->player->angle < 0)
		game->player->angle += 2 * M_PI;
	if (game->player->angle > 2 * M_PI)
		game->player->angle -= 2 * M_PI;
	

	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		tmpy += speed * sin(game->player->angle + M_PI / 2);
		tmpx += speed * cos(game->player->angle + M_PI / 2);
		if (valide_move(tmpy,tmpx,game))
		{
			game->player->x = tmpx;
			game->player->y = tmpy;
		}
	}
	
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		tmpy -= speed * sin(game->player->angle + M_PI / 2);
		tmpx -= speed * cos(game->player->angle + M_PI / 2);
		if (valide_move(tmpy,tmpx,game))
		{
			game->player->x = tmpx;
			game->player->y = tmpy;
		}
	}

	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		tmpy +=  speed * sin(game->player->angle);
		tmpx +=  speed * cos(game->player->angle);
		if (valide_move(tmpy,tmpx,game))
		{
			game->player->x = tmpx;
			game->player->y = tmpy;
		}
	}
	
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		tmpy -= speed * sin(game->player->angle);
		tmpx -= speed * cos(game->player->angle);
		if (valide_move(tmpy,tmpx,game))
		{
			game->player->x = tmpx;
			game->player->y = tmpy;
		}
	}
	

}

void draw_rectangle(mlx_image_t* img, int x, int y, int width,int color)
{
	int i = 0;
	int j ;

	while (i < width)
	{
		j = 0;
		while (j < width)
		{
			mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}


void draw(void *game2)
{
	t_game *game = (t_game *)game2;

	ray_casting(game);
}


int main(int ac, char **av)
{
	t_game  *game;


	if (ac == 2)
	{
		game = malloc(sizeof(t_game));
		set_game(game, av);
		init_images(game);

		game->mlx = mlx_init(WIGHT, HEIGHT, "Cub3d", false);
		game->img = mlx_new_image(game->mlx, WIGHT, HEIGHT);
		mlx_image_to_window(game->mlx,game->img,0,0);
		// mlx_key_hook(game->mlx, &key_press, game);

		mlx_loop_hook(game->mlx, key_press, game);
		mlx_loop_hook(game->mlx, draw, game);

		mlx_loop(game->mlx);
		
	}
	return (0);
}