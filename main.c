/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:48:17 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/01 15:45:11 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	direction_seter(t_game *game)
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

void	set_game(t_game *game, char **av)
{
	char	**map;
	char	**buff;

	name_check(av[1], game);
	map = just_map(av[1], game->cub, game);
	check_newline(map, game);
	buff = buff_map(map, game->cub);
	check_component(map, game);
	check_first_line(map, game->cub, game);
	check_mid(map, game);
	check_c_f(game->cub, game);
	if (game->cub->NO[0] == '\0' || game->cub->EA[0] == '\0' \
	|| game->cub->SO[0] == '\0' || game->cub->WE[0] == '\0')
		error("ERROR IN TEX\n", game);
	game->maps = buff;
	game->height = game->cub->lines + 1;
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
	t_game	*game;
	int		speed;
	float	tmpx;
	float	tmpy;

	game = (t_game *)game2;
	tmpx = game->player->x;
	tmpy = game->player->y;
	speed = 2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		// to_free(game);
		// system("leaks cub3D");
		mlx_close_window(game->mlx);
	}
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || \
	mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		tmpy += speed * sin(game->player->angle);
		tmpx += speed * cos(game->player->angle);
		if (valide_move(tmpy, tmpx, game))
		{
			game->player->x = tmpx;
			game->player->y = tmpy;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || \
	mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
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

void	draw_rectangle(mlx_image_t* img, int x, int y, int width,int color)
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

void	draw(void *game2)
{
	t_game	*game;

	game = (t_game *)game2;
	ray_casting(game);
}

void	allocation(t_game *game)
{
	game->player = malloc (sizeof(t_player));
	if (!game->player)
		error("ERROR IN MALLOC\n", game);
	ft_bzero(game->player, sizeof(t_player));
	game->cub = malloc(sizeof(t_cub));
	if (!game->cub)
		error("ERROR IN MALLOC\n", game);
	ft_bzero(game->cub, sizeof(t_cub));
	game->cast = malloc(sizeof(t_casting));
	if (!game->cast)
		error("ERROR IN MALLOC\n", game);
	ft_bzero(game->cast, sizeof(t_casting));
	game->wall = malloc(sizeof(t_wall));
	if (!game->wall)
		error("ERROR IN MALLOC\n", game);
	ft_bzero(game->wall, sizeof(t_wall));
	game->texture = malloc(sizeof(t_texture));
	if (!game->texture)
		error("ERROR IN MALLOC\n", game);
	ft_bzero(game->texture, sizeof(t_texture));
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
		ft_bzero(game, sizeof(t_game));
		allocation(game);
		set_game(game, av);
		initialize_mlx(game);
		// to_free(game);
		// system("leaks cub3D");
	}
	return (0);
}
