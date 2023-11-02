/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:05:28 by rennatiq          #+#    #+#             */
/*   Updated: 2023/11/02 15:45:43 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	key_press_right(t_game *game)
{
	int		speed;
	float	tmpx;
	float	tmpy;

	tmpx = game->player->x;
	tmpy = game->player->y;
	speed = 2;
	tmpy += speed * sin(game->player->angle + M_PI / 2);
	tmpx += speed * cos(game->player->angle + M_PI / 2);
	if (valide_move(tmpy, tmpx, game))
	{
		game->player->x = tmpx;
		game->player->y = tmpy;
	}
}

void	key_press_left(t_game *game)
{
	int		speed;
	float	tmpx;
	float	tmpy;

	tmpx = game->player->x;
	tmpy = game->player->y;
	speed = 2;
	tmpy -= speed * sin(game->player->angle + M_PI / 2);
	tmpx -= speed * cos(game->player->angle + M_PI / 2);
	if (valide_move(tmpy, tmpx, game))
	{
		game->player->x = tmpx;
		game->player->y = tmpy;
	}
}

void	key_press_up(t_game *game)
{
	int		speed;
	float	tmpx;
	float	tmpy;

	tmpx = game->player->x;
	tmpy = game->player->y;
	speed = 2;
	tmpy += speed * sin(game->player->angle);
	tmpx += speed * cos(game->player->angle);
	if (valide_move(tmpy, tmpx, game))
	{
		game->player->x = tmpx;
		game->player->y = tmpy;
	}
}

void	key_press_down(t_game *game)
{
	int		speed;
	float	tmpx;
	float	tmpy;

	tmpx = game->player->x;
	tmpy = game->player->y;
	speed = 2;
	tmpy -= speed * sin(game->player->angle);
	tmpx -= speed * cos(game->player->angle);
	if (valide_move(tmpy, tmpx, game))
	{
		game->player->x = tmpx;
		game->player->y = tmpy;
	}
}

void	key_press(void *game2)
{
	t_game	*game;

	game = (t_game *)game2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		exiter(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->angle -= 0.05;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->angle += 0.05;
	if (game->player->angle < 0)
		game->player->angle += 2 * M_PI;
	if (game->player->angle > 2 * M_PI)
		game->player->angle -= 2 * M_PI;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		key_press_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		key_press_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || \
	mlx_is_key_down(game->mlx, MLX_KEY_UP))
		key_press_up(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || \
	mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		key_press_down(game);
}
