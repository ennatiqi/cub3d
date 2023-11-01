/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:48:17 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/01 14:14:16 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initializer(t_game *game)
{
	game->cub->check_tex = 0;
	game->cub->NO = NULL;
	game->cub->EA = NULL;
	game->cub->SO = NULL;
	game->cub->WE = NULL;
	game->cub->C = NULL;
	game->cub->F = NULL;
	game->cub->c_color = NULL;
	game->cub->f_color = NULL;
	game->texture->Ncolors = NULL;
	game->texture->Ecolors = NULL;
	game->texture->Wcolors = NULL;
	game->texture->Scolors = NULL;
	game->texture->Npath = NULL;
	game->texture->Epath = NULL;
	game->texture->Wpath = NULL;
	game->texture->Spath = NULL;
}

void direction_seter(t_game *game)
{
	if (game->cub->start_p == 'N')
		game->player->angle = 3 * M_PI_2;
	if (game->cub->start_p == 'S')
		game->player->angle = M_PI_2;
	if (game->cub->start_p == 'E')
		game->player->angle = 0;
	if (game->cub->start_p == 'W')
		game->player->angle = M_PI;
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void set_game(t_game  *game, char **av)
{
	char	**map;
	char	**buff;

	initializer(game);
	name_check(av[1]);
	map = just_map(av[1], game->cub, game);
	check_newline(map, game->cub, game);
	buff = buff_map(map, game->cub);
	check_component(map, game);
	check_first_line(map, game->cub, game);
	check_mid(map, game);
	check_c_f(game->cub, game);
	if (game->cub->NO[0] == '\0' || game->cub->EA[0] == '\0' \
	|| game->cub->SO[0] == '\0' || game->cub->WE[0] == '\0')
		error("ERROR IN TEX\n", game);
	game->maps = buff;
	game->height = game->cub->lines;
	game->width = width_calc(map);
	game->player->y = (game->cub->y * 64) + 32;
	game->player->x = (game->cub->x * 64) + 32;
	direction_seter(game);
	free_map(map);
}

int	valide_move(int tmpy, int tmpx, t_game *game)
{
	tmpy /= 64;
	tmpx /= 64;
	if ((game->maps[(int)game->player->y / 64][tmpx] == '1' && \
	game->maps[tmpy][(int)game->player->x / 64] == '1') \
	|| game->maps[tmpy][tmpx] == '1')
		return (0);
	return (1);
}

void	key_press(void *game2)
{
	t_game	*game = (t_game *)game2;
	int		speed = 2;
	float	tmpx = game->player->x;
	float	tmpy = game->player->y;

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
	int	i;
	int	j;

	i = 0;
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
	t_game	*game = (t_game *)game2;

	ray_casting(game);
}

void	to_free(t_game	*game)
{
	if (game)
	{
		if (game->cub)
		{
			if (game->cub->NO)
				free(game->cub->NO);
			if (game->cub->EA)
				free(game->cub->EA);
			if (game->cub->SO)
				free(game->cub->SO);
			if (game->cub->WE)
				free(game->cub->WE);
			if (game->cub->C)
				free(game->cub->C);
			if (game->cub->F)
				free(game->cub->F);
			if (game->cub->c_color)
				free(game->cub->c_color);
			if (game->cub->f_color)
				free(game->cub->f_color);
			if (game->cub)
				free(game->cub);
		}
		if (game->player)
			free(game->player);
		if (game->cast)
			free(game->cast);
		if (game->wall)
			free(game->wall);

	if (game->texture)
	{
		// if (game->texture->Nimage)
		// 	mlx_delete_texture(game->texture->Nimage);
		// if (game->texture->Wimage)
		// 	mlx_delete_texture(game->texture->Wimage);
		// if (game->texture->Simage)
		// 	mlx_delete_texture(game->texture->Simage);
		// if (game->texture->Eimage)
		// 	mlx_delete_texture(game->texture->Eimage);

		if (game->texture->Ncolors)
			free(game->texture->Ncolors);
		if (game->texture->Ecolors)
			free(game->texture->Ecolors);
		if (game->texture->Wcolors)
			free(game->texture->Wcolors);
		if (game->texture->Scolors)
			free(game->texture->Scolors);
		if (game->texture->Npath)
			free(game->texture->Npath);
		if (game->texture->Epath)
			free(game->texture->Epath);
		if (game->texture->Wpath)
			free(game->texture->Wpath);
		if (game->texture->Spath)
			free(game->texture->Spath);
		free(game->texture);
	}
	
	// if (game->img)
	// 	mlx_delete_image(game->mlx, game->img);
	
	// int i = 0;
	// if (game->maps)
	// {
	// 	while (game->maps[i])
	// 		free(game->maps[i++]);
	// 	free(game->maps);
	// }
	if (game)
		free(game);
	}
}

void	allocation(t_game *game)
{
	game->player = malloc (sizeof(t_player));
	if (!game->player)
		error("ERROR IN MALLOC\n", game);
	game->cub = malloc(sizeof(t_cub));
	if (!game->cub)
		error("ERROR IN MALLOC\n", game);
	game->cast = malloc(sizeof(t_casting));
	if (!game->cast)
		error("ERROR IN MALLOC\n", game);
	game->wall = malloc(sizeof(t_wall));
	if (!game->wall)
		error("ERROR IN MALLOC\n", game);
	game->texture = malloc(sizeof(t_texture));
	if (!game->texture)
		error("ERROR IN MALLOC\n", game);
}

void	initialize_mlx(t_game * game)
{
	init_images(game);
	game->mlx = mlx_init(WIGHT, HEIGHT, "Cub3d", false);
	if (!game->mlx)
		error("ERROR IN MLX_INIT\n", game);
	game->img = mlx_new_image(game->mlx, WIGHT, HEIGHT);
	if (!game->img)
		error("ERROR IN MLX_NEW_IMAGE\n", game);
	mlx_image_to_window(game->mlx,game->img,0,0);
	if (!game->img)
		error("ERROR IN MLX_IMAGE_TO_WINDOW\n", game);
	mlx_loop_hook(game->mlx, key_press, game);
	mlx_loop_hook(game->mlx, draw, game);
	mlx_loop(game->mlx);
}

int main(int ac, char **av)
{
	t_game	*game;

	if (ac == 2)
	{
		game = malloc(sizeof(t_game));
		if (!game)
			error("ERROR IN MALLOC\n", game);
		allocation(game);
		set_game(game, av);
		initialize_mlx(game);
		// to_free(game);
		// system("leaks cub3D");
	}
	return (0);
}
